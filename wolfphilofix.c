# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				ate_enough;
	int				finish_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork_padlock;
	pthread_mutex_t	print_padlock;
	pthread_mutex_t	eat_padlock;
	pthread_mutex_t	finish_padlock;
}					t_table;

# define TAKE "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FINISH "f"
# define FINISH_MSG "All philosophers ate enough!"
# define YES 1
# define NO 0

void		advance_time(t_philo *philo, long long ms);
void		print_action(t_philo *philo, const char *status);
long long	now(void);
int		exit_error(char *msg, t_table *table, int n);
int			ft_atoi(const char *s);

int			lone_philosopher(t_table *table);
int		start_padlocks(t_table *table);
int		call_philosophers(t_table *table);
int		set_table(t_table *table, int ac, char **av);

int			is_time_to_finish(t_philo *philo, int order);
int			is_someone_dead_or_full(t_philo *philo);
void		time_to_eat(t_philo *philo);
void		*start_dinner(void *arg);
int			turn_philosophers_in_threads(t_table *table);

void		clean_table(t_table *table);
void		destroy_padlocks(t_table *table);
void		finish_dinner(t_table *table);
void		start_dinner_monitor(t_table *table);

int	is_time_to_finish(t_philo *philo, int finish_order)
{
	pthread_mutex_lock(&philo->table->finish_padlock);
	if (finish_order || philo->table->finish_flag)
	{
		if (finish_order)
			philo->table->finish_flag = 1;
		pthread_mutex_unlock(&philo->table->finish_padlock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_padlock);
	return (0);
}

int	is_someone_dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_padlock);
	if (now() - philo->last_eat >= philo->table->time_to_die)
	{
		print_action(philo, DIE);
		is_time_to_finish(philo, YES);
		pthread_mutex_unlock(&philo->table->eat_padlock);
		return (1);
	}
	else if (philo->table->must_eat_times > 0
		&& philo->eat_count >= philo->table->must_eat_times)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->philosophers)
		{
			is_time_to_finish(philo, YES);
			print_action(philo, FINISH);
			pthread_mutex_unlock(&philo->table->eat_padlock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->eat_padlock);
	return (0);
}

void	time_to_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_padlock[philo->l_fork]);
		pthread_mutex_lock(&philo->table->fork_padlock[philo->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_padlock[philo->r_fork]);
		pthread_mutex_lock(&philo->table->fork_padlock[philo->l_fork]);
	}
	print_action(philo, TAKE);
	print_action(philo, TAKE);
	print_action(philo, EAT);
	advance_time(philo, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->eat_padlock);
	philo->eat_count++;
	philo->last_eat = now();
	pthread_mutex_unlock(&philo->table->eat_padlock);
	pthread_mutex_unlock(&philo->table->fork_padlock[philo->r_fork]);
	pthread_mutex_unlock(&philo->table->fork_padlock[philo->l_fork]);
}

int	lone_philosopher(t_table *table)
{
	print_action(&table->philo[0], TAKE);
	advance_time(&table->philo[0], table->time_to_die);
	print_action(&table->philo[0], DIE);
	is_time_to_finish(&table->philo[0], YES);
	return (0);
}

void	*start_dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 100);
	while (1)
	{
		if (philo->table->philosophers == 1)
		{
			lone_philosopher(philo->table);
			return (0);
		}
		if (is_time_to_finish(philo, NO))
			return (0);
		time_to_eat(philo);
		print_action(philo, SLEEP);
		advance_time(philo, philo->table->time_to_sleep);
		print_action(philo, THINK);
		
	//	if (philo->table->philosophers % 2 != 0
	//		&& philo->table->philosophers <= 127)
	//		advance_time(philo, philo->table->time_to_eat);
		usleep(philo->table->time_to_eat * 1000 / 3);	
	}	
	return (0);
}

void	clean_table(t_table *table)
{
	free (table->philo);
	free (table->fork_padlock);
}

void	destroy_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philosophers)
		pthread_mutex_destroy(&table->fork_padlock[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_padlock);
	pthread_mutex_destroy(&table->eat_padlock);
	pthread_mutex_destroy(&table->finish_padlock);
}

void	finish_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philosophers)
		pthread_join(table->philo[i].thread, NULL);
	destroy_padlocks(table);
}

void	start_dinner_monitor(t_table *table)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = -1;
		table->ate_enough = 0;
		while (++i < table->philosophers)
		{
			if (continue_flag && is_someone_dead_or_full(&table->philo[i]))
				continue_flag = 0;
		}
		usleep(10);
	}
	finish_dinner(table);
}

int	turn_philosophers_in_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philosophers)
	{
		if (pthread_create(&table->philo[i].thread, NULL, \
			start_dinner, &table->philo[i]))
			return (exit_error("Couldn't create thread", table, 3));
	}
	return (1);
}

int	start_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philosophers)
	{
		if (pthread_mutex_init(&table->fork_padlock[i], NULL))
			return (exit_error("Couldn't init forks mutex", table, 2));
	}
	if (pthread_mutex_init(&table->print_padlock, NULL))
		return  (exit_error("Couldn't init print mutex", table, 2));
	if (pthread_mutex_init(&table->eat_padlock, NULL))
		return (exit_error("Couldn't init eat mutex", table, 2));
	if (pthread_mutex_init(&table->finish_padlock, NULL))
		return (exit_error("Couldn't init finish mutex", table, 2));
	return (1);
}

int	call_philosophers(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->philosophers);
	table->fork_padlock = malloc(sizeof(pthread_mutex_t) * table->philosophers);
	if (!table->philo || !table->fork_padlock)
		return (exit_error("Couldn't create the philosophers and forks", table, 1));
	table->start_time = now();
	while (++i < table->philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].l_fork = i;
		table->philo[i].r_fork = (i + 1) % table->philosophers;
		table->philo[i].eat_count = 0;
		table->philo[i].last_eat = table->start_time;
		table->philo[i].table = table;
	}
	return (1);
}

int	set_table(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (exit_error("Wrong number of arguments", NULL, 0));
	table->philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_times = ft_atoi(av[5]);
	else
		table->must_eat_times = -1;
	if (table->philosophers < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1
		|| (ac == 6 && table->must_eat_times < 1))
		return (exit_error("Invalid arguments", NULL, 0));
	table->finish_flag = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!set_table(&table, ac, av))
		return (1);
	if (!call_philosophers(&table))
		return (1);
	if (!start_padlocks(&table))
		return (1);
	if(!turn_philosophers_in_threads(&table))
		return (1);
	start_dinner_monitor(&table);
}

void	advance_time(t_philo *philo, long long stop)
{
	long long	begin;

	begin = now();
	while (!is_time_to_finish(philo, NO) && (now() - begin) < stop)
		usleep(100);
}

void	print_action(t_philo *philo, const char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_padlock);
	if (!is_time_to_finish(philo, NO))
	{
		time = now() - philo->table->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_padlock);
	if (status[0] == 'f')
		printf("%s\n", FINISH_MSG);
}

long long	now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

int	exit_error(char *msg, t_table *table, int n)
{
	printf("Error: %s\n", msg);
	if (n == 1)
		clean_table(table);
	if (n == 2)
		destroy_padlocks(table);
	if (n == 3)
		finish_dinner(table);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	r;
	int	sg;

	r = 0;
	sg = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sg *= -1;
		s++;
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		else if (*s >= '0' && *s <= '9')
			r = (r * 10) + (*s - '0');
		s++;
	}
	return (sg * r);
}

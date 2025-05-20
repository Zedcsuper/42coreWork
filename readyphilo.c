#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thrd;
}					t_philo;

typedef struct s_table
{
	int				philonum;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meal_limit;
	int				ate_enough;
	int				finish_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	finish_mutex;
}					t_table;

#define TAKING_FORK "has taken a fork"
#define EAT "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIE "died"
#define FINISH "f"
#define FINISH_MSG "All philosophers ate enough"
#define YES 1
#define NO 0

void				think_time(t_philo *philo, long long ms);
void				display_philosopher_status(t_philo *philo, const char *status);
long long			now(void);
int					terminate_on_error(char *msg, t_table *table, int n);
int					ft_atoi(const char *s);
int					isolated_philosopher(t_table *table);
int					start_padlocks(t_table *table);
int					call_philosophers(t_table *table);
int					set_table(t_table *table, int ac, char **av);
int					is_time_to_finish(t_philo *philo, int order);
int					check_philo_status(t_philo *philo);
void				begin_feeding(t_philo *philo);
void				*begin_meal(void *arg);
int					turn_philosophers_in_threads(t_table *table);
void				clean_table(t_table *table);
void				destroy_padlocks(t_table *table);
void				terminate_dinner(t_table *table);
void				begin_dinner_monitor(t_table *table);

int	is_time_to_finish(t_philo *philo, int finish_order)
{
	pthread_mutex_lock(&philo->table->finish_mutex);
	if (finish_order || philo->table->finish_flag)
	{
		if (finish_order)
			philo->table->finish_flag = 1;
		pthread_mutex_unlock(&philo->table->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_mutex);
	return (0);
}

int	check_philo_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (now() - philo->last_eat >= philo->table->die_time)
	{
		display_philosopher_status(philo, DIE);
		is_time_to_finish(philo, YES);
		pthread_mutex_unlock(&philo->table->meal_mutex);
		return (1);
	}
	else if (philo->table->meal_limit > 0
		&& philo->meal_count >= philo->table->meal_limit)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->philonum)
		{
			is_time_to_finish(philo, YES);
			display_philosopher_status(philo, FINISH);
			pthread_mutex_unlock(&philo->table->meal_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (0);
}

void	begin_feeding(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
	}
	display_philosopher_status(philo, TAKING_FORK);
	display_philosopher_status(philo, TAKING_FORK);
	display_philosopher_status(philo, EAT);
	think_time(philo, philo->table->eat_time);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meal_count++;
	philo->last_eat = now();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left_fork]);
}

int	isolated_philosopher(t_table *table)
{
	display_philosopher_status(&table->philo[0], TAKING_FORK);
	think_time(&table->philo[0], table->die_time);
	display_philosopher_status(&table->philo[0], DIE);
	is_time_to_finish(&table->philo[0], YES);
	return (0);
}

// try to make it take t_philo *//
void	*begin_meal(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->table->eat_time * 100);
	while (1)
	{
		if (philo->table->philonum == 1)
		{
			isolated_philosopher(philo->table);
			return (0);
		}
		if (is_time_to_finish(philo, NO))
			return (0);
		begin_feeding(philo);
		display_philosopher_status(philo, SLEEPING);
		think_time(philo, philo->table->sleep_time);
		display_philosopher_status(philo, THINKING);
		if (philo->table->philonum % 2 != 0)
			think_time(philo, philo->table->eat_time / 2);
	}
	return (0);
}

void	clean_table(t_table *table)
{
	free(table->philo);
	free(table->fork_mutex);
}

void	destroy_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
		pthread_mutex_destroy(&table->fork_mutex[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->finish_mutex);
}

void	terminate_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
		pthread_join(table->philo[i].thrd, NULL);
	destroy_padlocks(table);
}

void	begin_dinner_monitor(t_table *table)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = -1;
		table->ate_enough = 0;
		{
			while (++i < table->philonum)
			{
				if (continue_flag && check_philo_status(&table->philo[i]))
					continue_flag = 0;
			}
			usleep(10);
		}
	}
	terminate_dinner(table);
}

int	turn_philosophers_in_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
	{
		if (pthread_create(&table->philo[i].thrd, NULL, begin_meal,
				&table->philo[i]))
			return (terminate_on_error("Couldn't create thread", table, 3));
	}
	return (1);
}

int	start_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL))
			return (terminate_on_error("Couldn't init fork mutex", table, 2));
	}
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (terminate_on_error("Couldn't init fork mutex", table, 2));
	if (pthread_mutex_init(&table->meal_mutex, NULL))
		return (terminate_on_error("Couldn't init fork mutex", table, 2));
	if (pthread_mutex_init(&table->finish_mutex, NULL))
		return (terminate_on_error("Couldn't init fork mutex", table, 2));
	return (1);
}

int	call_philosophers(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->philonum);
	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->philonum);
	if (!table->philo || !table->fork_mutex)
		return (terminate_on_error("Error", table, 1));
    table->start_time = now();
	while (++i < table->philonum)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philonum;
		table->philo[i].meal_count = 0;
		table->philo[i].last_eat = table->start_time;
		table->philo[i].table = table;
	}
	return (1);
}

int	set_table(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (terminate_on_error("Error", NULL, 0));
	table->philonum = ft_atoi(av[1]);
	table->die_time = ft_atoi(av[2]);
	table->eat_time = ft_atoi(av[3]);
	table->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		table->meal_limit = ft_atoi(av[5]);
	else
		table->meal_limit = -1;
	if (table->philonum < 1 || table->die_time < 1
		|| table->eat_time < 1 || table->sleep_time < 1 || (ac == 6
			&& table->meal_limit < 1))
		return (terminate_on_error("Error", NULL, 0));
	table->finish_flag = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!set_table(&table, ac, av))
		return (1);
	if (!call_philosophers(&table))
		return (1);
	if (!start_padlocks(&table))
		return (1);
	if (!turn_philosophers_in_threads(&table))
		return (1);
	begin_dinner_monitor(&table);
	return (0);
}

void	think_time(t_philo *philo, long long stop)
{
	long long	begin;

	begin = now();
	while (!is_time_to_finish(philo, NO) && (now() - begin) < stop)
		usleep(100);
}

void	display_philosopher_status(t_philo *philo, const char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!is_time_to_finish(philo, NO))
	{
		time = now() - philo->table->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	if (status[0] == 'f')
		printf("%s\n", FINISH_MSG);
}

long long	now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

int	terminate_on_error(char *msg, t_table *table, int n)
{
	// here we should use ft_pustr_fd
	printf("Error: %s\n", msg);
	if (n == 1)
		clean_table(table);
	if (n == 2)
		destroy_padlocks(table);
	if (n == 3)
		terminate_dinner(table);
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
		else if (*s >= '0' || *s <= '9')
			r = (r * 10) + (*s - '0');
		s++;
	}
	return (sg * r);
}

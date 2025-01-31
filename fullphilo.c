# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define ERROR		-1
# define OFLOW		-2
# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define GOOD		3
# define ARGVALUE	4
# define EOL		'\0'

/*
 ** Philosopher struct
 ** Each philospher shoud have the same options: id[pid] number_of_ate[nta]
 ** last_time_ate[lta]
*/

typedef struct s_philo
{
	pthread_mutex_t	eating;
	pthread_t		thd_philo;
	pthread_t		myhem;
	int				pid;
	int				nta;
	int				lf;
	int				rf;
	int				is_eating;
	long long		lta;
	struct s_din	*din_table;
}				t_philo;

/*
 ** Each program should have the same options: number_of_philosophers[nop]
 ** time_to_die[ttd] time_to_eat[tte]
 ** time_to_sleep[tts] [number_of_times_each_philosopher_must_eat[ntpme]]
 ** starting_time[st]
 */

typedef struct s_din
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			**philos;
	long long		st;
	int				death;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				ntpme;
}	t_din;

t_philo	**initialize_philosphers(t_din *din_table);
pthread_mutex_t							*initialize_forks(t_din *din_table);
int		ft_is_number(char *string);
long long			ft_time_in_ms(void);
int		ft_atoi(const char *str);
void	*start_routine(void *data);
void	print_status(t_din *din_table, int pid, char *string);


/*
 ** Mainly check arguments validity and return acceptance
 ** In case of an error a -1 is returned
 */
int	check_arg_validity(int argSize, char **args)
{
	int	i;

	i = 1;
	if (argSize - 1 < ARGVALUE || argSize - 1 > 6)
		return (ERROR);
	while (i < argSize)
	{
		if (args[i][0] == '-' && ft_is_number(args[i]) != GOOD)
			return (ERROR);
		i++;
	}
	return (GOOD);
}

/*
 ** Parse arguments into a valid struct
 ** Which we will use later
 */
t_din	*fill_table(int argSize, char **args)
{
	t_din	*din_table;
	int		counter;

	counter = 1;
	din_table = (t_din *) malloc(sizeof(t_din) * 1);
	if (din_table == NULL)
		return (NULL);
	din_table->nop = ft_atoi(args[counter++]);
	din_table->ttd = ft_atoi(args[counter++]);
	din_table->tte = ft_atoi(args[counter++]);
	din_table->tts = ft_atoi(args[counter++]);
	din_table->ntpme = -1;
	din_table->death = 1;
	if (argSize - 1 == 5)
		din_table->ntpme = ft_atoi(args[counter]);
	din_table->forks = initialize_forks(din_table);
	if (din_table->forks == NULL)
		return (NULL);
	din_table->philos = initialize_philosphers(din_table);
	if (din_table->philos == NULL || din_table->nop == 0)
		return (NULL);
	if (pthread_mutex_init(&din_table->write, 0) != 0)
		return (NULL);
	return (din_table);
}

/*
 ** Mr mayhem check for a reason to kill
 ** one of the philospher either their
 ** time to die or number_of_times_each_philosopher_must_eat
 ** Each philosopher has it's own death master
 */
void	*mr_mayhem(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		if (!philo->is_eating
			&& ft_time_in_ms() - philo->lta >= philo->din_table->ttd)
		{
			pthread_mutex_lock(&philo->eating);
			print_status(philo->din_table, philo->pid, "died\n");
			philo->din_table->death = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->din_table->philos[philo->din_table->nop - 1]->nta
			== philo->din_table->ntpme)
			philo->din_table->death = 0;
		usleep(100);
	}
	return (NULL);
}

/*
 ** Initialize threads and start philospher
 */
int	start_threads(t_din *din_table)
{
	int	i;

	i = 0;
	din_table->st = ft_time_in_ms();
	while (i < din_table->nop)
	{
		din_table->philos[i]->lta = ft_time_in_ms();
		if (pthread_create(&din_table->philos[i]->thd_philo, NULL,
			&start_routine, (void *)din_table->philos[i]) != 0)
			return (ERROR);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < din_table->nop)
	{
		if (pthread_create(&din_table->philos[i]->myhem, NULL, &mr_mayhem,
		(void *)din_table->philos[i]) != 0)
			return (ERROR);
		usleep(100);
		i++;
	}
	while (din_table->death)
		continue ;
	return (GOOD);
}

int	main(int argc, char **argv)
{
	t_din	*din_table;
	int		p_counter;

	p_counter = 0;
	din_table = NULL;
	if (check_arg_validity(argc, argv) != GOOD)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (ERROR);
	}
	din_table = fill_table(argc, argv);
	if (din_table == NULL)
		return (ERROR);
	if (start_threads(din_table) != GOOD)
		return (ERROR);
	return (GOOD);
}

/*
 ** Print status using a write mutex
 ** to avoid other philospher status be scrambled or intertwined
 ** with another philosopher’s status.
 */
void	print_status(t_din *din_table, int pid, char *string)
{
	pthread_mutex_lock(&din_table->write);
	printf("%lld %d %s", ft_time_in_ms() - din_table->st, pid + 1, string);
	if (string[0] != 'd')
		pthread_mutex_unlock(&din_table->write);
}

/*
 ** Philosopher get both forks then start eating
 ** for an amount of time ( tte ).
 */
void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->din_table->forks[philo->lf]);
	print_status(philo->din_table, philo->pid, "taken left fork\n");
	pthread_mutex_lock(&philo->din_table->forks[philo->rf]);
	print_status(philo->din_table, philo->pid, "taken right fork\n");
	pthread_mutex_lock(&philo->eating);
	print_status(philo->din_table, philo->pid, "is eating\n");
	philo->lta = ft_time_in_ms();
	philo->is_eating = 1;
	usleep(philo->din_table->tte * 1000 - 16000);
	while (ft_time_in_ms() - philo->lta < philo->din_table->tte)
		continue ;
	philo->nta++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->din_table->forks[philo->lf]);
	pthread_mutex_unlock(&philo->din_table->forks[philo->rf]);
	return ;
}

/*
 ** Philospher time to sleep routine.
 */
void	sleep_routine(t_philo *philo)
{
	long long	time;

	print_status(philo->din_table, philo->pid, "is sleeping\n");
	time = ft_time_in_ms();
	usleep(philo->din_table->tts * 1000 - 16000);
	while (ft_time_in_ms() - time < philo->din_table->tts)
		continue ;
	return ;
}

/*
 ** Philospher time to think routine
 */
void	think_routine(t_philo *philo)
{
	print_status(philo->din_table, philo->pid, "is thinking\n");
	return ;
}

/*
 ** Routine start here with infinite loop
 ** that includes all routines that philospher must do
 ** which are eat - sleep - think.
 */
void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
		usleep(100);
	}
	return (NULL);
}

int	ft_check(unsigned long pt, int s)
{
	if (pt > 9223372036854775807 && s == -1)
		return (0);
	else if (pt > 2147483647)
		return (OFLOW);
	return (pt * s);
}

int	ft_atoi(const char *str)
{
	unsigned long long int	j;
	unsigned long long int	t_p;
	int						tt;

	tt = 1;
	j = 0;
	t_p = 0;
	while (*str >= 8 && *str <= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		tt = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + j) >= 48 && *(str + j) <= 57)
		t_p = t_p * 10 + (unsigned long long int)(*(str + j++) - '0');
	return (ft_check(t_p, tt));
}

/* Mainly check if the in string
 ** doesn't contain any ascii than numbers
 */
int	ft_is_number(char *string)
{
	int	i;

	i = 0;
	while (string[i] != EOL)
	{
		if (string[i] <= '0' || string[i] >= '9')
			return (ERROR);
		i++;
	}
	return (GOOD);
}

/*
 ** Get the current time in ms
 */
long long	ft_time_in_ms(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

/*
 ** Initialize philosophers struct
 */
t_philo	**initialize_philosphers(t_din *din_table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * din_table->nop + 1);
	if (philos == NULL)
		return (NULL);
	while (i < din_table->nop)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (philos[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(&philos[i]->eating, 0) != 0)
			return (NULL);
		philos[i]->din_table = din_table;
		philos[i]->pid = i;
		philos[i]->is_eating = 0;
		philos[i]->nta = 0;
		philos[i]->lf = i;
		philos[i]->rf = (i + 1) % philos[i]->din_table->nop;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*initialize_forks(t_din *din_table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (din_table->nop == OFLOW || din_table->ttd == OFLOW
		|| din_table->tte == OFLOW || din_table->tts == OFLOW
		|| din_table->ntpme == OFLOW)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (NULL);
	}
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * din_table->nop);
	if (forks == NULL)
		return (NULL);
	while (i < din_table->nop)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

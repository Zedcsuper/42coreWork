#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RED "\033[31mm"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CLEAR "\033[0m"
#define BOLD "\033[1m"

typedef struct	s_stats
{
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals;
	int		stop;
	long int	start_t;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	*fork;
}			t_stats;

typedef struct	s_philo
{
	int		id;
	int		meals_eaten;
	long int	last_meal;
	pthread_t	thread_id;
	t_stats		*pa;
}			t_philo;

long int	get_time(void)
{
	struct timeval	current_time;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(50);
}

void	print_status(char *str, t_philo *ph)
{
	long int time = get_time() - ph->pa->start_t;
	pthread_mutex_lock(&ph->pa->write_mutex);
	if (!ph->pa->stop)
		printf(BOLD"%ld ms "CLEAR"philo %d %s", time, ph->id, str);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	*monitor(void *data)
{
	t_philo *ph = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&ph->pa->dead_mutex);
		if (ph->pa->stop)
		{
			pthread_mutex_unlock(&ph->pa->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&ph->pa->dead_mutex);
		pthread_mutex_lock(&ph->pa->write_mutex);
		if (get_time() - ph->last_meal >= ph->pa->time_to_die)
		{
			pthread_mutex_lock(&ph->pa->dead_mutex);
			ph->pa->stop = 1;
			pthread_mutex_unlock(&ph->pa->dead_mutex);
			printf(BOLD"%ld ms "CLEAR RED"philo %d died\n"CLEAR, get_time() - ph->pa->start_t, ph->id);
			pthread_mutex_unlock(&ph->pa->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->pa->write_mutex);
		usleep(250);
	}
	return (NULL);
}

void	*philo_life(void *data)
{
	t_philo *ph = (t_philo *)data;
	int left_fork = ph->id - 1;
	int right_fork = ph->id % ph->pa->philos;
	while (1)
	{
		pthread_mutex_lock(&ph->pa->dead_mutex);
		if (ph->pa->stop)
		{
			pthread_mutex_unlock(&ph->pa->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&ph->pa->dead_mutex);
		if (left_fork < right_fork)
		{
			pthread_mutex_lock(&ph->pa->fork[left_fork]);
			print_status(GREEN"has taken fork\n"CLEAR, ph);
			pthread_mutex_lock(&ph->pa->fork[right_fork]);
			print_status(GREEN"has taken fork\n"CLEAR, ph);
		}
		else
		{
			pthread_mutex_lock(&ph->pa->fork[right_fork]);
			print_status(GREEN"has taken a fork\n"CLEAR, ph);
			pthread_mutex_lock(&ph->pa->fork[left_fork]);
			print_status(GREEN"has taken a fork\n"CLEAR, ph);
		}
		//EAT
		print_status(PURPLE"is eating\n"CLEAR, ph);
		pthread_mutex_lock(&ph->pa->write_mutex);
		ph->last_meal = get_time();
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->pa->write_mutex);
		ft_usleep(ph->pa->time_to_sleep);
		// put down fork
		pthread_mutex_unlock(&ph->pa->fork[left_fork]);
		pthread_mutex_unlock(&ph->pa->fork[right_fork]);
		//sleep
		print_status(BLUE"is sleeping\n"CLEAR, ph);
		ft_usleep(ph->pa->time_to_sleep);
		// think
		print_status(YELLOW"is thinking\n"CLEAR, ph);
	}
	return (NULL);
}

int	initialize(t_stats *stats, t_philo **philos)
{
	int	i;
	stats->start_t = get_time();
	stats->stop = 0;
	stats->fork = malloc(sizeof(pthread_mutex_t) * stats->philos);
	if (!stats->fork)
		return (0);
	for (i = 0; i < stats->philos; i++)
		pthread_mutex_init(&stats->fork[i], NULL);
	*philos = malloc(sizeof(t_philo) * stats->philos);
	if (!*philos)
		return (0);
	for (i = 0; i < stats->philos; i++)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = stats->start_t;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].pa = stats;
	}
	return (1);
}

void	cleanup(t_stats *stats, t_philo *philos)
{
	int	i;
	for (i = 0; i < stats->philos; i++)
		pthread_mutex_destroy(&stats->fork[i]);
	free(stats->fork);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_stats	stats;
	t_philo	*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int				i;


	if (argc != 5 && argc != 6)
		return (printf("Usage: %s [number_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [meals]\n", argv[0]), 1);
	stats.philos = atoi(argv[1]);
	stats.time_to_die = atoi(argv[2]);
	stats.time_to_eat = atoi(argv[3]);
	stats.time_to_sleep = atoi(argv[4]);
	stats.meals = (argc == 6) ? atoi(argv[5]) : -1;
	if (stats.philos < 1 || stats.time_to_die < 0 || stats.time_to_eat < 0 || stats.time_to_sleep < 0 || (argc == 6 && stats.meals < 0))
		return (printf("Invalid argument\n"), 1);
	if (!initialize(&stats, &philos))
		return (printf("Initilization failed\n"), 1);
	
	threads = malloc(sizeof(pthread_t) * stats.philos);
	if (!threads)
		return (printf("Thread allocation failed\n"), 1);
	pthread_mutex_init(&stats.write_mutex, NULL);
	pthread_mutex_init(&stats.dead_mutex, NULL);
	for (i = 0; i < stats.philos; i++)
		pthread_create(&threads[i], NULL, philo_life, &philos[i]);
	pthread_create(&monitor_thread, NULL, monitor, &philos[0]);
	for (i = 0; i < stats.philos; i++)
		pthread_join(threads[i], NULL);
	pthread_join(monitor_thread, NULL);
	cleanup(&stats, philos);
	free(threads);
	return (0);
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_philo
{
	int			id;
	pthread_mutex_t	*forks;
}			t_philo;

void	*routine(void	*arg)
{
	t_philo *data = (t_philo *)arg;
	int	i = data->id;
	pthread_mutex_t *forks = data->forks;

	while (1)
	{
		pthread_mutex_lock(&forks[i]);
		printf("%d taking right fork\n", i);
		pthread_mutex_lock(&forks[(i + 4) % 5]);
		printf("%d taking left fork\n", i );
		pthread_mutex_unlock(&forks[i]);
		pthread_mutex_unlock(&forks[(i + 4) % 5]);
		printf("%d is now thinking\n", i);
		usleep(450);
		printf("%d is now sleeping\n", i);
		usleep(450);
	}
	return (NULL);
}
		



int	main()
{
	pthread_t	philo[5];
	pthread_mutex_t	forks[5];
	t_philo		data[5];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 5)
	{
		pthread_mutex_init(&forks[j], NULL);
		j++;
	}

	while (i < 5)
	{
		data[i].id = i;
		data[i].forks = forks;
		pthread_create(&philo[i], NULL, routine, &data[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	j = 0;
	while (j < 5)
	{
		pthread_mutex_destroy(&forks[j]);
		j++;
	}	
	return (0);
}	

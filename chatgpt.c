#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>     // for memset

typedef struct s_data t_data;

typedef struct s_philo
{
    int         id;
    int         number_eaten;
    int         alive;
    int         ff; // first fork
    int         sf; // second fork
    t_data      *data;
    pthread_t   thread;
}   t_philo;

struct s_data
{
    int                 nop; // number_of_philosophers
    int                 ttd; // time_to_die
    int                 tte; // time_to_eat
    int                 tts; // time_to_sleep
    int                 noe; // number_of_times_each_philosopher_must_eat
    t_philo             *philo;
    pthread_mutex_t     *forks;
    pthread_mutex_t     write;
    // If you want a death mutex, do:
    // pthread_mutex_t     death;
};

static void print_status(t_data *data, int philo_id, const char *msg)
{
    pthread_mutex_lock(&data->write);
    printf("%d %s\n", philo_id, msg);
    pthread_mutex_unlock(&data->write);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        // Pick up forks
        if (philo->id % 2 == 1)
        {
            pthread_mutex_lock(&philo->data->forks[philo->ff]);
            print_status(philo->data, philo->id, "has taken a fork");
            pthread_mutex_lock(&philo->data->forks[philo->sf]);
            print_status(philo->data, philo->id, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&philo->data->forks[philo->sf]);
            print_status(philo->data, philo->id, "has taken a fork");
            pthread_mutex_lock(&philo->data->forks[philo->ff]);
            print_status(philo->data, philo->id, "has taken a fork");
        }

        // Eat
        print_status(philo->data, philo->id, "is eating");
        usleep(philo->data->tte * 1000);
        philo->number_eaten++;

        // Put down forks
        pthread_mutex_unlock(&philo->data->forks[philo->ff]);
        pthread_mutex_unlock(&philo->data->forks[philo->sf]);

        // Sleep
        print_status(philo->data, philo->id, "is sleeping");
        usleep(philo->data->tts * 1000);

        // Think
        print_status(philo->data, philo->id, "is thinking");

        // Very rough: no check to break out, no death check, etc.
        // In a real solution, you’d track last_meal_time and check for
        // philosopher death or for number_of_times_each_philosopher_must_eat.
    }
    return NULL;
}

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        write(2, "Usage: ./philo nop ttd tte tts [noe]\n", 36);
        return (1);
    }

    t_data  data;
    memset(&data, 0, sizeof(t_data));

    // Parse arguments
    data.nop = atoi(av[1]);
    data.ttd = atoi(av[2]);
    data.tte = atoi(av[3]);
    data.tts = atoi(av[4]);
    if (ac == 6)
        data.noe = atoi(av[5]);
    else
        data.noe = -1;  // if not provided

    // Allocate forks
    data.forks = malloc(sizeof(pthread_mutex_t) * data.nop);
    if (!data.forks)
        return (write(2, "Malloc error\n", 13), 1);

    // Initialize mutexes
    pthread_mutex_init(&data.write, NULL);
    // If you want a death mutex, declare it as non-pointer and init:
    // pthread_mutex_init(&data.death, NULL);

    // Initialize each fork
    for (int i = 0; i < data.nop; i++)
        pthread_mutex_init(&data.forks[i], NULL);

    // Create an array of philosophers
    t_philo philos[data.nop];
    memset(philos, 0, sizeof(philos));

    // Fill philosopher data
    for (int i = 0; i < data.nop; i++)
    {
        philos[i].id = i + 1;
        philos[i].number_eaten = 0;
        philos[i].alive = 1;
        philos[i].ff = i;
        philos[i].sf = (i + 1) % data.nop;
        philos[i].data = &data;
    }

    // Create threads
    for (int i = 0; i < data.nop; i++)
        pthread_create(&philos[i].thread, NULL, routine, &philos[i]);

    // In a real solution, you’d usually join or detach,
    // plus have some mechanism to exit the simulation.
    // Here, let’s just join so the main() doesn’t finish immediately:
    for (int i = 0; i < data.nop; i++)
        pthread_join(philos[i].thread, NULL);

    // Cleanup
    free(data.forks);
    return 0;
}


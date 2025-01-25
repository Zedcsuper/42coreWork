#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5
#define TIME_TO_DIE 10000 // Time to die in milliseconds

typedef struct s_philo {
    int id;
    long long last_meal_time;
    pthread_mutex_t *forks;
    pthread_mutex_t *status_mutex;
    int *is_alive;
} t_philo;

long long get_time_in_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *monitor(void *arg) {
    t_philo *data = (t_philo *)arg;
    while (1) {
        pthread_mutex_lock(data->status_mutex);
        if (*(data->is_alive) == 0) {
            pthread_mutex_unlock(data->status_mutex);
            break;
        }
        if (get_time_in_ms() - data->last_meal_time > TIME_TO_DIE) {
            printf("Philosopher %d died\n", data->id);
            *(data->is_alive) = 0;
        }
        pthread_mutex_unlock(data->status_mutex);
        usleep(1000); // Check every 1 ms
    }
    return NULL;
}

void *routine(void *arg) {
    t_philo *data = (t_philo *)arg;
    int i = data->id;
    pthread_mutex_t *forks = data->forks;

    while (1) {
        pthread_mutex_lock(data->status_mutex);
        if (*(data->is_alive) == 0) {
            pthread_mutex_unlock(data->status_mutex);
            break;
        }
        pthread_mutex_unlock(data->status_mutex);

        // Pick up forks
        if (i % 2 == 0) {
            pthread_mutex_lock(&forks[i]);
            printf("%d taking right fork\n", i);
            pthread_mutex_lock(&forks[(i + 1) % NUM_PHILOSOPHERS]);
            printf("%d taking left fork\n", i);
        } else {
            pthread_mutex_lock(&forks[(i + 1) % NUM_PHILOSOPHERS]);
            printf("%d taking left fork\n", i);
            pthread_mutex_lock(&forks[i]);
            printf("%d taking right fork\n", i);
        }

        // Eating
        printf("%d is now eating\n", i);
        data->last_meal_time = get_time_in_ms();
        usleep(1000 * 500); // Simulate eating

        // Put down forks
        pthread_mutex_unlock(&forks[i]);
        pthread_mutex_unlock(&forks[(i + 1) % NUM_PHILOSOPHERS]);

        // Thinking
        printf("%d is now thinking\n", i);
        usleep(1000 * 500); // Simulate thinking

        // Sleeping
        printf("%d is now sleeping\n", i);
        usleep(1000 * 500); // Simulate sleeping
    }
    return NULL;
}

int main() {
    pthread_t philo[NUM_PHILOSOPHERS];
    pthread_t monitors[NUM_PHILOSOPHERS];
    pthread_mutex_t forks[NUM_PHILOSOPHERS];
    pthread_mutex_t status_mutex;
    t_philo data[NUM_PHILOSOPHERS];
    int i;
    int is_alive = 1;

    pthread_mutex_init(&status_mutex, NULL);

    // Initialize forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        data[i].id = i;
        data[i].last_meal_time = get_time_in_ms();
        data[i].forks = forks;
        data[i].status_mutex = &status_mutex;
        data[i].is_alive = &is_alive;
        pthread_create(&philo[i], NULL, routine, &data[i]);
        pthread_create(&monitors[i], NULL, monitor, &data[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philo[i], NULL);
        pthread_join(monitors[i], NULL);
    }

    // Destroy forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&status_mutex);

    return 0;
}
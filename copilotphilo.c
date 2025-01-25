#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef struct s_philo {
    int id;
    pthread_mutex_t *forks;
} t_philo;

void *routine(void *arg) {
    t_philo *data = (t_philo *)arg;
    int i = data->id;
    pthread_mutex_t *forks = data->forks;

    while (1) {
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
    pthread_mutex_t forks[NUM_PHILOSOPHERS];
    t_philo data[NUM_PHILOSOPHERS];
    int i;

    // Initialize forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        data[i].id = i;
        data[i].forks = forks;
        pthread_create(&philo[i], NULL, routine, &data[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philo[i], NULL);
    }

    // Destroy forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
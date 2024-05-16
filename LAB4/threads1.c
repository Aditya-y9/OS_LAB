#include <pthread.h> // for pthread_create, pthread_join, pthread_exit
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for clock_gettime

long long sum; /* use a larger data type */
pthread_mutex_t sum_mutex;  /* mutex to protect the critical section */

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
    struct timespec start, end; // timespec is a struct with tv_sec and tv_nsec
    double cpu_time;

    pthread_t tid;       /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    if (argc != 2)
    {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }

    if (atoll(argv[1]) < 0)
    {
        fprintf(stderr, "%lld must be >= 0\n", atoll(argv[1])); /* use %lld for long long */
        return -1;
    }

    /* Initialize the mutex */
    pthread_mutex_init(&sum_mutex, NULL);

    /* get the default attributes */
    pthread_attr_init(&attr);

    clock_gettime(CLOCK_MONOTONIC, &start); // Record the start time

    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);

    /* wait for the thread to exit */
    pthread_join(tid, NULL); // we join the thread to wait for it to finish

    clock_gettime(CLOCK_MONOTONIC, &end); // Record the end time

    /* Destroy the mutex */
    pthread_mutex_destroy(&sum_mutex);

    // Calculate the CPU time in seconds
    cpu_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("sum = %lld\n", sum); /* use %lld for long long */
    printf("Computation Time: %lf seconds\n", cpu_time);

    return 0;
}

/* The thread will begin control in this function */
void *runner(void *param)
{
    long long i, upper = atoll(param); /* use %lld for long long */

    for (i = 1; i <= upper; i++) {
        /* Lock the mutex before updating the sum */
        pthread_mutex_lock(&sum_mutex);
        sum += i;
        /* Unlock the mutex after updating the sum */
        pthread_mutex_unlock(&sum_mutex);
    }

    pthread_exit(0);
}


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long sum; /* use a larger data type */
pthread_mutex_t sum_mutex; /* mutex to protect the critical section */

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{

    struct timespec start, end;
    double cpu_time;

    pthread_t *tid;       /* the thread identifiers */
    pthread_attr_t attr;  /* set of thread attributes */
    int num_threads;

    if (argc != 3)
    {
        fprintf(stderr, "usage: a.out <integer value> <num_threads>\n");
        return -1;
    }

    long long upper = atoll(argv[1]); /* use %lld for long long */
    num_threads = atoi(argv[2]);

    if (upper < 0 || num_threads <= 0)
    {
        fprintf(stderr, "Both integer value and num_threads must be positive\n");
        return -1;
    }

    sum = 0; // Initialize sum to zero

    /* Initialize the mutex */
    pthread_mutex_init(&sum_mutex, NULL);

    /* get the default attributes */
    pthread_attr_init(&attr);

    tid = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

    clock_gettime(CLOCK_MONOTONIC, &start); // Record the start time

    /* create the threads */
    for (int i = 0; i < num_threads; i++)
    {
        long long thread_lower = (i * upper) / num_threads + 1;
        long long thread_upper = ((i + 1) * upper) / num_threads;

        long long *thread_args = malloc(2 * sizeof(long long));
        thread_args[0] = thread_lower;
        thread_args[1] = thread_upper;

        pthread_create(&tid[i], &attr, runner, thread_args);
    }

    /* wait for the threads to exit */
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end); // Record the end time

    /* Destroy the mutex */
    pthread_mutex_destroy(&sum_mutex);

    // Calculate the CPU time in seconds
    cpu_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Hey there, I am using %d number of threads for computation\n", num_threads);
    printf("sum = %lld\n", sum); /* use %lld for long long */
    printf("Computation Time: %lf seconds\n", cpu_time);

    free(tid);

    return 0;
}

/* The thread will begin control in this function */
void *runner(void *param)
{
    long long thread_lower = ((long long *)param)[0];
    long long thread_upper = ((long long *)param)[1];
    long long thread_sum = 0;

    for (long long i = thread_lower; i <= thread_upper; i++)
    {
        thread_sum += i;
    }

    /* Lock the mutex before updating the sum */
    pthread_mutex_lock(&sum_mutex);
    sum += thread_sum;
    /* Unlock the mutex after updating the sum */
    pthread_mutex_unlock(&sum_mutex);

    free(param); // Free the allocated memory for thread arguments

    pthread_exit(0);
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *generateFibonacci(void *arg) {
    int n = *((int *)arg);

    int fib[n];

    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Store the Fibonacci sequence in shared data (an array)
    int *result = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = fib[i];
    }

    printf("Thread: Calculated Fibonacci sequence up to index %d.\n", n - 1);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_Fibonacci_numbers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer for the number of Fibonacci numbers.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t tid;
    void *result;

    printf("Main: Creating a thread to generate Fibonacci sequence.\n");

    // Create a separate thread to generate Fibonacci sequence
    if (pthread_create(&tid, NULL, generateFibonacci, &n) != 0) {
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }

    printf("Main: Waiting for the thread to finish.\n");

    // Wait for the thread to finish
    if (pthread_join(tid, &result) != 0) {
        perror("pthread_join error");
        exit(EXIT_FAILURE);
    }

    printf("Main: Thread has finished.\n");

    // Output the generated Fibonacci sequence
    int *fibonacciSequence = (int *)result;
    printf("Main: Fibonacci Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacciSequence[i]);
    }
    printf("\n");

    // Free allocated memory
    free(result);

    return 0;
}


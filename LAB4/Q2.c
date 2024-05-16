#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int n = 0;
    int m = 0;
    pid_t pid;  

    do {
        // Get a positive integer from the user
        printf("Enter a positive number:\n");
        scanf("%d", &m);
    } while (m <= 0);

    pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process\n");
        printf("Collatz Sequence for %d is computed below:\n", m);

        while (m != 1) {
            if (m % 2 == 0) {
                m = m / 2;
            } else if (m % 2 == 1) {
                m = 3 * m + 1;
            }
            printf("%d ", m);
        }

        printf("Child process is completed\n");
    } else {
        // Parent process
        printf("Parent is waiting\n");
        wait(NULL); // parent calls wait(NULL) to wait for the child to finish where null is the status of the child process
        printf("Parent process is completed\n");
    }

    return 0;
}


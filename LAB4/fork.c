#include <sys/types.h>  // for pid_t
#include <stdio.h> 
#include <unistd.h> // for fork
#include <sys/wait.h> // for wait
#include <stdlib.h> // for exit

int value = 5;

int main() {
    pid_t pid;

    /* fork a child process */
    pid = fork();

    // now, due to the fork, we have two processes running concurrently
    // the child process is an exact copy of the parent process
    // the only difference is the return value of fork
    // the child process gets a return value of 0
    // the parent process gets the process id of the child process

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    } 
    
    else if (pid == 0) { /* child process */
        value += 15;
        printf("Child process is running\n");
        printf("Child process: My PID is %d\n", getpid());
        sleep(10); // Child waits for 10 seconds
        // Child exits immediately, becoming a zombie.
        exit(0);
    } 
    
    else { /* parent process */
        // wait(NULL);
        printf("Parent process: My PID is %d\n", getpid());

        // Introduce a delay to observe the child in the zombie state
        sleep(20);
        system("ps -l");  // Run 'ps -l' to observe the child process
    }

    return 0;
}


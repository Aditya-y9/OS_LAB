#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FRAMES 100

// Structure to represent a frame
typedef struct {
    int page;
    int used;
} Frame;

// Global variables
Frame frames[MAX_FRAMES];
int fault = 0;
int rear = -1;

// Function to generate a random reference string
void* get_input_reference_string(void* length_ptr) {
    int length = *((int*) length_ptr);
    int* reference_string = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        reference_string[i] = rand() % 10;
    }
    return (void*) reference_string;
}

// Function to simulate FIFO page replacement algorithm
void* fifo_page_replacement(void* args) {
    int length = *((int*) args);
    int capacity;
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    int* reference_string = (int*) get_input_reference_string(&length);
    printf("Enter the length of the reference string: %d\n", length);

    printf("\nString|Frame ->\t");
    for (int i = 0; i < capacity; i++) {
        printf("%d ", i);
    }
    printf("Fault\n   ↓\n");

    for (int i = 0; i < length; i++) {
        int page = reference_string[i];
        int found = 0;

        for (int j = 0; j <= rear; j++) {
            if (frames[j].page == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (rear < capacity - 1) {
                frames[++rear].page = page;
            } else {
                for (int j = 0; j < rear; j++) {
                    frames[j].page = frames[j + 1].page;
                }
                frames[rear].page = page;
            }
            fault++;
            printf("   %d\t\t", page);
            for (int j = 0; j <= rear; j++) {
                printf("%d ", frames[j].page);
            }
            printf(" Yes\n");
        } else {
            printf("   %d\t\t", page);
            for (int j = 0; j <= rear; j++) {
                printf("%d ", frames[j].page);
            }
            printf(" No\n");
        }
    }

    printf("\nTotal requests: %d\nTotal Page Faults: %d\nFault Rate: %.2f%%\n", length, fault, (fault / (double) length) * 100);

    free(reference_string);
    return NULL;
}

int main() {
    pthread_t thread;
    int length;
    printf("Enter the length of the reference string: ");
    scanf("%d", &length);

    pthread_create(&thread, NULL, fifo_page_replacement, &length);
    pthread_join(thread, NULL);

    return 0;
}

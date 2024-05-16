#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FRAMES 100

// Global variables
int frames[MAX_FRAMES];
int top = 0;
int fault = 0;

// Function to generate a random reference string
void* get_input_reference_string(void* length_ptr) {
    int length = *((int*) length_ptr);
    int* reference_string = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        reference_string[i] = rand() % 10;
    }
    return (void*) reference_string;
}

// Function to simulate Optimal page replacement algorithm
void* optimal_page_replacement(void* args) {
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

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (top < capacity) {
                frames[top++] = page;
            } else {
                int farthest = i + 1;
                int farthest_index = 0;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < length; k++) {
                        if (reference_string[k] == frames[j]) {
                            break;
                        }
                    }
                    if (k == length) {
                        farthest_index = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        farthest_index = j;
                    }
                }
                frames[farthest_index] = page;
            }
            fault++;
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j]);
            }
            printf(" Yes\n");
        } else {
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j]);
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

    pthread_create(&thread, NULL, optimal_page_replacement, &length);
    pthread_join(thread, NULL);

    return 0;
}

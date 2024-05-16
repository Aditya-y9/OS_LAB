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

// Function to generate a random reference string
void* get_input_reference_string(void* length_ptr) {
    int length = *((int*) length_ptr);
    int* reference_string = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        reference_string[i] = rand() % 10;
    }
    return (void*) reference_string;
}

// Function to simulate LRU page replacement algorithm
void* lru_page_replacement(void* args) {
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

    int* used = (int*) calloc(capacity, sizeof(int));

    for (int i = 0; i < length; i++) {
        int page = reference_string[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j].page == page) {
                found = 1;
                used[j] = i + 1;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (used[j] < used[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index].page = page;
            used[lru_index] = i + 1;
            fault++;
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j].page);
            }
            for (int j = 0; j < capacity - fault; j++) {
                printf(" ");
            }
            printf(" Yes\n");
        } else {
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j].page);
            }
            for (int j = 0; j < capacity - fault; j++) {
                printf(" ");
            }
            printf(" No\n");
        }
    }

    printf("\nTotal requests: %d\nTotal Page Faults: %d\nFault Rate: %.2f%%\n", length, fault, (fault / (double) length) * 100);

    free(reference_string);
    free(used);
    return NULL;
}

int main() {
    pthread_t thread;
    int length;
    printf("Enter the length of the reference string: ");
    scanf("%d", &length);

    pthread_create(&thread, NULL, lru_page_replacement, &length);
    pthread_join(thread, NULL);

    return 0;
}

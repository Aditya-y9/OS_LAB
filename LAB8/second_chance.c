#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FRAMES 100


typedef struct {
    int page;
    int second_chance_bit;
} Frame;


Frame frames[MAX_FRAMES];
int top = 0;
int fault = 0;


void* get_input_reference_string(void* length_ptr) {
    int length = *((int*) length_ptr);
    int* reference_string = (int*) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        reference_string[i] = rand() % 10;
    }
    return (void*) reference_string;
}


void* second_chance_page_replacement(void* args) {
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

        // Check if page already exists in frames
        for (int j = 0; j < top; j++) {
            if (frames[j].page == page) {
                frames[j].second_chance_bit = 1; // Give the page a second chance
                found = 1;
                break;
            }
        }

        if (!found) {
            if (top < capacity) {
                // If there's still space in frames, add the page
                frames[top].page = page;
                frames[top].second_chance_bit = 1; // Give the page a second chance
                top++;
            } else {
                // Find a page to replace
                int replace_index = -1;
                while (1) {
                    if (frames[top % capacity].second_chance_bit == 0) {
                        replace_index = top % capacity;
                        break;
                    } else {
                        frames[top % capacity].second_chance_bit = 0; // Reset second chance bit
                        top++;
                    }
                }
                // Replace the page at replace_index with the new page
                frames[replace_index].page = page;
                frames[replace_index].second_chance_bit = 1; // Give the page a second chance
            }
            fault++;
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j].page);
            }
            printf(" Yes\n");
        } else {
            printf("   %d\t\t", page);
            for (int j = 0; j < capacity; j++) {
                printf("%d ", frames[j].page);
            }
            printf(" No\n");
        }
    }

    printf("\nTotal requests: %d\nTotal Page Faults: %d\nFault Rate: %.2f%%\n", length, fault, (fault / (double)length) * 100.0);



    free(reference_string);
    return NULL;
}

int main() {
    pthread_t thread;
    int length;
    printf("Enter the length of the reference string: ");
    scanf("%d", &length);

    pthread_create(&thread, NULL, second_chance_page_replacement, &length);
    pthread_join(thread, NULL);

    return 0;
}

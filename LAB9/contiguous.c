#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main()
{
    int i, j, k, tot_blocks, n_blocks, n_files, sb[50], l[50];

    clock_t start, end;
    start = clock();
    
    // Prompt the user to enter the total number of blocks
    printf("\n Enter the total number of blocks : ");
    scanf("%d", &tot_blocks);
    
    // Create an array to represent the memory blocks
    int memory[tot_blocks];
    
    // Initialize all memory blocks to -1, indicating they are free
    for (i = 0; i < tot_blocks; i++)
        memory[i] = -1;
    
    // Prompt the user to enter the number of files
    printf(" Enter the number of files : ");
    scanf("%d", &n_files);
    
    // Create arrays to store file allocation information
    bool file_alloc[n_files];
    int alloc_info[n_files];
    
    printf("\n");
    
    // Prompt the user to enter the starting block number and length for each file
    for (i = 0; i < n_files; i++)
    {
        printf(" Enter the starting block number of file %d : ", i + 1);
        scanf("%d", &sb[i]);
        
        printf(" Enter the length of file %d : ", i + 1);
        scanf("%d", &l[i]);
        
        // Adjust the starting block number to 0-based indexing
        sb[i]--;
        
        // Initialize file allocation status and allocation information
        file_alloc[i] = false;
        alloc_info[i] = -1;
    }
    
    // Allocate memory blocks for each file
    for (i = 0; i < n_files; i++)
    {
        j = sb[i];
        alloc_info[i] = j;
        file_alloc[i] = true;
        
        // Check if the starting block is already allocated
        if (memory[j] != -1)
        {
            printf("\n Cannot allocate file %d.", i + 1);
            alloc_info[i] = -1;
            file_alloc[i] = false;
            continue;
        }
        else
        {
            // Check if there is enough contiguous space to allocate the file
            for (j = sb[i]; j < sb[i] + l[i]; j++)
            {
                if (memory[j] != -1)
                {
                    printf("\n Not enough space to allocate file %d.", i + 1);
                    file_alloc[i] = false;
                    
                    // Free the previously allocated blocks
                    for(k = j-1; k >= sb[i]; k--)
                    {
                        memory[k] = -1;
                    }
                    
                    alloc_info[i] = -1;
                    break;
                }
                
                // Allocate the memory block for the file
                memory[j] = i + 1;
            }
        }
    }
    
    // Print the file allocation information
    printf("\n\n File allocation information : ");
    printf("\n File no. Starting block no. Length \n");
    for (i = 0; i < n_files; i++)
    {
        if (file_alloc[i] == true)
        {
            printf(" %d %d %d \n", i + 1, alloc_info[i] + 1, l[i]);
        }
        else if (file_alloc[i] == false)
        {
            printf(" %d Not allocated %d \n", i + 1, l[i]);
        }
    }
    
    // Print the final memory block allocation
    printf("\n");
    for (i = 0; i < tot_blocks; i++)
        printf(" %d ", memory[i]);
    printf("\n");


    end = clock();
    double time_required = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time required: %lf\n", time_required);


    return 0;
}
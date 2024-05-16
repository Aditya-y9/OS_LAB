#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PAGE_SIZE (4 * (1ULL << 10)) // 4KB expressed using bitwise left shift

#define VIRTUAL_MEMORY_SIZE ((1ULL << 48)) // 256TB expressed using bitwise left shift

#define NUMBER_OF_PAGES (VIRTUAL_MEMORY_SIZE / PAGE_SIZE) // Number of pages in virtual memory

#define BITS_FOR_PAGE_NUMBER 52 // (2^64/2^12) = 2^52

#define BITS_FOR_OFFSET 12 // 2^12

int main(int argc, char *argv[]) {

    // Input checker
    // 1st argument is the virtual address
    // 2nd argument is the page size
    if (argc != 2) {
        printf("Input error: Please provide a single argument as the virtual address\n");
        return 1;
    }

    // Convert the command-line argument to an unsigned long integer
    unsigned long long VA = strtoull(argv[1], NULL, 10);

    // Calculate the page number by dividing the virtual address by the page size
    unsigned long long Pg_no = VA / PAGE_SIZE;

    // Calculate the offset by taking the remainder of the virtual address divided by the page size
    unsigned long long offset = VA % PAGE_SIZE;

    // Print the virtual address, page number, and offset in binary format
    printf("----------------------------------------\n");
    printf("Virtual Address is of size 64 bits\n");
    printf("Virtual Address: %llu (binary: ", VA);
    for (int i = 47; i >= 0; i--) {
        printf("%llu", (VA >> i) & 1);
    }
    printf(")\n");
    printf("----------------------------------------\n");
    
    printf("Page size is of size %d bits\n", BITS_FOR_PAGE_NUMBER);      
    printf("Page Number: %llu (binary: ", Pg_no);
    for (int i = BITS_FOR_PAGE_NUMBER - 1; i >= 0; i--) {
        printf("%llu", (Pg_no >> i) & 1);
    }
    printf(")\n");
    printf("----------------------------------------\n");

    printf("Offset is of size %d bits\n", BITS_FOR_OFFSET);
    printf("Offset: %llu (binary: ", offset);
    for (int i = BITS_FOR_OFFSET - 1; i >= 0; i--) {
        printf("%llu", (offset >> i) & 1);
    }
    printf(")\n");
    printf("----------------------------------------\n");

    printf("Thank you for using the program!\n");
    printf("----------------------------------------\n");

    return 0;
}

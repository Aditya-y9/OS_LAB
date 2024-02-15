#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Macro for handling errors and printing an error message
#define DIE(message)                    \
    do                                  \
    {                                   \
        perror(message);                \
        exit(EXIT_FAILURE);             \
    } while (0)

#endif /* COMMON_H */

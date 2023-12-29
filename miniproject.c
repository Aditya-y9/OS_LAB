#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}};

bool verification[11];
int auxSquares = 2;

typedef struct
{
    int row;
    int column;
} parameter;

pthread_t columns, rows, first_square, second_square, third_square,
    fourth_square, fifth_square, sixth_square, seventh_square, eighth_square, ninth_square;

void *traverseColumn(void *params)
{
    parameter *column = (parameter *)params;
    int initialColumn = column->column;
    int initialRow = column->row;

    for (int i = initialColumn; i < 9; i++)
    {
        int col[9] = {0};
        for (int j = initialRow; j < 9; j++)
        {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0)
            {
                col[aux - 1] = aux;
            }
            else if (aux <= 0)
            {
                verification[0] = 0;
                printf("Sorry, there is an invalid number in column [%d].\n", j + 1);
                pthread_exit(0);
            }
            else
            {
                verification[0] = 0;
                printf("Sorry, there is a repeated number in column [%d].\n", j + 1);
                pthread_exit(0);
            }
        }
    }
    verification[0] = 1;
    pthread_exit(0);
}

void *traverseRow(void *params)
{
    parameter *row = (parameter *)params;
    int initialColumn = row->column;
    int initialRow = row->row;

    for (int i = initialColumn; i < 9; i++)
    {
        int fil[9] = {0};
        for (int j = initialRow; j < 9; j++)
        {
            int aux = sudoku[i][j];
            if (fil[aux - 1] == 0 && aux > 0)
            {
                fil[aux - 1] = aux;
            }
            else if (aux <= 0)
            {
                verification[0] = 0;
                printf("Sorry, there is an invalid number in row [%d].\n", i + 1);
                pthread_exit(0);
            }
        }
    }
    verification[1] = 1;
    pthread_exit(0);
}
void *traverseBlock(void *parameters)
{

    parameter *block = (parameter *)parameters;
    int rowInitial = block->row;
    int columnInitial = block->column;
    int square[9] = {0};

    for (int i = rowInitial; i < rowInitial + 3; ++i)
    {
        for (int j = columnInitial; j < columnInitial + 3; ++j)
        {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0)
            {
                square[aux - 1] = aux;
            }
            else
            {
                verification[auxSquares] = 0;
                auxSquares++;
                pthread_exit(0);
            }
        }
    }
    verification[auxSquares] = 1;
    auxSquares++;
    pthread_exit(0);
}

int main()
{

    /*Asignamos (reservamos) cada parameter en memoria y asi poder pasar más fácil la ubicacion del Struct con &a*/
    parameter *verificarrows = (parameter *)malloc(sizeof(parameter));
    verificarrows->row = 0;
    verificarrows->column = 0;

    parameter *verificarcolumns = (parameter *)malloc(sizeof(parameter));
    verificarcolumns->row = 0;
    verificarcolumns->column = 0;

    parameter *block1 = (parameter *)malloc(sizeof(parameter));
    block1->row = 0;
    block1->column = 0;

    parameter *block2 = (parameter *)malloc(sizeof(parameter));
    block2->row = 0;
    block2->column = 3;

    parameter *block3 = (parameter *)malloc(sizeof(parameter));
    block3->row = 0;
    block3->column = 6;

    parameter *block4 = (parameter *)malloc(sizeof(parameter));
    block4->row = 3;
    block4->column = 0;

    parameter *block5 = (parameter *)malloc(sizeof(parameter));
    block5->row = 3;
    block5->column = 3;

    parameter *block6 = (parameter *)malloc(sizeof(parameter));
    block6->row = 3;
    block6->column = 6;

    parameter *block7 = (parameter *)malloc(sizeof(parameter));
    block7->row = 6;
    block7->column = 0;

    parameter *block8 = (parameter *)malloc(sizeof(parameter));
    block8->row = 6;
    block8->column = 3;

    parameter *block9 = (parameter *)malloc(sizeof(parameter));
    block9->row = 6;
    block9->column = 6;

    pthread_create(&columns, NULL, traverseColumn, (void *)verificarcolumns);
    pthread_create(&rows, NULL, traverseRow, (void *)verificarrows);
    pthread_create(&first_square, NULL, traverseBlock, (void *)block1);
    pthread_create(&second_square, NULL, traverseBlock, (void *)block2);
    pthread_create(&third_square, NULL, traverseBlock, (void *)block3);
    pthread_create(&fourth_square, NULL, traverseBlock, (void *)block4);
    pthread_create(&fifth_square, NULL, traverseBlock, (void *)block5);
    pthread_create(&sixth_square, NULL, traverseBlock, (void *)block6);
    pthread_create(&seventh_square, NULL, traverseBlock, (void *)block7);
    pthread_create(&eighth_square, NULL, traverseBlock, (void *)block8);
    pthread_create(&ninth_square, NULL, traverseBlock, (void *)block9);

    pthread_join(columns, NULL);
    pthread_join(rows, NULL);
    pthread_join(first_square, NULL);
    pthread_join(second_square, NULL);
    pthread_join(third_square, NULL);
    pthread_join(fourth_square, NULL);
    pthread_join(fifth_square, NULL);
    pthread_join(sixth_square, NULL);
    pthread_join(seventh_square, NULL);
    pthread_join(eighth_square, NULL);
    pthread_join(ninth_square, NULL);

    for (int k = 0; k < 11; ++k)
    {
        if (!verification[k])
        {
            printf("\nWhoops... The Sudoku was NOT solved.\n");
            exit(0);
        }
    }
    printf("\nYay!!! Congratulations, the Sudoku was solved.\n");
    return 0;
}

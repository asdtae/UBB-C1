/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) Conway's Game of Life rules
 *      (2) ANSI C Standard Library
 *      (3) gemini - implementation logic
 */

#define DEBUG 0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


typedef struct
{
    bool isAlive;
    bool willBeAlive;
} Cell;

void writeStr(const char *msg)
{
    printf("%s", msg);
}

void writeInt(long long int num)
{
    printf("%lld\n", num);
}

bool char2lli(const char *chr, long long int *x)
{
    char *endptr = NULL;

    errno = 0;
    *x = strtoll(chr, &endptr, 10);

    if (chr == endptr || ((errno == ERANGE) && (*x == LLONG_MAX || *x == LLONG_MIN)) || *endptr != '\0')
    {
        return false;
    }

    return true;
}

Cell** initGrid(long long int rows, long long int cols)
{
    Cell **grid = (Cell**)malloc(rows * sizeof(Cell*));
    if (grid == NULL) return NULL;

    for (long long int i = 0; i < rows; i++)
    {
        grid[i] = (Cell*)malloc(cols * sizeof(Cell));
        if (grid[i] == NULL) return NULL;

        for (long long int j = 0; j < cols; j++)
        {
            grid[i][j].isAlive = false;
            grid[i][j].willBeAlive = false;
        }
    }
    return grid;
}

void printGrid(Cell **grid, long long int rows, long long int cols)
{
    for (long long int i = 0; i < rows; i++)
    {
        for (long long int j = 0; j < cols; j++)
        {
            if (grid[i][j].isAlive)
            {
                printf("%c", (unsigned char)219);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


bool loadState(FILE* input, Cell **grid, long long int rows, long long int cols)
{
    long long int r, c;
    while (fscanf(input, "%lld %lld", &r, &c) == 2)
    {
        if (r >= 1 && r <= rows && c >= 1 && c <= cols)
        {
            grid[r-1][c-1].isAlive = true;
        }
    }
    return true;
}

int countNeighbors(Cell **grid, long long int r, long long int c, long long int rows, long long int cols)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;

            long long int nr = (r + i + rows) % rows;
            long long int nc = (c + j + cols) % cols;

            if (grid[nr][nc].isAlive)
            {
                count++;
            }
        }
    }
    return count;
}

void processSimulation(Cell **grid, long long int rows, long long int cols)
{
    for (long long int i = 0; i < rows; i++)
    {
        for (long long int j = 0; j < cols; j++)
        {
            int neighbors = countNeighbors(grid, i, j, rows, cols);
            bool alive = grid[i][j].isAlive;

            if (alive)
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    grid[i][j].willBeAlive = false;
                }
                else
                {
                    grid[i][j].willBeAlive = true;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    grid[i][j].willBeAlive = true;
                }
                else
                {
                    grid[i][j].willBeAlive = false;
                }
            }
        }
    }

    for (long long int i = 0; i < rows; i++)
    {
        for (long long int j = 0; j < cols; j++)
        {
            grid[i][j].isAlive = grid[i][j].willBeAlive;
        }
    }
}

void freeGrid(Cell **grid, long long int rows)
{
    for (long long int i = 0; i < rows; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

int main(int argc, const char *argv[])
{
    // INIT
    FILE* inFile = fopen("input.txt", "r");

    // VALIDATE
    if (argc != 4)
    {
        writeStr("hiba");
        if (inFile) fclose(inFile);
        exit(1);
    }

    long long int rows = 0;
    long long int cols = 0;
    long long int iters = 0;

    if (char2lli(argv[1], &rows) == false ||
        char2lli(argv[2], &cols) == false ||
        char2lli(argv[3], &iters) == false)
    {
        writeStr("hiba");
        if (inFile) fclose(inFile);
        exit(1);
    }

    if (rows <= 0 || cols <= 0 || iters < 0)
    {
        writeStr("hiba");
        if (inFile) fclose(inFile);
        exit(1);
    }

    if (inFile == NULL)
    {
        writeStr("hiba");
        exit(2);
    }

    // SETUP
    Cell **grid = initGrid(rows, cols);
    if (grid == NULL)
    {
        writeStr("hiba");
        fclose(inFile);
        exit(3);
    }

    // Read
    loadState(inFile, grid, rows, cols);

    // Sim
    writeInt(0);
    printGrid(grid, rows, cols);

    for (long long int k = 1; k <= iters; k++)
    {
        processSimulation(grid, rows, cols);

        writeInt(k);
        printGrid(grid, rows, cols);
    }

    // CLEANUP
    freeGrid(grid, rows);
    fclose(inFile);

    return 0;
}
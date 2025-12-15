/*
*  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) error() from L3/mrim2553.c
 *      (2) fin() | fout() from L3/mrim2553.c
 *      (3) 9 - Dinamikus memóriakezelés és Pointerek II.pdf
 *      (4) Gemini - debug/test case
 */

#define DEBUG 0
#define INP_SIZE 100
#define OUTP_SIZE 100
#define MAX_STEPS 1000
#define SIM_YEARS 100

#define Black "\033[30m"
#define Red "\033[31m"
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Blue "\033[34m"
#define Magenta "\033[35m"
#define Cyan "\033[36m"
#define White "\033[37m"

#define Bright_Black "\033[90m"
#define Bright_Red "\033[91m"
#define Bright_Green "\033[92m"
#define Bright_Yellow "\033[93m"
#define Bright_Blue "\033[94m"
#define Bright_Magenta "\033[95m"
#define Bright_Cyan "\033[96m"
#define Bright_White "\033[97m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

int fin(FILE* file)
{
    int numb = 0;
    fscanf(file,"%d",&numb);

    return numb;
}

int** read(FILE* NetFile, int *size)
{
    int src, dest, weight;
    int **p = 0;

    while(fscanf(NetFile,"%d %d %d",&src,&dest,&weight) == 3)
    {
        #if DEBUG
        printf("%s%d %d %s%d%s\n",Bright_Cyan, src, dest, Bright_Magenta, weight, White);
        #endif

        int maxi = (src > dest) ? src : dest;
        int newSize = maxi + 1;

        if (newSize > *size)
        {
            int **tmp = (int **)realloc(p, newSize * sizeof(int*));
            if(tmp == NULL) { perror("Memory allocation error"); exit(1); }
            p = tmp;

            for(int i = 0; i < newSize; i++)
            {
                if(i < *size)
                {
                    int *tmpRow = (int *)realloc(p[i], newSize * sizeof(int));
                    if(tmpRow == NULL) { perror("Memory allocation error"); exit(1); }
                    p[i] = tmpRow;

                    memset(p[i] + *size, 0, (newSize - *size) * sizeof(int));
                }
                else
                {
                    p[i] = (int *)calloc(newSize, sizeof(int));
                    if(p[i] == NULL) { perror("Memory allocation error"); exit(1); }
                }
            }

            *size = newSize;
        }

        p[src][dest] = weight;
        p[dest][src] = weight;
    }


    // DEBUG
    #if DEBUG
    printf("   ");
    for(int i = 0; i < *size; i++) printf("%2d ",i);
    printf("\n");

    for(int i = 0; i < *size; i++) {
        printf("%s%2d ",White,i);
        for(int j = 0; j < *size; j++)
            if(p[i][j] == 0) printf("%s%2d ",Bright_Black,p[i][j]);
            else printf("%s%2d ",Bright_Cyan,p[i][j]);
        printf("\n");
    }
    printf("%s\n",White);
    #endif

    return p;
}

int* szomszedNeni(int **p, int size, int currNode, int *count)
{
    int *neighbors = (int*)malloc(size * sizeof(int));
    if(neighbors == NULL) { perror("Memory allocation error"); exit(1); }

    *count = 0;
    for (int i = 0; i < size; i++)
    {
        if(p[currNode][i] > 0)
        {
            neighbors[(*count)++] = i;
        }
    }
    return neighbors;
}

int* santaSim(int **p, int size, int start)
{
    int *res = (int*)calloc(3, sizeof(int));
    if(!res) { perror("Memory allocation error"); exit(1); }

    int *visited = (int*)calloc(size, sizeof(int));
    if (!visited) { perror("Memory allocation error"); exit(1); }

    int currNode = start;
    int count = 0;

    visited[currNode] = 1;
    count++;

    #if DEBUG
    printf("%sStart poz: %d%s\n", Green, start, White);
    #endif

    while(res[0] < MAX_STEPS && count < size)
    {
        int neighbor_count = 0;
        int *neighbors = szomszedNeni(p, size, currNode, &neighbor_count);

        if (neighbor_count == 0)
        {
            #if DEBUG
            printf("%sDead end! Stuck at %d.%s\n", Red, currNode, White);
            #endif

            free(neighbors);
            break;
        }

        int rIndx = rand() % neighbor_count;
        int nextNode = neighbors[rIndx];

        res[1] += p[currNode][nextNode];
        res[0]++;

        currNode = nextNode;

        if(visited[currNode] == 0)
        {
            visited[currNode] = 1;
            count++;
        }

        free(neighbors);
    }

    #if DEBUG
    printf("\n%sRESULT:%s\n", Bright_Magenta, White);
    if (count == size) {
        printf("%sSUCCESS! Done in %d steps.%s\n", Green, steps, White);
    } else {
        printf("%sFAIL! [%d / %d]%s\n", Bright_Red, count, size, White);
    }
    #endif

    if (count == size)
    {
        res[2] = 1;
    }
    else
    {
        res[2] = 0;
    }

    free(visited);
    return res;
}

int main(void)
{
    // INIT
    srand(time(NULL));
    FILE *InFile, *NetFile, *OutFile;
    InFile = fopen("input.txt", "r");
    NetFile = fopen("network.txt", "r");
    OutFile = fopen("output.txt", "w");
    int size = 0;
    int start = 0;
    int **p;

    // FILE CHECK
    if(InFile == NULL || NetFile == NULL)
    {
        perror ("File error");
        #if !DEBUG
        exit(1);
        #endif
    }

    // BUILD DA MATRIX
    p = read(NetFile, &size);

    // GET START POZ
    start = fin(InFile);

    // STATZ
    int successfulYears = 0;
    int bestYear = 0;

    long long totalSteps = 0;
    int minSteps = INT_MAX;

    long long totalDistance = 0;

    for (int year = 1; year <= SIM_YEARS; year++)
    {
        int *res = santaSim(p, size, start);

        totalSteps += res[0];
        totalDistance += res[1];

        if (res[2] == 1)
        {
            successfulYears++;
            if (res[0] < minSteps)
            {
                minSteps = res[0];
                bestYear = year;
            }
        }

        free(res);
    }

    // WRITE
    fprintf(OutFile, "%d\n", successfulYears);
    fprintf(OutFile, "%.2f\n", (double)totalDistance / SIM_YEARS);
    fprintf(OutFile, "%.2f\n", (double)totalSteps / SIM_YEARS);
    if(bestYear != 0)
    {
        fprintf(OutFile, "%d %d\n", bestYear, minSteps);
    }

    // CLEANUP
    for(int i = 0; i < size; i++) free(p[i]);
    free(p);
    fclose(InFile);
    fclose(NetFile);
    fclose(OutFile);
    return 0;
}
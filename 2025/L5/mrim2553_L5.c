/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) 9 - Dinamikus memóriakezelés és Pointerek II.pdf
 *      (2) 10 - Karakterláncok.pdf
 *      (3) 11 - Állományok kezelése.pdf
 *      (4) gemini - strtoll usage
 *          promt: char to int with strtoll in C99
 *          date: 1/5/2026 @ 3:04 AM
 *          model name: gemini-3-pro-preview
 */

#define DEBUG 0

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

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

char** read(FILE* input, long long int saveStartPoz, long long int saveEndPoz)
{
    const long long int size = saveEndPoz - saveStartPoz + 1;

    char **p = (char**)malloc(size*sizeof(char*));
    char *tmp = (char *) malloc(size * sizeof(char));

    long long int i = 1;
    while (i <= saveEndPoz)
    {
        if (i >= saveStartPoz && i <= saveEndPoz)
        {
            p[i - saveStartPoz] = (char*)malloc(255*sizeof(char));

            fgets(p[i - saveStartPoz], 255, input);
        } else {
            fgets(tmp, 255, input);
        }
        i++;
    }

    free(tmp);
    return p;
}

void write(FILE* output, const char *msg)
{
    fprintf(output, "%s", msg);
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

bool processData(char **data)
{
    char *row = *data;
    int i = 0;

    const char *numbs[] =
    {
        "nulla", "egy", "ketto", "harom", "negy",
        "ot", "hat", "het", "nyolc", "kilenc"
    };

    while (row[i] != '\0')
    {
        if (isdigit(row[i]))
        {
            const int x = row[i] - '0';
            const char *num = numbs[x];
            const int len = strlen(num);

            const int currLen = strlen(row);
            const int newLen = currLen + len;

            char *newRow = (char*)realloc(row, newLen);
            if (newRow == NULL) {
                return false;
            }
            row = newRow;
            *data = row;

            memmove(row + len + i, row + i + 1, currLen - i);

            memcpy(row + i, num, len);

            i += len;
        } else {
            i++;
        }
    }

    return true;
}

int main(int argc, const char *argv[])
{
    // INIT
    FILE* inFile = fopen("input.txt", "r");
    FILE* outFile = fopen("output.txt", "w");
    char **data = NULL;

    // VALIDATION + READ DATA

        // get/validate params
        if (argc != 3)
        {
            write(outFile,"hiba");
            fclose(inFile);
            fclose(outFile);
            exit(1);
        }

        char *src = (char*)malloc(32*sizeof(char));
        char *dest = (char*)malloc(32*sizeof(char));

        long long int startPoz = 0;
        long long int endPoz = 0;

        strncpy(src, argv[1], 31);
        strncpy(dest, argv[2], 31);

        src[31] = '\0';
        dest[31] = '\0';

        if (char2lli(src, &startPoz) == false || char2lli(dest, &endPoz) == false || startPoz > endPoz)
        {
            write(outFile,"hiba");
            fclose(inFile);
            fclose(outFile);
            exit(1);
        }

        free(src);
        free(dest);

        // file check
        if (inFile == NULL || outFile == NULL)
        {
            write(outFile,"hiba");
            fclose(inFile);
            fclose(outFile);
            exit(2);
        }

        // get data
        data = read(inFile,startPoz,endPoz);
        long long int n = endPoz - startPoz + 1;

    // DA GUD STUFF
    for (int i = 0; i < n; i++)
    {
        if (processData(&data[i]) == false) {
            write(outFile,"hiba");
            fclose(inFile);
            fclose(outFile);
            exit(3);
        }
        write(outFile,data[i]);
        free(data[i]);
    }

    // CLEANUP
    free(data);
    fclose(inFile);
    fclose(outFile);

    return 0;
}
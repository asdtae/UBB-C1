/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) error() from L1/mrim2553.c
 *      (2) fin() | fout() from L1/mrim2553.c
 *      (3) Eloadas 6. pdf
 *      (4) Eloadas 7. pdf
 *      (5) algo: 08 - Rekurzió.pdf
 *      (6) https://cplusplus.com/reference/ctime/
 */

#define DEBUG false
#define INP_SIZE 100
#define OUTP_SIZE 100

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
#include <stdbool.h>
#include <time.h>

// MODE | STR dolog
#include "mrim2553_mode.h"
#if (MODE == 1)
    #include "mrim2553_normal.h"
#elif (MODE == 2)
    #include "mrim2553_inline.h"
#elif (MODE == 3)
    #include "mrim2553_macro.h"
#endif

void char2int(const char s[INP_SIZE], int *n)
{
    int i=0, j=0;
    int numb[INP_SIZE];
    int temp = 1;

    while(s[i] != '\0')
    {
        if((s[i] != ' ') && ( s[i] < 58 && s[i] > 47))
        {
            numb[j] = s[i] - '0';
            j++;
        }
        i++;
    }

    j--;

    while(j>=0)
    {
        //printf("%s%d%s \n",Bright_Cyan,numb[j],White);

        numb[j] *= temp;
        *n += numb[j];
        temp *= 10;

        j--;
    }
}

void fouts(FILE *OutFile ,const char s[OUTP_SIZE])
{
    fprintf(OutFile,"%s",s);
}

void foutd(FILE *OutFile ,long long int n)
{
    fprintf(OutFile,"%lld",n);
}

void foutf(FILE *OutFile ,double n)
{
    fprintf(OutFile,"%f",n);
}

#if DEBUG
void error(int errorCode, char in[OUTP_SIZE])
{
    switch (errorCode)
    {
        case 1:
            printf("%sERROR: %sin %s%s:%s Couldn't open the file.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            break;
        case 2:
            printf("%sERROR: %sin %s%s:%s File empty.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            break;
        case 3:
            printf("%sERROR: %sin %s%s:%s Invalid input.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            break;
        default:
            printf("%sERROR: %sin %serror():%s '%s%d%s' is not a valid error code.%s\n", Bright_Red, Yellow, Bright_Yellow, Bright_Red, Bright_White, errorCode, Bright_Red, Bright_White);
    }
}
#endif

void fin(char s[INP_SIZE])
{
    FILE *InFile;
    InFile = fopen("input.txt", "r");;

    if(InFile != NULL)
    {
        fgets(s,INP_SIZE,InFile);
    }
    else
    {
        perror ("File error");
        exit(1);
    }

#if DEBUG
    if(InFile == NULL) error(1,"fin/fopen()");
#endif

    fclose(InFile);
}

void fibo(int n, long long int T[INP_SIZE])
{
    if(n >= 2)
    {
        fibo(n-1,T);
        T[n] = add(T[n-1],T[n-2]);
    }
    else
    {
        T[0] = 1;
        T[1] = 1;
    }
}

void clear(long long int T[INP_SIZE])
{
    for(int i=0; i<INP_SIZE; i++)
    {
        T[i] = 0;
    }
}

double tester(int n, clock_t *sum, long long int T[INP_SIZE])
{
    clock_t curr = clock();

    fibo(n,T);
    //for(int i; i<10000000; i++) ;
    curr = clock() - curr;

    *sum += curr;
    return ((double)curr/CLOCKS_PER_SEC);
}

int main()
{
    // INIT
    int n = 0;
    clock_t sum = 0;
    long long int T[INP_SIZE] = {0};
    char s[INP_SIZE] = {'\0'};
    FILE *OutFile = fopen("output.txt", "a");

    // READ STRING
    fin(s);

    // CONV NUMB
    char2int(s,&n);
    //printf("%s%d%s \n",Bright_Magenta,n,White);

    // WRITE FIBO
    fouts(OutFile,"fibonacci(");
    foutd(OutFile,n);
    fouts(OutFile,") = ");

    fibo(n,T);
    foutd(OutFile,T[n-1]);
    fouts(OutFile,"\n");

    // WRITE STR
    fouts(OutFile,STR);
    fouts(OutFile,"\n");

    // WRITE TIME
    for(int i=0; i<5; i++)
    {
        fouts(OutFile,"#");
        foutd(OutFile,i+1);
        fouts(OutFile, " run: ");
        foutf(OutFile,tester(n,&sum,T));
        clear(T);
        fouts(OutFile,"\n");
    }

    sum /= 5;
    fouts(OutFile,"average: ");
    foutf(OutFile,((double)sum/CLOCKS_PER_SEC));
    fouts(OutFile,"\n");
    fouts(OutFile,"\n");


    // DEBUG ONLY
    #if DEBUG
    printf("\n%s",STR);

    scanf("%s",s);
    #endif

    fclose(OutFile);
    return 0;
}
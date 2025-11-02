/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) https://cplusplus.com/reference/cstdio/fopen/
 *      (2) https://cplusplus.com/reference/cstdio/fgets/
 *      (3) https://cplusplus.com/reference/cstdio/scanf/
 *
 */

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
#include <stdbool.h>

void error(int errorCode, char in[100])
{
    switch (errorCode)
    {
        case 1:
            printf("%sERROR: %sin %s%s:%s Couldn't open the file.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            perror ("File error");
            break;
        case 2:
            printf("%sERROR: %sin %s%s:%s File empty.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            break;
        case 3:
            printf("%sERROR: %sin %s%s:%s invalid input.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            break;
        default:
            printf("%sERROR: %sin %serror():%s '%s%d%s' is not a valid error code.%s\n", Bright_Red, Yellow, Bright_Yellow, Bright_Red, Bright_White, errorCode, Bright_Red, Bright_White);
    }
}

bool validInpNmb(char chr1, char chr2, char chr3)
{
    if(chr1 < 48 || chr1 > 57) return false;
    if(chr2 < 48 || chr2 > 57) return false;
    if(chr3 < 48 || chr3 > 57) return false;

    return true;
}

bool validInpStr(const unsigned char str[4])
{
    if(str[0] < 33 || str[0] > 254) return false;
    if(str[1] < 33 || str[1] > 254) return false;
    if(str[2] < 33 || str[2] > 254) return false;

    return true;
}

void fin(char s[256], int *sLen, int numbs[3],unsigned char s2[4])
{
    FILE *INFile;
    INFile = fopen("input.txt","r");

    int i;
    char tmp[3][2];

    if(INFile != NULL)
    {
        if(fgets(s, 256, INFile) != NULL)
        {
            i = 0;
            while(s[i] != '\0')
            {
                sLen++;
                i++;
            }

            for(i=0; i<3; i++)
            {
                printf("Numb%d: ",i+1);
                scanf("%s",tmp[i]);
            }
            if(validInpNmb(tmp[0][0],tmp[1][0],tmp[2][0]))
            {
                for(i=0; i<3; i++)
                {
                    numbs[i] = tmp[i][0] - 48;
                }

                printf("String: ");
                scanf("%s",s2);
                if(!validInpStr(s2)) error(3,"fin/scanf() -string");
            }
            else error(3,"fin/scanf() -numbs");
        }
        else error(2,"fin/fgets()");
    }
    else error(1,"fin/fopen()");+

    fclose(INFile);
}

void fout(char s[256])
{
    FILE *OUTFile;
    OUTFile = fopen("output.txt","w");

    if(OUTFile != NULL)
    {
        fprintf(OUTFile, "%s", s);
    }
    else error(1,"fout/fopen()");

    fclose(OUTFile);
}

int main()
{
    char clionbug[1];
    char inputString[256];
    int inStrLen = 0;
    struct secret
    {
        int numbs[3];
        unsigned char sha[4];
    } key;

    fin(inputString, &inStrLen, key.numbs, key.sha);

    printf("%s\n\n",inputString);

    for(int i=0; i<inStrLen; i++)
    {
        int d = ~key.numbs[0] << ( key.numbs[1] + key.numbs[2] );
        printf("%d",d);

        int bitmap = key.sha[0] & key.sha[1] | key.sha[2];

        inputString[i] = inputString[i] ^ d ^ bitmap;
    }

    printf("%s",inputString);

    fout(inputString);

    gets(clionbug);
    gets(clionbug);
}

/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) https://cplusplus.com/reference/cstdio/fopen/
 *      (2) https://cplusplus.com/reference/cstdio/fgets/
 *      (3) https://cplusplus.com/reference/cstdio/scanf/
 *      (4) https://cplusplus.com/reference/cstdlib/exit/
 *      (5) https://theasciicode.com.ar/
 *      (6) https://www.blindtextgenerator.com/lorem-ipsum
 *      (7) https://www.learncpp.com/cpp-tutorial/the-conditional-operator/
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
#include <stdlib.h>

void fout(const char s[256])
{
    FILE *OUTFile;
    OUTFile = fopen("output.txt","w");

    if(OUTFile != NULL)
    {
        fprintf(OUTFile, "%s", s);
    }
    //else error(1,"fout/fopen()");

    fclose(OUTFile);
}

void error(int errorCode, char in[100])
{
    switch (errorCode)
    {
        case 1:
            printf("%sERROR: %sin %s%s:%s Couldn't open the file.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            perror ("File error");
            {
                const char errmsg[100] = "Couldn't open the file.";
                fout(errmsg);
                exit(1);
            }
        case 2:
            printf("%sERROR: %sin %s%s:%s File empty.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            {
                const char errmsg[100] = "File empty.";
                fout(errmsg);
                exit(2);
            }
        case 3:
            printf("%sERROR: %sin %s%s:%s Invalid input.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            {
                const char errmsg[100] = "Invalid input.";
                fout(errmsg);
                exit(3);
            }
        default:
            printf("%sERROR: %sin %serror():%s '%s%d%s' is not a valid error code.%s\n", Bright_Red, Yellow, Bright_Yellow, Bright_Red, Bright_White, errorCode, Bright_Red, Bright_White);
    }
}

bool validInpNmb(const char chr1[3], const char chr2[3], const char chr3[3])
{
    if(chr1[1] != '\0' ) return false;
    if(chr2[1] != '\0' ) return false;
    if(chr3[1] != '\0' ) return false;

    if(chr1[0] < 48 || chr1[0] > 57) return false;
    if(chr2[0] < 48 || chr2[0] > 57) return false;
    if(chr3[0] < 48 || chr3[0] > 57) return false;

    return true;
}

bool validInpStr(const unsigned char str[5])
{
    if(str[0] < 33 || str[0] > 254) return false;
    if(str[1] < 33 || str[1] > 254) return false;
    if(str[2] < 33 || str[2] > 254) return false;
    if(str[3] != '\0' ) return false;

    return true;
}

void fin(char s[256], int *sLen, int numbs[3],unsigned char s2[5])
{
    FILE *INFile;
    INFile = fopen("input.txt","r");

    int i;
    char tmp[3][3]={"0\0","0\0","0\0"};

    if(INFile != NULL)
    {
        if(fgets(s, 256, INFile) != NULL)
        {
            i = 0;
            while(s[i] != '\0')
            {
                //printf("%c : %d\n",s[i],*sLen);
                *sLen = *sLen + 1;
                i++;
            }

            for(i=0; i<3; i++)
            {
                printf("Numb%d: ",i+1);
                scanf("%s",tmp[i]);
                if(!validInpNmb(tmp[0],tmp[1],tmp[2])) error(3,"fin/scanf() -numbs");

                numbs[i] = tmp[i][0] - 48;
            }

            printf("String: ");
            scanf("%s",s2);
            if(!validInpStr(s2)) error(3,"fin/scanf() -string");
        }
        else error(2,"fin/fgets()");
    }
    else error(1,"fin/fopen()");

    fclose(INFile);
}

void encrypt(char s[256], const int numbs[3], const unsigned char str[4], int inStrLen)
{
    for(int i=0; i<inStrLen; i++)
    {
        int d = ~numbs[0] << ( numbs[1] + numbs[2] );
        int bitmap = str[0] & str[1] | str[2];

        s[i] = s[i] ^ d ^ bitmap;
    }
}

void ascii()
{
    const int cl2 = 26;
    const int cl3 = 52;
    const int cl4 = 78;
    const int cl5 = 104;
    const int cl6 = 130;
    const int cl7 = 156;
    const int cl8 = 182;
    const int cl9 = 208;
    const int cl10 = 234;

    for(int i=0; i<26; i++)
    {
        printf("|%3d [0x%.2X]:  ",i,i);
        printf("|%3d [0x%.2X]: %c ",i+cl2,i+cl2, (i+cl2 > 32) ? i+cl2 : ' ' );
        printf("|%3d [0x%.2X]: %c ",i+cl3,i+cl3, i+cl3);
        printf("|%3d [0x%.2X]: %c ",i+cl4,i+cl4, i+cl4);
        printf("|%3d [0x%.2X]: %c ",i+cl5,i+cl5, (i+cl5 != 127) ? i+cl5 : ' ');
        printf("|%3d [0x%.2X]: %c ",i+cl6,i+cl6, i+cl6);
        printf("|%3d [0x%.2X]: %c ",i+cl7,i+cl7, i+cl7);
        printf("|%3d [0x%.2X]: %c ",i+cl8,i+cl8, i+cl8);
        printf("|%3d [0x%.2X]: %c ",i+cl9,i+cl9, i+cl9);
        if(i+cl10 < 256) printf("|%3d [0x%.2X]: %c ",i+cl10,i+cl10, (i+cl10 != 255) ? i+cl10 : ' ');

        printf("\n");
    }
}

int main()
{
    char inputString[256];
    int inStrLen = 0;
    struct secret
    {
        int numbs[3];
        unsigned char str[4];
    } key;

    fin(inputString, &inStrLen, key.numbs, key.str);
    encrypt(inputString,key.numbs,key.str,inStrLen);
    fout(inputString);

    printf("\n");
    ascii();

//    getchar();
//    getchar();
}

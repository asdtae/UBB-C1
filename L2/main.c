/*
 *  Mathe Ruben-Jonathan
 *  512/1
 *  mrim2553
 *
 *  References:
 *      (1) error() from L1/mrim2553.c
 *      (2) fin() | fout() from L1/mrim2553.c
 *      (3) https://en.wikipedia.org/wiki/Luhn_algorithm
 *      (4) https://www.freeformatter.com/credit-card-number-generator-validator.html
 *      (5) https://en.wikipedia.org/wiki/Payment_card_number
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
#include <stdlib.h>
#include <stdbool.h>

void char2int(const char s[100], int numb[21])
{
    int i=0, j=0;

    while(s[i] != '\0')
    {
        if(s[i] != ' ')
        {
            numb[j] = s[i] - '0';
            j++;
        }

        printf("%d %d\n", i, numb[j-1]);
        i++;
    }

    printf("\n");
}

void strcpy(const char dest[100], const char scr[100])
{
    int i;
    
    for(i=0; i<100; i++) dest[i] = "";
    i=0;
    
    while(scr[i] != '\0')
    {
        dest[i] = scr[i];
        i++;
    }    
    
    dest[i] = '\0';
}

void fout(const char s[100])
{
    FILE *OutFile;
    OutFile = fopen("output.txt", "w");

    if(OutFile != NULL)
    {
        fprintf(OutFile,"%s",s);
    }

    fclose(OutFile);
}

void error(int errorCode, char in[100])
{
    switch (errorCode)
    {
        case 1:
            printf("%sERROR: %sin %s%s:%s Couldn't open the file.%s\n",Bright_Red,Yellow,Bright_Yellow,in,Bright_Red,Bright_White);
            perror ("File error");
            {
                const char errmsg[100] = "Hiba";
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

void fin(int numb[21], int *sLen)
{
    int i;
    char s[100];

    FILE *InFile;
    InFile = fopen("input.txt", "r");
    *sLen = 0;
    for(i=0; i<21; i++) numb[i] = 0;

    i = 0;

    if(InFile != NULL)
    {
        fgets(s,100,InFile);
        while(s[i] != '\n')
        {
            if(s[i] > 47 && s[i] < 58) *sLen = *sLen + 1;
            i++;
        }
    }
    else error(1,"fin/fopen()");

    char2int(s,numb);
    fclose(InFile);
}

bool validBCardLen(const int *len)
{
    if( *len < 12 || *len > 19) return false;

    return true;
}

bool luhn(const int numb[21], const int *len)
{
    const int control = numb[*len - 1];
    printf("%sControl: %d%s\n",Bright_Magenta,control,Bright_White);

    int invNumb[21] = {0};
    for(int i = *len - 2, k = 0; i >= 0; i--, k++)
    {
        printf("%scurrent numb[%d]: %d%s\n",Bright_Cyan,i,numb[i],Bright_White);
        invNumb[k] = numb[i];
    }

    printf("\n");
    for(int i = 0; i < *len - 1; i++) printf("%d ",numb[i]);
    printf("\n");
    for(int i = 0; i < *len - 1; i++) printf("%d ",invNumb[i]);
    printf("\n");

    for(int i = 0; i < *len - 1; i++)
    {
        if(i%2 == 0)
        {
            invNumb[i] *= 2;
            printf("%s%d %s",Bright_Yellow,invNumb[i],Bright_White);
        }
        else printf("%d ",invNumb[i]);
    }
    printf("\n");

    for(int i = 0; i < *len - 1; i++)
    {
        if(invNumb[i] > 9)
        {
            invNumb[i] -= 9;
            printf("%s%d %s",Bright_Red,invNumb[i],Bright_White);
        }
        else printf("%d ",invNumb[i]);
    }
    printf("\n");

    int checkSum = 0;
    for(int i = 0; i < *len - 1; i++) checkSum += invNumb[i];
    printf("\npre-mod chs: %d\n",checkSum);

    checkSum %= 10;
    printf("chs: %s%d %scontrol: %s%d%s",Bright_Red,checkSum,Bright_White,Bright_Green,control,Bright_White);

    if(checkSum == control) return true;

    return false;
}

void getIIN(const int numb[21], char result[100])
{
    switch(numb[0])
    {
        case 2:
        {
            strcpy(result,"MasterCard");
            break;
        }
        case 3:
        {
            switch(numb[1])
            {
                case 4:7:
                {
                    strcpy(result,"American Express");
                    break;
                }
                case 0:6:8:9:
                {
                    strcpy(result,"Dinners Club International");
                    break;
                }
            }
        }
        case 4:
        {
            strcpy(result,"Visa");
            break;
        }
        case 5:
        {
            switch(numb[1])
            {
                case 0:8:
                {
                    strcpy(result,"MasterCard");
                    break;
                }
                case 1:2:3:4:5:
                {
                    strcpy(result,"Maestro");
                    break;
                }
            }
        }
        case 6:
        {
            strcpy(result,"Maestro");
            break;
        }
        default:
            strcpy(result,"etc");
    }
}

void validate(int numb[21] ,const int *len)
{
    if(vaildBCardLen(len))
    {
        if(luhn(numb, len))
        {
            char iin[100] = "";
            getIIN(numb, iin);
        }
    }
}

int main()
{
    struct bCard
    {
        int cardNbr[21];
        int cardNbrLen;
    } c1;

    fin(c1.cardNbr,&c1.cardNbrLen);
    validate(c1.cardNbr,&c1.cardNbrLen);

    //fout(c1.cardNbr);

    getchar();
    getchar();
    return 0;
}

/*
 *  Visa                        =   4
 *  Mastercard                  =   2221–2720 | 51–55
 *  Maestro                     =   5018, 5020, 5038, 5893, 6304, 6759, 6761, 6762, 6763
 *  American Express            =   34, 37
 *  Diners Club International   =   30, 36, 38, 39
 *
 *  [2,3,4,5,6]
 *
 *  0:  invalid
 *  1:  invalid
 *
 *  2:  Mastercard
 *  3:  AE      ||  DCI
 *      [4,7]   ||  [0,6,8,9]
 *  4:  Visa
 *  5:  MC      ||  M
 *      [0,8]       [1,2,3,4,5]
 *  6:  Maestro
 *
 *  7:  invalid
 *  8:  invalid
 *  9:  invalid
 */

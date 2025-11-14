/*
Név: Csete Árpád-Máté
Csoport: 511
ID: caim2527
Feladat: Lab1
Platform: macOS
Források:
-https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
-ChatGPT
-https://cplusplus.com/reference/cstdio/fscanf/
-https://theasciicode.com.ar
-https://www.cplusplus.com/reference/cstdio/printf/
-https://www.cplusplus.com/reference/cstdio/scanf/

2. beküldés változtatás: a szóhozz ellenőrzés ha kissebb mint 3 betű) be lett iktatva (73. sor)
*/

#include <stdio.h>

void ascii_tablazat()
{
    int one=0,two=0;

    for(int i=0;i<=25;i++)
    {
        one=two;
        for(int j=0;j<=9 && one<=255;j++)
        {
            //borzasztó csúnya igen, de legalább szépen néz ki a táblázat (mac-en legalább is)
            // whitespace, meg egyeb hasonlo karakterek kikuszobolese
            if(one>=52 && one<=58 ||one==153) printf(" ");
            printf("| ");
            if(one<=9) printf(" ");
            if(one<=99) printf(" ");


            if(one!=7 && one!=8 && one!=9 && one!=10 && one!=11 && one!=12 && one!=13 && one!=27 && one!=32) printf("%d [0x%02X]: %c ",one,one,one);
            else {
                if(one==127) printf("%d [0x%02X]:   ",one,one);
                else printf("%d [0x%02X]:  ",one,one);
            }
            one+=26;
        }

        two++;
        printf("\n");
    }
}


int main()
{
    char szo[256],kulcs[4];
    int x,y,z;
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt","w");

    if(in==NULL) {
        printf("No input.txt :(\n");
        return 0;
    }
    fgets(szo,255,in);
    fclose(in);

    printf("Írj be 3 (0 és 9 közötti) számot szóközzel, vagy enterrel elválasztva:\n");
    scanf("%d",&x);
    scanf("%d",&y);
    scanf("%d",&z);
    printf("Írj be egy 3 betűből álló kulcsszavat:\n");
    scanf("%3s",kulcs);

    //2. beküldésre a szóhossz ellenőrzés (ha kissebb mint 3 betű) be lett iktatva.
    if(x<0 || x>9 ||y<0 || y>9 || z<0 || z>9 || kulcs[0]=='\0' || kulcs[1]=='\0' || kulcs[2]=='\0')
    {
        fprintf(out,"Hiba! A bemeneti adatok nem megfelelőek.\n");
        return 0;
    }

    int i=0, szo_bitterkep=kulcs[0] & kulcs[1] | kulcs[2], D=(~x)<<(y+z);
    while(szo[i]!='\0'){
        szo[i]=szo[i] ^ D ^ szo_bitterkep;
        i++;
    }

    fprintf(out,"%s",szo);
    fclose(out);

    printf("\nA kódolt szöveg megtalálható az output.txt-ben.\n\nASCII táblázat:\n");
    ascii_tablazat();

    return 0;
}

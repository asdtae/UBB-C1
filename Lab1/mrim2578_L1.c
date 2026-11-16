/*
 *  Mathe Ruben-Jonathan
 *  511
 *  mrim2578
 *
 *  References:
 *      (1) https://cplusplus.com/reference/cstdio/printf/
 *      (2) https://cplusplus.com/reference/cstdio/scanf/
 *      (3) https://theasciicode.com.ar/
 */


#include <stdio.h>

int read(char s[256], int *n, int numbs[3], char str[5])
{
    FILE* inp = fopen("input.txt", "r");
    FILE* outp = fopen("output.txt", "w");

    // Megnyitjuk a filet es beolvasunk max 255 chart
    if(inp != NULL && fgets(s, 256, inp) != NULL)
    {
        int i = 0;
        while(s[i] != '\0')
        {
            *n = *n + 1;
            i++;
        }

        printf("Sikeres az \'input.txt\' beolvasasa.\n");
    } else {
        fprintf(outp, "Hiba: Nem sikerult megnyitni a file-t.\n");
        fclose(outp);
        return 1;
    }

    // Beolvasunk 3 szamjegyet es egy pontosan 3 char-os szot
    printf("Adj meg 3db 0-9 kozti szamjegyet & egy pontosan 3 char len szot: ");
    if (scanf("%d %d %d %4s", &numbs[0], &numbs[1], &numbs[2], str) == 4)
    {
        if (numbs[0] >= 0 && numbs[0] <= 9 &&
            numbs[1] >= 0 && numbs[1] <= 9 &&
            numbs[2] >= 0 && numbs[2] <= 9 &&
            str[3] == '\0' && str[2] != '\0' && str[1] != '\0' && str[0] != '\0')
        {
            printf("Sikeres a kulcs beolvasasa.\n");
        } else {
            fprintf(outp, "Hiba: A kulcs nem a megadott schema szerinti.\n");
            fclose(inp);
            fclose(outp);
            return 1;
        }
    } else {
        fprintf(outp, "Hiba: Nem sikerult beolvasni a kulcsot.\n");
        fclose(inp);
        fclose(outp);
        return 1;
    }

    fclose(inp);
    fclose(outp);
    return 0;
}

void write(char s[256], const int *n)
{
    FILE* outp = fopen("output.txt", "w");

    // Kiirjuk a kodolt text-et az output-ba
    if(outp != NULL)
    {
        int i = 0;
        while(i < *n)
        {
            fprintf(outp, "%c", s[i]);
            i++;
        }

        fclose(outp);
    }
}

void encrypt(char s[256], const int *n, const int numbs[3], const char str[5])
{
    for(int i = 0; i < *n; i++)
    {
        const int D = ~numbs[0] << (numbs[1] + numbs[2]);
        const char szo_bitterkep = str[0] & str[1] | str[2];
        s[i] = s[i] ^ D ^ szo_bitterkep;
    }
}

void setup(char s[256], char str[5])
{
    // Lenullazuk a stringeket
    int i = 0;
    while (i<256)
    {
        if (i<5) str[i] = '\0';
        s[i] = '\0';
        i++;
    }
}

void ascii()
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            const int x = i + j * 26;
            const int c = (x >= 0 && x <= 32) || x == 127 ? ' ' : x;
            x<256 ? printf("|%3d [0x%02X]: %c ", x, x, c) : 0;
        }

        printf("\n");
    }
}

int main(void)
{
    char s[256], str[5];
    int n = 0, numbs[3];
    setup(s,str);

    if (read(s,&n,numbs,str) == 0)
    {
        encrypt(s,&n,numbs,str);
        write(s,&n);
        ascii();
    } else return 1;

    return 0;
}

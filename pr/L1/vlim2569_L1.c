// Név: Varga Levente
// Csoport: 512/2
// Azonosító: vlim2569
// Felhasznált források: Órai prezentáció, ChatGPT, Kaiser Márk (511-es csoport), Szász Tamás-László

#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    char szoveg[256], szo[4];
    char kodolt, szo_bitterkep;
    unsigned int x, y, z, d;
    FILE *f, *ki;

    f = fopen("input.txt", "r");
    if (!f)
    {
        ki = fopen("output.txt", "w");
        fprintf(ki, "Hiba: Nem sikerult megnyitni az input.txt-t.");     // megpróbáljuk megnyitni a file-t és megnézzük, hogy sikerült-e 
        fclose(ki);
        exit(0);
    }
    fgets(szoveg, 256, f);
    fclose(f);

    printf("Adj meg 3 szamot 0-tol 9-ig:\n");           // beolvassuk az adatokat
    scanf("%d%d%d", &x, &y, &z);
    
    while (getchar() != '\n');

    printf("Adj meg egy 3 karakteres szot:\n");
    fgets(szo, 5, stdin);


    if (x > 9 || y > 9 || z > 9 || szo[3] != '\n')      // megnézzük, hogy a számok helyesek-e, illetve, hogy a 4. karakter amit a betüknél kaptunk az \n-e
    {
        ki = fopen("output.txt", "w");
        fprintf(ki, "Hiba: Ervenytelen bemeneti adat!");     // megvizsgáljuk, hogy a bemeneti adatok helyesek, ha nem, akkor beírjuk az output-ba hogy hibás
        fclose(ki);
        exit(0);
    }

    ki = fopen("output.txt", "w");                             // a megadott módszerrel titkosítjuk a szöveget és beírjuk a fileba
    for (int i = 0; szoveg[i] != '\n'; i++) 
    {
        d = ~x << (y + z);
        szo_bitterkep = ((szo[0] & szo[1]) | szo[2]);
        kodolt = szoveg[i] ^ d ^ szo_bitterkep;
        fprintf(ki, "%c", kodolt);
    }
    fclose(ki);

    int sor = 26;  // sorok száma 
    int oszlop = 10;  // oszlopok száma           a kettőnek a szorzata nagyobb, mint 256
    int ascii;
    char c;                     // a c-t a különleges esetek miatt vesszük fel, pl. endline, delete stb.

    printf("\n");

    for (int i = 0; i < sor; i++)
    {
        for (int j = 0; j < oszlop; j++)                            // az első sorban a 0. elem aztán a 26. majd az 52. és így tovább
        {                                                           // a második sorban az 1. elem aztán a 27. majd az 53. és így tovább
            ascii = i + j * sor;                            
            if (ascii > 255) 
                break;                                              // ha 255 fölé megyünk, akkor befejezzük a táblázatot

            if ((ascii >= 0 && ascii <= 31) || ascii == 127)        // a különleges eseteket helyettesítsük szóközzel
                c = ' ';
            else
                c = ascii;

            printf("| %3d 0x[%02X]: %c ", ascii, ascii, c);         // kiiratjuk a táblázatot soronként a megadott alakban
        }
        printf("\n");
    }

    return 0;
}

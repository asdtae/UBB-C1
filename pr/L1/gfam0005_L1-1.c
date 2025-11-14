// gfam0005
// Gábor Farkas Ferenc
// 1611/1
// kurzusok
// Ladányi Péter segítségével
// CHATGPT tobbszor is ellenorizte, a fajlkezelesnel tobbszor kertem a segitseget

#include <stdio.h>

int main()
{

    printf("\n\n\n");
    FILE *f;
    FILE *g;
    f = fopen("input.txt", "r");
    g = fopen("output.txt", "w");
    if (!f)
    {                                                           //FAJLOK KINYITASA
        printf("> hiba\n"); // 2. kurzus 41. oldal
        return 0;
    }
    else
    {
        printf(" >fajl megnyitva\n");
    }
    if (!g)
    {                                                           //FAJLOK KINYITASA
        printf("> hiba\n"); // 2. kurzus 41. oldal
        return 0;
    }
    else
    {
        printf(" >fajl megnyitva\n");
    }




    char sorFajlbol[256];
    char aux;
    int i = 0;      
    while ((aux = fgetc(f)) !='\n' && i <= 255)                              //BEOLVASOM A KARAKTERSORT A FAJLBOL
    {
        sorFajlbol[i] = (char)aux;
        i++;
    }
    printf("\n");
    sorFajlbol[i] = '\0';




    int x, y, z;
    scanf("%d",&x);
    if (x > 9 || x < 0 )
    {
        fprintf(g, "> helytelen bemeneti adatok a standard bemenetrol! Az x ertek nem felel meg a 0<= x <= 9 kriteriumnak\n");    //SZAMOK BEOLVASASA, TESZTELESE
        fclose(f);fclose(g);
        return 0;
    }
    scanf("%d",&y);
    if (y > 9 || y < 0 )
    {
        fprintf(g, "> helytelen bemeneti adatok a standard bemenetrol! Az y ertek nem felel meg a 0<= y <= 9 kriteriumnak\n");   //SZAMOK BEOLVASASA, TESZTELESE
        fclose(f);fclose(g);
        return 0;
    }
    scanf("%d",&z);
    if (z > 9 || z < 0 )
    {
        fprintf(g, "> helytelen bemeneti adatok a standard bemenetrol! Az z ertek nem felel meg a 0<= z <= 9 kriteriumnak\n");    //SZAMOK BEOLVASASA, TESZTELESE
        fclose(f);fclose(g);
        return 0;
    }


    char szo[256];
    scanf("%255s", szo);
    int szamlalo = 0;
    while(szo[szamlalo] != '\0')
    {
        szamlalo++;                                             //SZO BEOLVASASA ES TESZTELESE
    }
    if (szamlalo!= 3)
    {
        fprintf(g, "> helytelen bemeneti adatok a standard bemenetrol! szo nem 3 karakteres.\n");
        fclose(f);fclose(g);
        return 0;
    }


    char C,feldolgozott;
    int D = ~x << (y + z);
    int szo_bitterkep = (szo[0] & szo[1]) | szo[2];
    szamlalo = 0;
    while(sorFajlbol[szamlalo] != '\0')
    {
        szamlalo++;  
                                          //BEOLVASOTT LANC KODOLASA
    }
    for( i = 0; i < szamlalo; i++)
    {
        C = sorFajlbol[i];
        feldolgozott= C ^ D ^ szo_bitterkep;
        fprintf(g,"%c",feldolgozott);
    }
    fprintf(g,"\0");




    for(i = 0; i != 233; i+=26)
    {   
        if(i > 255)
        {
            printf("\n");
            i %= 256;                                                       //ASCII
            i -= 3;
        }
        if(i == 0 ||i == 7 ||i == 8 ||i == 9)
            printf("|  %d [0x%02X]:   ",i,i);
        else if (i == 10 ||i == 13 ||i == 32)
            printf("| %d [0x%02X]:   ",i,i);
        else if (i < 10 && i > 0)
            printf("|  %d [0x%02X]: %c ",i,i,i);
        else if (i < 100 && i > 9)
            printf("| %d [0x%02X]: %c ",i,i,i);
        else if (i < 1000 && i > 99)
            printf("|%d [0x%02X]: %c ",i,i,i);
    }
    printf("|%d [0x%02X]: %c ",i ,i,i);
    fclose(f);fclose(g);
    return 0;
}
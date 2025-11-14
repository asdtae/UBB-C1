//Chiorean-Péter Noémi,511,cnim2526
//Az input, output fájl megnyitását, leellenőrzését, a titkosítást ChatGPT segítségével csináltam
//az ASCII táblázat kiírásához Gemini és Bálint Eszter segítségét kértem


#include <stdio.h>
#include <string.h>
#include <ctype.h> 

int main(void)
{

    FILE* fin = NULL;
    FILE* fout = NULL;

    int x, y, z;
    char szoveg[256];
    char szo[10];
    int error_code; 

    //Input.txt megnyitása (Olvasás)
    error_code = fopen_s(&fin, "Inp ut.txt", "r");

    if (error_code != 0) {
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "Nem sikerult beolvasni az allomanyt (fopen_s hiba: %d).\n", error_code);
            fclose(fout);
        }
        return 1;
    }

    if (fgets(szoveg, sizeof(szoveg), fin) == NULL) {
        fclose(fin);
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "Nem sikerult beolvasni az allomanyt.\n");
            fclose(fout);
        }
        return 1;
    }

    fclose(fin);

    printf("Adj meg 3 szamot 0-9 kozott: ");
    if (scanf_s("%d %d %d", &x, &y, &z) != 3) {
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "Nem sikerult beolvasni a 3 szamot.\n");
            fclose(fout);
        }
        return 1;
    }
    
    //Leellenőrzi, hogy a számok 0 és 9 között vannak-e
    if ((x < 0 || x > 9) || (y < 0 || y > 9) || (z < 0 || z > 9)) {
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "A szamok nem 0-9 kozott vannak.\n");
            fclose(fout);
        }
        return 1;
    }

    printf("Adj egy 3 karakter hosszusagu szot: ");
    if (scanf_s("%s", szo, sizeof(szo)) != 1) {
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "Nem sikerult beolvasni a szot.\n");
            fclose(fout);
        }
        return 1;
    }

    int szo_hossz = 0;
    while (szo[szo_hossz] != '\0') {
        szo_hossz++;
    }
    
    // Leellenőrzi, hogy a szó 3 betű hosszú-e
    if (szo_hossz != 3) {
        fopen_s(&fout, "output.txt", "w");
        if (fout) {
            fprintf(fout, "A szo nem 3 betubol all.\n");
            fclose(fout);
        }
        return 1;
    }

    // Titkosítás 
    int D = (~x) << (y + z);
    int szo_bitterkep = (szo[0] & szo[1]) | szo[2];

    for (int i = 0; szoveg[i] != '\0'; i++) 
        szoveg[i] = szoveg[i] ^ D ^ szo_bitterkep;
    

    //Output.txt megnyitása (Írás)
    error_code = fopen_s(&fout, "output.txt", "w");
    if (error_code != 0) {
        printf("Nem sikerult megnyitni az output.txt-t (fopen_s hiba: %d).\n", error_code);
        return 1;
    }

    fprintf(fout, "%s", szoveg);
    fclose(fout);

    //ASCII táblázat kiírása
    printf("\nASCII tablazat.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
     
   int sor, oszlop, index;

    unsigned char karakter;


    // 26 sor és max. 10 oszlop
    for (sor = 0; sor < 26; sor++) { 

        for (oszlop = 0; oszlop < 10; oszlop++) { 

            // Kód kiszámítása: oszlop-alapú bejárás (col * 26 + row)
            // [Index = 0...255]
            index =oszlop * 26 + sor;           

            if (index > 255) // Csak a (0-255) kódok kiírása

                break;
            
            // Az index átalakítása kiírható karakterré
            karakter = (unsigned char)index;

           // Vezérlőkarakterek (0-31) vagy DEL (127)
            if (karakter < 32 || karakter == 127) {

                // Nem nyomtathatók: A karakter helye szóközökkel kitöltve.
                printf("| %3d [0x%02X]        ", index, index);

            } else {
                // Nyomtatható karakterek: Kód + Hex + Karakter
                printf("| %3d [0x%02X]  %-3c   ", index, index, karakter);

            }

        }
        
        // Sortörés minden sor (0-25) végén a 10. oszlop után
        printf("\n"); 
      }
    
     printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
     return 0;
}
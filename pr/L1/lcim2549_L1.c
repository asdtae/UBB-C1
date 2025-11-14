    // Lorincz Csanad, lcim2549, 512/1 csoport, lab1 feladat
    // Segedanyagok amiket hasznaltam a weboldalon a tanarur altal feltoltott linkjei es Gemini az ascii tablazat kirajzolasahoz szoveges utbaigazitast.
    // - http://www.cplusplus.com/reference/cstdio/printf/ 
//http://www.cplusplus.com/reference/cstdio/scanf/ 
//https://theasciicode.com.ar/ 
    #include <stdio.h>
    #include <stdbool.h>

    int main() {
        FILE *finput, *foutput;  // fajl pointerek
        
        finput = fopen("input.txt", "r");   
        foutput = fopen("output.txt", "w");

        if (foutput == NULL) {
            fprintf(stderr, "Nem hozhato letre!\n");
            return 1;
        }

        if (finput == NULL) {
            fprintf(foutput, "Nem talalhato vagy nem olvashato az 'input.txt'\n");
            fclose(foutput);
            return 1;
        }

        char cX, cY, cZ;
        char szo[3];
        char szoellenorzo;  
        bool hiba = false;   // hibajelzo ami az elejen false ,es ha a felteteleknek nem felel meg a bemenet igazza valik

        printf("Adj meg harom szamot: ");
        cX = getchar();
        cY = getchar();
        cZ = getchar();
        getchar();

        if (cX < '0' || cX > '9' || cY < '0' || cY > '9'|| cZ < '0' || cZ > '9') { //ellenorzom hogy a szam 0-9 kozott van-e
            hiba = true;
        }

        printf("Adj meg harom karaktert: ");
        szo[0] = getchar();
        szo[1] = getchar();
        szo[2] = getchar();
        szoellenorzo = getchar(); // ennek \n-ek kell lennie.

        if (szoellenorzo != '\n' && szoellenorzo != EOF) { //ha a negyedik karakter nem "enterrel" vegzodik hibas
            hiba = true;
        }

        if (hiba) {
            fprintf(foutput, "Nem helyes kulcs, a szamok 0-9-ig kell legyen es a szo 3 betubol allhat!"); 
            fclose(finput);
            fclose(foutput);
            return 1;
        }

        int X = cX - '0';
        int Y = cY - '0';
        int Z = cZ - '0';

        int D = ~X << (Y + Z);
        int szo_bitterkep = (unsigned char)szo[0] & (unsigned char)szo[1] | (unsigned char)szo[2];

        int c_input;
        while ((c_input = fgetc(finput)) != EOF) { //beolvassa a fajl karaktereit amig el nem eri a fajlzaro karaktert
                unsigned char C = c_input;
                unsigned char feldolgozott_ertek = C ^ D ^ szo_bitterkep;
                fputc(feldolgozott_ertek, foutput);  
        }
        fclose(finput);
        fclose(foutput);

        printf("Kesz!\n");
        printf("ASCII tablazat\n"); //ascii tablazat kirajzolasa

        for (int i = 0; i < 26; i++) { // 26 sor
            for (int j = 0; j < 10; j++) { // 10 oszlop
                int val = j * 26 + i;
                if (val <= 255) {
                unsigned char c = (unsigned char)val;
                printf("%3d [%c] %3d (0x%02x)",val, c, val, val); 
            }
                if (j < 9) {
                    printf(" | ");
                }   
            }
            printf("\n");    
        }

        return 0;


    }
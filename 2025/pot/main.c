#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        exit(1);
    }

    // Elso arg
    char *rendNev= (char*)calloc(255,sizeof(char));
    strncpy(rendNev, argv[1], strlen(argv[1]));

    // Masodik arg
    int maxArany = 0;
    char *maxAranyTemp= (char*)calloc(255,sizeof(char));
    strncpy(maxAranyTemp, argv[2], strlen(argv[2]));
    maxArany = atoi(maxAranyTemp);

    // File
    FILE* inp = fopen("input.txt", "r");
    if (inp == NULL)
    {
        exit(1);
    }

    // File eltarolasa
    struct szemely
    {
        char vezeteknev[128];
        char keresztnev[128];
        char orszag[128];
        int eletkor;
        int goldNumb;
    };

    int players = 0;
    struct szemely **game = (struct szemely**)calloc(players + 1, sizeof(struct szemely));
    game[0] = (struct szemely*)calloc(players,sizeof(struct szemely));

    char buffer[512];


    while (fgets(buffer,512,inp))
    {
        char vez[128];
        char ker[128];
        char orszag[128];
        char eletkorTemp[128];
        int eletkor;

        sscanf(buffer,"%s %s %s %d",vez,ker,orszag,&eletkor);
        // eletkor = atoi(eletkorTemp);

        printf("1: %s %s %s %d\n",vez,ker,orszag,eletkor);

        strncpy(game[players]->vezeteknev,vez,sizeof(vez));
        strncpy(game[players]->keresztnev,ker,sizeof(ker));
        strncpy(game[players]->orszag,orszag,sizeof(orszag));
        game[players]->eletkor = eletkor;

        //
        printf("1: %s %s %s %d\n\n",game[players]->vezeteknev,game[players]->keresztnev,game[players]->orszag,game[players]->eletkor);

        // Realloc
        players++;
        struct szemely **newGame = (struct szemely**)realloc(game,(players + 1) * sizeof(struct szemely));
        if (newGame == NULL)
        {
            fclose(inp);
            free(newGame);
            free(game);
            free(maxAranyTemp);
            free(rendNev);

            exit(1);
        }

        game = newGame;
        free(newGame);

        // printf("2: %s %s %s %d\n",vez,ker,orszag,eletkor);
        // printf("2: %s %s %s %d\n\n",game[players]->vezeteknev,game[players]->keresztnev,game[players]->orszag,game[players]->eletkor);

        game[players] = (struct szemely*)calloc(players,sizeof(struct szemely));
    }
    //free(game[players]);


    // Game
    printf("Udv a %s Olimpian!\n\n",rendNev);

    struct jatekok
    {
        char nev[128];
        int maxPlayers;
    };

    int games = 0;
    struct jatekok **gameList = (struct jatekok**)calloc(players + 1, sizeof(struct jatekok));
    gameList[0] = (struct jatekok*)calloc(players,sizeof(struct jatekok));


    bool gameListReadOver = false;

    while (1)
    {
        char nev[128];
        char maxPlayersTemp[128];

        scanf("%s",nev);
        if (strcmp(nev,"VEGE") == 0) break;
        scanf("%d",maxPlayersTemp);
        int maxPlayers = atoi(maxPlayersTemp);

        strncpy(gameList[games]->nev,nev,sizeof(nev));
        gameList[games]->maxPlayers = maxPlayers;

        // Realloc
        games++;
        struct jatekok **newGameList = (struct jatekok**)realloc(gameList,(games + 1) * sizeof(struct jatekok));
        if (newGameList == NULL)
        {
        fclose(inp);
        free(newGameList);
        free(gameList);
        free(game);
        free(maxAranyTemp);
        free(rendNev);

        exit(1);
        }

        gameList = newGameList;
        free(newGameList);

        // printf("2: %s %s %s %d\n",vez,ker,orszag,eletkor);
        // printf("2: %s %s %s %d\n\n",game[players]->vezeteknev,game[players]->keresztnev,game[players]->orszag,game[players]->eletkor);

        game[players] = (struct szemely*)calloc(players,sizeof(struct szemely));
    }

    bool gameOver = false;
    srand(time(NULL));

    int gamesCounter = 0;

    while (!gameOver)
    {
        int playersRand = 0;
        playersRand = rand() % 10;
        if (playersRand > players) playersRand = players;
        if (playersRand > gameList[gamesCounter]->maxPlayers) playersRand = gameList[gamesCounter]->maxPlayers;

        int getPlayersCounter = 0;
        char szemelyek[playersRand - 1][128];
        while (getPlayersCounter < playersRand)
        {
            int getId = rand() % players;
            strncpy(szemelyek[getPlayersCounter],game[getId]->vezeteknev,128);
            getPlayersCounter++;
        }

        int maxGold = ((rand() % maxArany) % 5) + 1;
        int maxSilver = (rand() % 5) + 1;
        int maxCopper = (rand() % 5) + 1;

        int usedGold = 0;
        int usedSilver = 0;
        int usedCopper = 0;
        int medalDistr[playersRand];
        int distrCounter = 0;

        while (distrCounter < playersRand)
        {
            if (usedGold < maxGold)
            {
                medalDistr[distrCounter] = 1;
                usedGold++;
            }

            if (usedSilver < maxSilver)
            {
                medalDistr[distrCounter] = 2;
                usedSilver++;
            }

            if (usedCopper < maxCopper)
            {
                medalDistr[distrCounter] = 3;
                usedCopper++;
            }

            distrCounter++;
        }

        maxArany -= usedGold;

        gamesCounter++;
        if (strcmp(gameList[gamesCounter]->nev,"VEGE") == 0) gameOver = true;
    }

    // Cleanup
    for (int i = 0; i<=players; i++)
    {
        free(game[i]);
    }
    for (int i = 0; i<=games; i++)
    {
        free(gameList[i]);
    }
    free(game);
    free(gameList);
    free(maxAranyTemp);
    free(rendNev);
    fclose(inp);

    return 0;
}

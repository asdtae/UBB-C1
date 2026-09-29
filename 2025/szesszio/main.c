/*
 *  Mathe Ruben-Jonathan
 *  512
 *  mrim2553
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define arg1_max 255

typedef struct
{
    char name[25];
    int HP;
    int XP;

} player;

typedef struct
{
    int nrOfPlayers;
    int alive;
    player **players;

} game;

bool char2int(const char *inp, int *oup)
{
    if (inp[3] != '\0')
    {
        return false;
    }

    if (inp[0] < '0' || inp[0] > '9' ||
        inp[1] < '0' || inp[1] > '9' ||
        inp[2] < '0' || inp[2] > '9')
    {
        return false;
    }

    *oup = inp[0] - '0';
    *oup *= 10;
    *oup += inp[1] - '0';
    *oup *= 10;
    *oup += inp[2] - '0';

    if (*oup <=100 || *oup > 500)
    {
        return false;
    }

    return true;
}

bool isOneWord(char *inp)
{
    int i = 0;
    bool space = false;

    while (inp[i] != '\0')
    {
        if (inp[i] == ' ') space = true;
        if (space && (inp[i] >= 'a' || inp[i] < 'z' || inp[i] >= 'A' || inp[i] < 'Z')) return false;

        i++;
    }

    return true;
}

void read(FILE* input, game *g)
{
    char tmp[25];
    char lastTmp[25];

    g->players = (player**)malloc(1*sizeof(player));
    int i = 0;

    while (!feof(input))
    {
        fgets(tmp,25,input);
        //if (!strcmp(tmp,lastTmp)) break;

        player *p = (player*)malloc(1*sizeof(player));
        strncpy(p->name,tmp,25);
        p->HP = 100;
        p->XP = 0;

        //g->nrOfPlayers = i;
        i++;
        player **q = (player**)realloc(g->players,i*sizeof(player));
        if (q != NULL)
        {
            g->players = q;
            g->players[i-1] = p;
        }

        strncpy(lastTmp,tmp,25);
        printf("i:%d nr: %d pl: %s tmp: %s\n",i,g->nrOfPlayers,g->players[i-1]->name, tmp);
    }

    //printf("i:%d nr: %d pl: %s tmp: %s\n",i,g->nrOfPlayers,g->players[i-1]->name, tmp);
    i--;
    free(g->players[i-1]);
    i--;
    g->nrOfPlayers = i;

    //printf("i:%d nr: %d pl: %s tmp: %s\n",i,g->nrOfPlayers,g->players[i-1]->name, tmp);
}

int main(int argc, const char *argv[])
{
    // ARGS VALIDATION
    if (argc != 3)
    {
        printf("hiba\n");
        exit(1);
    }
    char *missionName = (char*)malloc(arg1_max * sizeof(char));
    char *gateStabilityPre = (char*)malloc(5 * sizeof(char));

    strncpy(missionName,argv[1],arg1_max);
    strncpy(gateStabilityPre,argv[2],5);

    if (!isOneWord(missionName))
    {
        printf("hiba\n");
        exit(1);
    }

    int gateStability = 0;
    if (!char2int(gateStabilityPre,&gateStability))
    {
        printf("hiba\n");
        exit(1);
    }

    // Mission start
    FILE* input = fopen("input.txt","r");
    if (input == NULL)
    {
        printf("hiba\n");
        exit(1);
    }

    printf("--- Kuldetes: %s ---\n",missionName);

    game g;
    g.nrOfPlayers = 0;
    g.players = NULL;

    read(input,&g);
    g.alive = g.nrOfPlayers;



    if (g.alive > g.nrOfPlayers/2) printf("A Kapu lezarult, Hawkins megmenekult!");
    else printf("The Upside Down is spreading, further missions are needed...");


    // CLEANUP
    free(missionName);
    free(gateStabilityPre);
    int tmp_free = g.nrOfPlayers;

    printf("\n");

    for (int i=0; i<tmp_free; i++)
    {
        printf("%d %s\n",i,g.players[i]->name);
        free(g.players[i]);
    }

    fclose(input);
    return 0;
}
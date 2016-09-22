// DracView.c ... DracView ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
// #include "Map.h" ... if you decide to use the Map ADT
typedef struct _player *Player;

struct dracView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    Round round;
    int score;
    Player players[NUM_PLAYERS];
    LocationID immatureVampire;
    LocationID Traps[NUM_MAP_LOCATIONS];
};

typedef struct _player {
    int health;
    LocationID location;
    LocationID history[TRAIL_SIZE];
    int connections[NUM_MAP_LOCATIONS];
    int numLocations;
} *Player;

static void analyseTraps(DracView dracView, char *pastPlays);
     

// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    DracView dracView = malloc(sizeof(struct dracView));
    GameView g = newGameView(pastPlays, messages);
    LocationID Traps[NUM_MAP_LOCATIONS] = { 0 };

    dracView->Traps[NUM_MAP_LOCATIONS] = *Traps;

    dracView->round = getRound(g);
    dracView->score = getScore(g);
    printf("Round is %d\n", dracView->round);
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("setting for player %d\n", i);
        dracView->players[i] = malloc(sizeof(struct _player));
        dracView->players[i]->health = getHealth(g, i);
        dracView->players[i]->location = getLocation(g, i);
        getHistory(g, i, dracView->players[i]->history);

        if (dracView->players[i]->location == UNKNOWN_LOCATION) break;
        int size, *edges;
        memset(dracView->players[i]->connections, 0, NUM_MAP_LOCATIONS* sizeof(int));
        edges = connectedLocations(g, &size, dracView->players[i]->location, i, dracView->round, TRUE, TRUE, TRUE);
        printf("edges done\n");
        for (int j = 0; j < size; j++) {
            dracView->players[i]->connections[edges[j]] = 1;
        }
        printf("finished for player %d\n", i);
    }

    analyseTraps(dracView, pastPlays);


    return dracView;
}

static void analyseTraps(DracView dracView, char *pastPlays)
{
    int length = 0;
    for (int i=0; pastPlays[i] != '\0'; i++) {
        length++;
    }
    length = length+1;
    int numPlays = length / 8;

    int currPlay = 0;

    while (currPlay < numPlays) {
        if ((currPlay+1) % 5 == 0) {
            assert(pastPlays[currPlay*8] == 'D');

            char action[1];
            memcpy(action, &pastPlays[currPlay*8+5], 1);
            action[1] = '\0';

            char location[2];
            memcpy(location, &pastPlays[currPlay*8+1], 2);
            location[2] = '\0';

            char encounter[2];
            memcpy(encounter, &pastPlays[currPlay*8+3], 2);
            encounter[2] = '\0';

            for (int i = 0; i < 2; i++) {
                switch(encounter[i]) {
                    case 'T': dracView->Traps[abbrevToID(location)] += 1; break;
                    case 'V': dracView->immatureVampire = abbrevToID(location); break;
                }
            }
            if (action[0] == 'M') {
                LocationID trapLoc = dracView->players[PLAYER_DRACULA]->history[5];
                dracView->Traps[trapLoc] -= 1;
            }
            if (action[0] == 'V') {
                dracView->immatureVampire = NOWHERE;
            }
        }
        currPlay += 1;
    }

}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->round;
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player]->health;
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player]->location;
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    *start = currentView->players[player]->history[1];
    *end = currentView->players[player]->history[0];
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
    *numTraps = currentView->Traps[where];
    if (where == currentView->immatureVampire) {
        *numVamps = 1;
    } else {
        *numVamps = 0;
    }
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    for (int i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = currentView->players[player]->history[i];
    }
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION

//    LocationID moves[NUM_MAP_LOCATIONS];
    return NULL;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    LocationID *moves = (LocationID *)malloc(currentView->players[player]->numLocations*sizeof(LocationID));
    int k = 0;
    printf("k should be zero\n");

    for (int i = 0; i < NUM_MAP_LOCATIONS; i++) {
        if ( currentView->players[player]->connections[i] == 1 ) {
            printf("name of location is %s\n", idToName(i));
//            if (road == TRUE && idToType(i) == ROAD) {
//                moves[k] = i;
//                k++;
//            }
//            if (rail == TRUE && idToType(i) == RAIL) {
//                moves[k] = i;
//                k++;
//            }
//            if (sea == TRUE && (idToType(i) == SEA || idToType(i) == SEA_UNKNOWN)) {
//                moves[k] = i;
//                k++;
//            }
            moves[k] = i;
            k++;
        }
    }
    printf("k is %d\n", k);
    *numLocations = k;
    return moves;
}

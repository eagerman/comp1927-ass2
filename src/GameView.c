// GameView.c ... GameView ADT implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"

typedef struct _player *Player;

struct gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    Player players[NUM_PLAYERS];
    Map map;
    int score;
    Round currentRound;
    PlayerID currentPlayer;
}; //hey baby


typedef struct _player {
    int health;
    LocationID current;
    LocationID history[TRAIL_SIZE];
} *Player;

// Extra Functions
static void setInitialState(GameView newGameView);
static void analyseMove(char move[]);

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView g = malloc(sizeof(struct gameView));
    assert(g != NULL);
    setInitialState(g);
    
    int beginIndex = 0;
    while (pastPlays[beginIndex] != '\0') {
        // pass in GST.....
        char move[10];
        strncpy(move, pastPlays + sizeof(char)*beginIndex, 8);
        analyseMove(move);
        beginIndex += 8;
    }

    return g;
}

static void analyseMove(char move[])
{
    PlayerID player = move[0];
    char *location = strncpy(location, move[1], 2));
    locationID currLocation = abbrevToID(location);
    char actions[] = strncpy(location, move[3], 4));
}
     
static void setInitialState(GameView g)
{
    g->map = newMap();
    g->score = GAME_START_SCORE;

    g->currentRound = 0;
    g->currentPlayer = PLAYER_LORD_GODALMING;

    g->players[PLAYER_LORD_GODALMING] = malloc(sizeof(struct _player));
    g->players[PLAYER_DR_SEWARD] = malloc(sizeof(struct _player));
    g->players[PLAYER_VAN_HELSING] = malloc(sizeof(struct _player));
    g->players[PLAYER_MINA_HARKER] = malloc(sizeof(struct _player));
    g->players[PLAYER_DRACULA] = malloc(sizeof(struct _player));

    g->players[PLAYER_LORD_GODALMING]->health = GAME_START_HUNTER_LIFE_POINTS;
    g->players[PLAYER_LORD_GODALMING]->current = NOWHERE;

    g->players[PLAYER_DR_SEWARD]->health = GAME_START_HUNTER_LIFE_POINTS;
    g->players[PLAYER_DR_SEWARD]->current = NOWHERE;

    g->players[PLAYER_VAN_HELSING]->health = GAME_START_HUNTER_LIFE_POINTS;
    g->players[PLAYER_VAN_HELSING]->current = NOWHERE;

    g->players[PLAYER_MINA_HARKER]->health = GAME_START_HUNTER_LIFE_POINTS;
    g->players[PLAYER_MINA_HARKER]->current = NOWHERE;

    g->players[PLAYER_DRACULA]->health = GAME_START_BLOOD_POINTS;
    g->players[PLAYER_DRACULA]->current = NOWHERE;
}
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    assert(toBeDeleted != NULL);
    for (int i = 0; i < TRAIL_SIZE; i++) {
        free(toBeDeleted->players[i]);
    }
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return currentView->currentRound;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return currentView->currentPlayer;
}

// Get the current score
int getScore(GameView currentView)
{
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    return currentView->players[player]->health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    return currentView->players[player]->current;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    for (int i=0; i < TRAIL_SIZE; i++) {
        trail[i] = currentView->players[player]->history[i];
    }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //TODO: Implement function to return array of locationIDs
    return NULL;
}

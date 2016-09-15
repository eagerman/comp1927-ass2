// GameView.c ... GameView ADT implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"
// #include "Map.h" ... if you decide to use the Map ADT

typedef struct _player *Player;

struct gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    Player players[NUM_PLAYERS];
    Map map;
    int score;
    Round currentRound;
    PlayerID currentPlayer;
};


typedef struct _player {
    int health;
    LocationID current;
    LocationID history[TRAIL_SIZE];
} *Player;

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    assert(gameView != NULL);
    gameView->map = newMap();
    gameView->score = GAME_START_SCORE;
    printf("string length is %zd\n", strlen(pastPlays));
    gameView->currentRound = (strlen(pastPlays) / 8) / NUM_PLAYERS;
    gameView->currentPlayer = strlen(pastPlays) / NUM_PLAYERS;

    gameView->players[PLAYER_LORD_GODALMING] = malloc(sizeof(struct _player));
    gameView->players[PLAYER_DR_SEWARD] = malloc(sizeof(struct _player));
    gameView->players[PLAYER_VAN_HELSING] = malloc(sizeof(struct _player));
    gameView->players[PLAYER_MINA_HARKER] = malloc(sizeof(struct _player));
    gameView->players[PLAYER_DRACULA] = malloc(sizeof(struct _player));

    gameView->players[PLAYER_LORD_GODALMING]->health = GAME_START_HUNTER_LIFE_POINTS;
    gameView->players[PLAYER_LORD_GODALMING]->current = NOWHERE;

    gameView->players[PLAYER_DR_SEWARD]->health = GAME_START_HUNTER_LIFE_POINTS;
    gameView->players[PLAYER_DR_SEWARD]->current = NOWHERE;

    gameView->players[PLAYER_VAN_HELSING]->health = GAME_START_HUNTER_LIFE_POINTS;
    gameView->players[PLAYER_VAN_HELSING]->current = NOWHERE;

    gameView->players[PLAYER_MINA_HARKER]->health = GAME_START_HUNTER_LIFE_POINTS;
    gameView->players[PLAYER_MINA_HARKER]->current = NOWHERE;

    gameView->players[PLAYER_DRACULA]->health = GAME_START_BLOOD_POINTS;
    gameView->players[PLAYER_DRACULA]->current = NOWHERE;

    return gameView;
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
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->currentRound;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->currentPlayer;
}

// Get the current score
int getScore(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player]->health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
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

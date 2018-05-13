#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

//created assert function that prints if the assertion passed or failed. 
void assertTrue(int a, int b) {
	if(a==b) {
		printf("Assertion passed\n");
	}
	else printf("Assertion Failed\n");
}

//randomize number of players
int randomizePlayers(){
	int players;
	//random integer between 0 and 4 to check for scenario failure
	players = rand() % MAX_PLAYERS+1;
	return players;
}

//randomize hand count
int randHandCount(){
	int hand;
	//random integer 0 and MAXHand
	hand = rand() % MAX_HAND+1;
	return hand;
}
//randomize kingdom cards available

//randomize handposition
//need to use numHandCards(struct gameState *state) beforehand
int randHandPos(int numHand){
	int hand;
	//random integer 0 and the amount of cards available in user hand
	hand = rand() % numHand+1;
	return hand;
}
//randomize deck count
int randDeckCount(){
	int deck;
	//random integer between 0 and MAXdeck
	deck = rand() % MAX_DECK+1;
	return deck;
}
//randomize discard count
int randDiscardCount(){
	int deck;
	//random integer between 0 and MAXdeck
	deck = rand() % MAX_DECK+1;
	return deck;
}

//randomize played cards count
int randPlayedCount(){
	int deck;
	//random integer between 0 and MAXdeck
	deck = rand() % MAX_DECK+1;
	return deck;
}
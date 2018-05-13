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
//randomize kingdom cards available
enum CARD randKingdom() {
	enum CARD r = (rand() % (27-7) + 7);
	return r;
}

//randomize all cards available
enum CARD randCard() {
	enum CARD r = (rand() % 27);
	return r;
}

//randomize number of players
int randomizePlayers(){
	int players;
	//random integer between 0 and 4 to check for scenario failure
	players = rand() % MAX_PLAYERS+1;
	return players;
}
int * setKingdomCards(){
	static int k[10];
	int h, j;
	//initialize random kingdom cards

	for(h =0; h <10; h++) {
		k[h] = randKingdom();
	}

	int card = 0;
	h=0;
	while(card == 0) {
			for(j=0; j < h; j++){
				if(k[h] == k[j]) {
					k[h] = randKingdom();
					h--;
					card = 0;
				}
				if((j == 9) && (k[h] != k[j])){
					card = 1;
				}
			}
			h++;
		}
		return k;
}
//randomize hand count
int randHandCount(){
	int hand;
	//random integer 0 and 16
	hand = rand() % 16+1;
	return hand;
}
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
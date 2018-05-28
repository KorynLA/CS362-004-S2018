//adventurer
//1. Current player looks through deck until 2 treasure cards are found
// all the cards that were looked through are put into the discard pile
//the 2 treasure cards are added to their hand - hand with 2 treasure cards on top
//-hand with 2 treasure cards throughout
//2. if all cards are gone through and only 1 treasure card is found, that is the only card recieved - make only 1 treasure card avail
//3. No state change should occur for other players. X
//4. No state change should occur to the victory card piles and kingdom card piles. X
//5. No state change should occur with other players decks. X
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){
	printf("Testing adventurer\n\n\n");
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	//whose turn it is
	int player = 0;
	int i, j;
	int prevDeckCountT, prevHandCountT, prevDiscardCount;
	int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province};
	int n = sizeof(cardPiles) / sizeof(int);
	int prevCardPilesAmnt[n];
	int acceptableCounter = 0, tests = 0;
	
printf ("--------------------Testing when only 1 treasure card in deck---------------------\n\n");
// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);
	G.deckCount[player] = 0;
     //changing players deck
     for (j = 0; j < 10; j++) {
     	if(j==0) {
	  		G.deck[player][j] = copper;
	  	}
	  	G.deck[player][j] = estate;
	  	G.deckCount[player]++;
	}

	prevHandCountT = G.handCount[player];

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCountT+1);
	tests++;
	if(G.handCount[player] == prevHandCountT+1) {
		acceptableCounter++;
	}

	printf ("--------------------Testing card looked through is added to discard pile---------------------\n\n");
	//clears game
	 memset(&G, 23, sizeof(struct gameState));
	// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);
	G.deckCount[player] = 0;
     //changing players deck
     for (j = 0; j < 10; j++) {
     	if(j==0) {
	  		G.deck[player][j] = estate;
	  	}
	  	G.deck[player][j] = copper;
	  	G.deckCount[player]++;
	}

	prevDiscardCount = G.discardCount[player];

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	tests++;
	printf("discard count = %d, expected = %d\n", G.discardCount[player], prevDiscardCount+1);
	if(G.discardCount[player] == prevDiscardCount+1){
		acceptableCounter++;
	}

printf ("--------------------Testing 2 cards are added to the player hand---------------------\n\n");
//clears game
	 memset(&G, 23, sizeof(struct gameState));
// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);
	G.deckCount[player] = 0;
     //changing players deck
     for (j = 0; j < 10; j++) {
	  	G.deck[player][j] = copper;
	  	G.deckCount[player]++;
	}

	prevHandCountT = G.handCount[player];

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCountT+2);
	tests++;
	if(G.handCount[player] == prevHandCountT+2){
		acceptableCounter++;
	}

	printf ("--------------------Testing Deck when all are treasure cards ---------------------\n\n");
//clears game
	 memset(&G, 23, sizeof(struct gameState));
	// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);
	G.deckCount[player] = 0;
     //changing players deck
     for (j = 0; j < 10; j++) {
	  	G.deck[player][j] = copper;
	  	G.deckCount[player]++;
	}

	prevDeckCountT = G.deckCount[player];

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	tests++;
	printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCountT-2);
	if(G.deckCount[player] == prevDeckCountT){
		acceptableCounter++;
	}
	

	printf ("--------------------Testing Deck when top 2 cards are treasure cards ---------------------\n\n");
	 //clears game
	 memset(&G, 23, sizeof(struct gameState));
	// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);

	G.deckCount[player] = 0;
     //changing players deck
     for (j = 0; j < 10; j++) {
     	if((j ==0) || (j==1)) {
	  		G.deck[player][j] = copper;
	  	}
	  	G.deck[player][j] = estate;
	  	G.deckCount[player]++;
	}

	prevDeckCountT = G.deckCount[player];

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCountT-2);
	tests++;
	if(G.deckCount[player] == prevDeckCountT){
		acceptableCounter++;
	}

	 //clears game
	 memset(&G, 23, sizeof(struct gameState));
	// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);

	for(i=0; i < n; i++) {
		prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
	}
	//for previous values
	int prevHandCount = G.handCount[player];
	int prevDeckCount = G.deckCount[player];
	int prevHandCountP2 = G.handCount[1];
	int prevDeckCountP2 = G.deckCount[1];
	

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	printf ("--------------------Testing Hand count for other player has not changed---------------------\n\n");
	printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2);
	tests++;
	if(G.handCount[1] == prevHandCountP2){
		acceptableCounter++;
	} 

	printf ("--------------------Testing Deck count for other player has not changed---------------------\n\n");
	printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);
	tests++;
	if(G.deckCount[1] == prevDeckCountP2){
		acceptableCounter++;
	}

	printf ("--------------------Testing the victory piles and kingdom card piles have not changed---------------------\n\n");
	for(i=0; i < n; i++) {
		tests++;
		if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){
			printf("Supply amount Expected: %d Count: %d\n", prevCardPilesAmnt[i], G.supplyCount[cardPiles[i]]);
			acceptableCounter++;
		}
	}
 	printf("\n%d/%d tests passed!\n", acceptableCounter, tests);
	return 0;
}
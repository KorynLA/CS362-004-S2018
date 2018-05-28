//smithy
//1. Current player should receive exact 3 cards.
//2. 3 cards should come from his own pile.
//3. No state change should occur for other players.
//4. No state change should occur to the victory card piles and kingdom card piles.

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
	printf("Testing smithy! \n\n\n");
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int player = 0;
	int i;
	int acceptableCounter=0, tests=0;
	int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province};
	int n = sizeof(cardPiles) / sizeof(int);
	int prevCardPilesAmnt[n];

	// initialize a game state and player cards
	initializeGame(numPlayers, k, 50, &G);

	for(i=0; i < n; i++) {
		prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
	}
	
	int prevHandCount = G.handCount[player];
	int prevDeckCount = G.deckCount[player];
	int prevHandCountP2 = G.handCount[1];
	int prevDeckCountP2 = G.deckCount[1];
	

	smithyCard(&G, handpos);
	
	printf ("--------------------Testing in Hand Card Amount---------------------\n\n");
	tests++;
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount+3-1);
	if(G.handCount[player] == prevHandCount+3-1) {
		acceptableCounter++;
	}
	printf ("--------------------Testing in Cards are from own pile---------------------\n\n");
	tests++;
	printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount-3);
	if(G.deckCount[player] == prevDeckCount-3) {
		acceptableCounter++;
	}
	
	printf ("--------------------Testing Hand count for other player has not changed---------------------\n\n");
	tests++;
	printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2);
	if(G.handCount[1] == prevHandCountP2) {
		acceptableCounter++;
	}

	printf ("--------------------Testing Deck count for other player has not changed---------------------\n\n");
	tests++;
	printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);
	if(G.deckCount[1] == prevDeckCountP2){
		acceptableCounter++;
	}
	
	printf ("--------------------Testing the victory piles and kingdom card piles have not changed---------------------\n\n");
	

	for(i=0; i < n; i++) {
		tests++;
		if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){
			acceptableCounter++;
		}
	}
	printf("\n%d/%d tests passed!\n", acceptableCounter, tests);
	
	return 0;
}

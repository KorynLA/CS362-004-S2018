//baron
//1. Current player can recieve 4 coins (with discard) or gain another estate card (in hand)
//2. estate card can be taken from victory pile 
//discard should not change if gains another estate card.
//increases player buys by 1
//3. No state change should occur for other players.
//4. No state change should occur to the kingdom card piles.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <assert.h>

int main(){

	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	 int numPlayers = 2; 
	int handpos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0; 
	//whose turn it is 
	int player = 0; 
	int i, j;
	int prevDeckCountT, prevHandCountT, prevDiscardCount; 
	int prevCardPilesAmnt[16];
	int prevNumBuys, prevEstate;
	int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province, copper, silver, gold};
	int acceptableCounter =0, tests =0;
	
	//clears game
	memset(&G, 23, sizeof(struct gameState)); // initialize a game state and player cards initializeGame(numPlayers, k, 50, &G);
	// initialize a game state and player cards 
	initializeGame(numPlayers, k, 50, &G); 

	//for previous values
	int prevHandCount = G.handCount[player]; 
	int prevDeckCount = G.deckCount[player]; 
	int prevHandCountP2 = G.handCount[1];
	int prevDeckCountP2 = G.deckCount[1]; 
	int prevCoins = G.coins;
	prevNumBuys = G.numBuys;
	prevEstate = G.supplyCount[estate];

	for(i=0; i < 16; i++) { 
		prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
	}
	// need an estate card available
	for(i=0; i < G.handCount[player]; i++) {
		G.hand[player][i] = gold;
		if(i == 1) {
			G.hand[player][1] = baron;
			G.hand[player][0] = estate;
		}
		
	}
	cardEffect(baron, choice1, choice2, choice3, &G, handpos, &bonus); 

	printf ("--------------------Testing number of buys for player ---------------------\n\n");
	printf("Number of buys count = %d, expected = %d\n", G.numBuys, prevNumBuys+1); 
	tests++;
	if(G.numBuys == prevNumBuys+1){
		acceptableCounter++;
	}


	printf ("******Testing choice as gaining +4 with discard (of estate) ******\n\n\n");

	printf ("--------------------Testing coins for player has changed---------------------\n\n");
	printf("coin count = %d, expected = %d\n", G.coins, prevCoins+4); 
	tests++;
	if(G.coins == prevCoins+4){
		acceptableCounter++;
	}

	printf ("--------------------Testing Hand count for player has changed---------------------\n\n");
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount-2); 
	tests++;
	if(G.handCount[player] == prevHandCount-2){
		acceptableCounter++;
	}

	printf ("--------------------Testing supply count of estate  ---------------------\n\n\n");
	printf("Supply count of estate= %d, expected = %d\n", G.supplyCount[estate], prevEstate);
	tests++; 
	if(G.supplyCount[estate] == prevEstate){
		acceptableCounter++;
	}


	printf ("--------------------Testing Hand count for other player has not changed---------------------\n\n");
	tests++;
	printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2); 
	if(G.handCount[1] == prevHandCountP2){
		acceptableCounter++;
	}

	printf ("--------------------Testing Deck count for other player has not changed---------------------\n\n");
	printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2); 
	tests++;
	if(G.deckCount[1] == prevDeckCountP2){
		acceptableCounter++;
	}

	printf ("--------------------Testing all the supply piles---------------------\n\n");
	for(i=0; i < 16; i++) { 
		printf("Card = %d supply count = %d, expected = %d\n", cardPiles[i], G.supplyCount[cardPiles[i]], prevCardPilesAmnt[i]); 
		tests++;
		if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){
			acceptableCounter++;
		}
	}

	printf ("--------------------Testing when player doesn’t have estate card in hand to discard ---------------------\n\n\n");
	//clears game
	memset(&G, 23, sizeof(struct gameState)); 
	// initialize a game state and player cards 
	initializeGame(numPlayers, k, 50, &G);

	//for previous values
	prevHandCount = G.handCount[player]; 
	prevCoins = G.coins;
	prevNumBuys = G.numBuys;
	prevEstate = G.supplyCount[estate];

	//figure out how to change the hand – no estate cards
		// need an estate card available
	for(i=0; i < G.handCount[player]; i++) {
		G.hand[player][i] = gold;
		if(i == 0) 
			G.hand[player][i] = baron;
	}

	cardEffect(baron, choice1, choice2, choice3, &G, handpos, &bonus); 

	printf ("--------------------Testing coins for player has changed---------------------\n\n");
	printf("coin count = %d, expected = %d\n", G.coins, prevCoins); 
	tests++;
	if(G.coins == prevCoins){
		acceptableCounter++;
	}

	printf ("--------------------Testing Hand count for player has changed---------------------\n\n");
	tests++;
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount); 
	if(G.handCount[player] == prevHandCount){
		acceptableCounter++;
	}

	printf ("--------------------Testing supply count of estate  ---------------------\n\n\n");
	printf("Supply count of estate= %d, expected = %d\n", G.supplyCount[estate], prevEstate-1); 
	tests++;
	if(G.supplyCount[estate] == prevEstate-1){
		acceptableCounter++;
	}



	printf ("******Testing choice as gaining estate card******\n\n\n");

	//clears game
	memset(&G, 23, sizeof(struct gameState)); 
	// initialize a game state and player cards 
	initializeGame(numPlayers, k, 50, &G); 
	prevEstate = G.supplyCount[estate];
	prevCoins = G.coins;
	prevHandCount = G.handCount[player]; 

	for(i=0; i < 16; i++) { 
		prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
	}

	choice1 = 0;
	cardEffect(baron, choice1, choice2, choice3, &G, handpos, &bonus); 

	printf ("--------------------Testing the player hand has changed correctly---------------------\n\n");
	//add estate and take away baron = same amount of cards as in previous hand.
	printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount); 
	tests++;
	if(G.handCount[player] == prevHandCount){
		acceptableCounter++;
	}

	printf ("--------------------Testing coins for player has not changed---------------------\n\n");
	printf("coin count = %d, expected = %d\n", G.coins, prevCoins); 
	tests++;
	if(G.coins == prevCoins){
		acceptableCounter++;
	}

	printf ("--------------------Testing estate supply pile---------------------\n\n");
	printf("Supply count = %d, expected = %d\n", G.supplyCount[estate],  prevEstate-1); 
	tests++;
	if(G.supplyCount[estate] ==  prevEstate-1){
		acceptableCounter++;
	}

	printf ("--------------------Testing all supply piles (not estate)---------------------\n\n");

	for(i=0; i < 16; i++) { 
		if(i != 10) {
			tests++;
		printf("Card = %d supply count = %d, expected = %d\n", cardPiles[i], G.supplyCount[cardPiles[i]], prevCardPilesAmnt[i]); 
		if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){
			acceptableCounter++;
		 }
		}
	}
 printf("\n%d/%d tests passed!\n", acceptableCounter, tests);
	return 0; 
}

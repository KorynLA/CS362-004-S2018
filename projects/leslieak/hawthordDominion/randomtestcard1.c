//smithy
//1. Current player should receive exact 3 cards.
//2. 3 cards should come from his own pile.
//3. No state change should occur for other players.
//4. No state change should occur to the victory card piles and kingdom card piles.

#include "dominion.h"
#include "dominion_helpers.h"
#include "test.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>




int main(){
	printf("Testing smithy\n\n");
	srand(time(NULL)); 
	struct gameState G;
	int num = rand() % 51;
	int player = 0;
	int t, i, j;
	//0-1
	int functionCall = rand() % 2;

	int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province};
	int n = sizeof(cardPiles) / sizeof(int);
	int prevCardPilesAmnt[n];
	int game;

	for(t= 0; t < 45; t++){
	//Randomize number of players in game
		int numPlayers = randomizePlayers();
		//base case when all kingdom cards are set to the same value.
		if(t == 0) {
			int h[] = {baron, baron, baron, baron, baron, baron, baron, baron, baron, baron};
			game = initializeGame(numPlayers, h, num, &G);
			assertTrue(game, -1);
			memset(&G, 23, sizeof(struct gameState));
		}
		//set the kingdom cards
		int *k;
		k = setKingdomCards();

		// initialize a game state and player cards
		game = initializeGame(numPlayers, k, num, &G);
		//assert that the game can run
		while(game != 0) {
			assertTrue(game, -1);
			numPlayers = randomizePlayers();
			//clears game
			memset(&G, 23, sizeof(struct gameState));
			printf("Not able to initialize game!\n");
			// initialize a game state and player cards
			game = initializeGame(numPlayers, k, num, &G);
		}
		
		for(i=0; i < n; i++) {
			prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
		}
		
		int prevHandCount = G.handCount[player];
		int prevDeckCount = G.deckCount[player];
		int prevHandCountP2 = G.handCount[1];
		int prevDeckCountP2 = G.deckCount[1];
		
		//get the hand position that smithy is in
		int handpos = randHandPos(G.handCount[player]);

		if(functionCall == 1) {
			smithyCard(&G, handpos);
		}
		else{
			//the choices should not matter with this card. 
			int choice1 = rand() %3, choice2 = rand() %3, choice3 = rand() %3, bonus = rand() %3;
			cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
		}
		printf ("--------------------Testing in Hand Card Amount---------------------\n\n");
		printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount+3-1);
		assertTrue(G.handCount[player], prevHandCount+3-1);

		printf ("--------------------Testing in Cards are from own pile---------------------\n\n");
		printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount-3);
		assertTrue(G.deckCount[player], prevDeckCount-3);
		
		printf ("--------------------Testing Hand count for other player has not changed---------------------\n\n");
		printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2);
		assertTrue(G.handCount[1], prevHandCountP2);

		printf ("--------------------Testing Deck count for other player has not changed---------------------\n\n");
		printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);
		assertTrue(G.deckCount[1], prevDeckCountP2);
		
		printf ("--------------------Testing the victory piles and kingdom card piles have not changed---------------------\n\n");
		
		for(i=0; i < n; i++) {
			assertTrue(prevCardPilesAmnt[i], G.supplyCount[cardPiles[i]]);
		}
		printf("\n ALL TESTS COMPLETED\n");
		
		//clears game
		memset(&G, 23, sizeof(struct gameState));
	}
	return 0;
}
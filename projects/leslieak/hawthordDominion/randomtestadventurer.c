#include "dominion.h"
#include "dominion_helpers.h"
#include "test.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

int main() {
	srand(time(NULL)); 
	printf("Random testing adventurer\n\n");
	struct gameState G, testG;
	int l;
	for(l =0; l < 11; l++) {
		int num = rand() % 51;
		//choose which function call to use
		int functionCall = rand() % 2;

		//randomize the amount of players available in the game.
		int numPlayers = randomizePlayers();
		
		//the choices and bonus should not effect this cards.
		int choice1 = rand() %3, choice2 = rand() %3, choice3 = rand() %3, bonus = rand() %3;
		
		//whose turn it is numPlayer since player number starts @ 0.
		int player = rand() % numPlayers;
		//counters
		int i, j;
		int game;
		//victory and kingdom cards to determine they have not been changed during the function call (in the supply).
		int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province};
		int n = sizeof(cardPiles) / sizeof(int);
		int prevCardPilesAmnt[n];
		
		//base case when all kingdom cards are set to the same value.
		if(l == 0) {
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
			//whose turn it is numPlayer since player number starts @ 0.
			player = rand() % numPlayers;
		}

		printf("Number of players: %d, player %d\n", numPlayers, player);
		//initialize previous supply card counts to determine they haven't changed after.
		for(i=0; i < n; i++) {
			prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
		}

		int treasureAmnt = 0, discardAmnt=0;
		//randomize the cards in the deck & amount of cards in the deck
		G.deckCount[player] = randDeckCount();
	    //changing players deck
	    for (j = 0; j < G.deckCount[player]; j++) {
		  	G.deck[player][j] = randCard();
		  	//determine the amount of treasure cards available in deck.
		  	if((treasureAmnt < 3) && (G.deck[player][j] != silver) && (G.deck[player][j] != copper) && (G.deck[player][j] != gold)) {
		  		discardAmnt++;
		  	}
		  	if((G.deck[player][j] == silver) || (G.deck[player][j] == copper) ||(G.deck[player][j] == gold)){
		  		treasureAmnt++;
		  	}
		}

		//randomize the cards in the hand 
		G.handCount[player] = randHandCount();
		for (j = 0; j < G.handCount[player]; j++) {
		  	G.hand[player][j] = randCard();
		  	if(j==0) {
		  		G.hand[player][j] = adventurer;
		  	}
		}

		//randomize the cards in discard
		G.discardCount[player] = randDeckCount();
		for (j = 0; j < G.discardCount[player]; j++) {
			G.discard[player][j] = randCard();
		}

		//retrieve the previous values
		memcpy(&testG, &G, sizeof(struct gameState));

		//calling the functions
		if(functionCall == 1) {
			int drawntreasure = 0;
			int z[200];
			int cardDrawn = 0;
			adventurerCard(&G, cardDrawn, drawntreasure, z);
		} 
		else{
			cardEffect(adventurer, choice1, choice2, choice3, &G, randHandPos(G.handCount[player]), &bonus);
		} 

		int toAdd = 0;
		//determine if cards in player's hands have changed
		if(treasureAmnt >= 1){
			if(treasureAmnt == 1) {
				toAdd = 1;
			}
			else{
				toAdd = 2;
			}
		}

		//check if amount in player hand has changed. 
		printf("Player: hand count = %d, expected = %d\n", G.handCount[player], testG.handCount[player]+toAdd-1);
		assertTrue(testG.handCount[player]+toAdd-1, G.handCount[player]);
		
		//check if discard pile has changed (of player)
		printf("Player: discard count = %d, expected = %d\n", G.discardCount[player], testG.discardCount[player]+discardAmnt);
		assertTrue(G.discardCount[player], testG.discardCount[player]+discardAmnt);
		
		//check if deck has changed -- if there is a change in the 
		printf("Player: deck count = %d, expected = %d\n", G.deckCount[player], testG.deckCount[player]-discardAmnt-toAdd);
		assertTrue(G.deckCount[player], testG.deckCount[player]-discardAmnt-toAdd);

		//amount of treasure cards in deck has changed.
		int newTreasureAmnt = 0;
	    for (j = 0; j < G.deckCount[player]; j++) {
		  	//determine the amount of treasure cards available in deck.
		  	if((G.deck[player][j] == silver) || (G.deck[player][j] == copper) ||(G.deck[player][j] == gold)){
		  		newTreasureAmnt++;
		  	}
		}
		printf("Treasure card in deck count = %d, expected = %d\n", newTreasureAmnt, treasureAmnt-toAdd);
		assertTrue(newTreasureAmnt, treasureAmnt-toAdd);

		//check if hand for other players have not changed
		for(i=0; i < numPlayers; i++){
			if(i != player) {
				printf("Player %d: hand count = %d, expected = %d\n", i, G.handCount[i], testG.handCount[i]);
				assertTrue(testG.handCount[i], G.handCount[i]);
			}
		}
		

		//check that deck for other player has not changed
		for(i=0; i < numPlayers; i++){
			if(i != player) {
				printf("Player %d: deck count = %d, expected = %d\n", i, G.deckCount[i], testG.deckCount[i]);
				assertTrue(testG.deckCount[i], G.deckCount[i]);
			}
		}
		//check that the victory and kingdom cards have not changed (in supply).
		for(i=0; i < n; i++) {
			printf("Supply count = %d, expected = %d\n", G.supplyCount[cardPiles[i]], testG.supplyCount[cardPiles[i]]);
				assertTrue(testG.supplyCount[cardPiles[i]], G.supplyCount[cardPiles[i]]);
		}

		printf("\n ALL TESTS COMPLETED\n");
		
		//clears game
		memset(&G, 23, sizeof(struct gameState));
		memset(&testG, 23, sizeof(struct gameState));
	}
}

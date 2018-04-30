#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//unit test 1 tests the buyCard function in dominion.c
//according to documentation: Validates the card being played can be played then calls cardEffect to play the
//card. In actual implemenation it does not call cardEffect.
int main(int argc, char *argv[])
{
	//kingdom cards that will be available in the game.
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numPlayers = 2;
    int p, i, r, success, j, badVal;
    int acceptable =0;
    int tests = 0;
    int inSupply = k[1];
    //create a supply array, one will have a kingdom card available to buy. The other will not.
    int supplyPos[3] = {inSupply, minion, copper};
    for(i=0; i < 3; i++) {
        printf("%d\n", supplyPos[i]);
    }
    int coin[2] = {0, 50};
   // int prevNumBuys, prevCoins, prevSupplyCount, prevDiscard;
    printf ("--------------------Testing buyCard---------------------\n\n");
   	    	printf("Kingdom cards available ");
    		for(i=0; i < 10; i++){
    			printf("%d ", k[i]);
    		}
    		printf("\n");



 //done to go through supplies
    for(j=0; j <3; j++) {
    //done to see with each player hand
    for (p = 0; p < numPlayers; p++)
    {

    //clears game
    memset(&G, 23, sizeof(struct gameState));
    //initializes game & player is given 1 numBuys value with initialization
    r = initializeGame(numPlayers, k, 50, &G);
    //varying numBuys values -> goes from 1 to 0
    do{
    //sets the amount of coins available to the player
    G.coins = coin[p];
    printf("\nPlayer has %d buys, %d coins, and is trying to buy card %d at cost %d\n", G.numBuys, G.coins, supplyPos[j], getCost(supplyPos[j]));

            //done to compare prevoius state of game with new state depending on if gainCard() has succeeded or failed
    int prevCoins = G.coins;
    int prevNumBuys = G.numBuys;
            int prevDiscardCount = G.discardCount[whoseTurn(&G)];
            int prevDiscard = G.discard[whoseTurn(&G)][
G.discardCount[whoseTurn(&G)] ];
            int prevSupplyCount = G.supplyCount[supplyPos[j]];
            //sets counter to see if test has passed
            badVal = 0;
    //supplyPos is changed according to which player is played
    success = buyCard(supplyPos[j], &G);

    if(success == -1) {
    printf("Card buy failed\n");
    //check if card is gained, check coins available, and numBuys left.
                if((getCost(supplyPos[j]) == 0) && (G.numBuys > 0)) {
                    printf("Cost is 0, number of buys is greater than 0. Should be able to buy card.\n");
                    badVal++;
                }
    if(prevNumBuys != G.numBuys) {
    printf("Number of buys was changed.\n");
                     badVal++;
    }
    if(prevCoins != G.coins) {
    printf("coin amount has changed\n");
                     badVal++;
    }
                if(prevSupplyCount != G.supplyCount[supplyPos[j]]){
                    printf("Amount of supply cards available has changed\n");
                     badVal++;
                }
                if(prevDiscardCount != G.discardCount[whoseTurn(&G)]){
                    printf("Discard pile count has changed\n");
                    badVal++;
                }
                if(prevDiscard != G.discard[whoseTurn(&G)][G.discardCount[whoseTurn(&G)] ]){
                    printf("Discard pile has added the card\n");
                    badVal++;
                }
                if (badVal == 0)
                {
                    acceptable++;
                }
    G.numBuys--;
    }
    if(success != -1) {
    printf("Card succeeded\n");
    //check if card is gained, check coins available, and numBuys left.
    if((prevNumBuys -1) != G.numBuys) {
    printf("Number of buys was not changed.\n");
                     badVal++;
    }
    if((prevCoins-(getCost(supplyPos[j]))) != G.coins) {
    printf("coin amount has not changed\n");
                     badVal++;
    }
                if(prevSupplyCount == G.supplyCount[supplyPos[j]]){
                    printf("Amount of supply cards available was not changed\n");
                     badVal++;
                }
                 if(prevDiscardCount == G.discardCount[whoseTurn(&G)]){
                    printf("Discard pile count has not changed\n");
                    badVal++;
                }
                if(prevDiscard != G.discard[whoseTurn(&G)][G.discardCount[whoseTurn(&G)] ]){
                    printf("Discard pile has not added the card\n");
                    badVal++;
                }
                if(badVal == 0) {
                    acceptable++;
                }
    }
    tests++;

            }while(G.numBuys >= 0);               
    	}
	}
    return 0;
}
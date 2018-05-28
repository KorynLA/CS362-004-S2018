//ambassador

//1.  take card from hand, and add 0,1, or 2 copies from the hand

//2. cards should be added to the Supply pile

//3. Players change their state to gain a copy of that card from the supply

//if added to supply when it is empty, the game does not end.

 

#include "dominion.h"

#include "dominion_helpers.h"

#include <string.h>

#include <stdio.h>

#include <assert.h>

#include "rngs.h"

 

int main(){

 printf("Testing Ambassador\n\n\n");

struct gameState G;

int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

int numPlayers = 2;

//choice 1 is card number

int handpos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;

//whose turn it is

int player = 0;

int i, j;

int acceptableCounter = 0, tests=0;

int prevDeckCountT, prevHandCountT, prevDiscardCount;
int prevCardPilesAmnt[16];

int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province, copper, silver, gold};

 

 

//clears game

memset(&G, 23, sizeof(struct gameState));

// initialize a game state and player cards

initializeGame(numPlayers, k, 50, &G);

 

//for previous values

int prevHandCount = G.handCount[player];

int prevDeckCount = G.deckCount[player];

prevDiscardCount = G.discardCount[player];

 

int prevHandCountP2 = G.handCount[1];

int prevDeckCountP2 = G.deckCount[1];

int prevDiscardCountP2 = G.discardCount[1];

for(i=0; i < 16; i++) {
	prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
}

 

 

//to discard is 0

cardEffect(ambassador, choice1, choice2, choice3, &G, handpos, &bonus);

 

printf ("\n******Testing choice discarding 0 cards from hand (2 players) ******\n\n\n");

 

printf ("--------------------Testing Hand count for player---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[player], prevHandCount-1); 
if(G.handCount[player] == prevHandCount-1){

                acceptableCounter++;

}

 

printf ("--------------------Testing Deck count for  player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount);

if(G.deckCount[player] == prevDeckCount){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for player has changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[player], prevDiscardCount+1);

if(G.discardCount[player] == prevDiscardCount+1){

acceptableCounter++;

}

 

 

printf ("--------------------Testing Hand count for other player has not changed---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2);

if(G.handCount[1] == prevHandCountP2){

acceptableCounter++;

}

 

printf ("--------------------Testing Deck count for other  player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);

if(G.deckCount[1] == prevDeckCountP2){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for other player has not changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[1], prevDiscardCountP2);

if(G.discardCount[1] == prevDiscardCount){

acceptableCounter++;

}

 

 

printf ("--------------------Testing all the supply piles have not changed---------------------\n\n");

for(i=0; i < 16; i++) {

tests++;

printf("Card = %d supply count = %d, expected = %d\n", cardPiles[i], G.supplyCount[cardPiles[i]], prevCardPilesAmnt[i]);

if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){

                acceptableCounter++;

}

}

printf ("\n******Testing choice as discarding 1 card from hand (2 players) ******\n\n\n");

 

//clears game

memset(&G, 23, sizeof(struct gameState));

// initialize a game state and player cards

initializeGame(numPlayers, k, 50, &G);

 

//for previous values

prevHandCount = G.handCount[player];

prevDeckCount = G.deckCount[player];

prevDiscardCount = G.discardCount[player]; 

prevHandCountP2 = G.handCount[1];

prevDeckCountP2 = G.deckCount[1];

prevDiscardCountP2 = G.discardCount[1];

 

for(i=0; i < 16; i++) {
	 prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
}

//to discard is 1

choice2 = 1;

cardEffect(ambassador, choice1, choice2, choice3, &G, handpos, &bonus);

 

 

printf ("--------------------Testing Hand count for player---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[player],  prevHandCount-2); if(G.handCount[player] == prevHandCount-2){

                acceptableCounter++;

}

 

printf ("--------------------Testing Deck count for  player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount);

if(G.deckCount[player] == prevDeckCount){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for player has changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[player], prevDiscardCount+1);

if(G.discardCount[player] == prevDiscardCount+1){

acceptableCounter++;

}

 

 

printf ("--------------------Testing Hand count for other player has changed---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2+1);

if(G.handCount[1] == prevHandCountP2+1){

acceptableCounter++;

}

printf ("--------------------Testing Deck count for  other player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);

if(G.deckCount[1] == prevDeckCountP2){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for other player has not changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[1], prevDiscardCountP2);

if(G.discardCount[1] == prevDiscardCount){

acceptableCounter++;

}

 

printf ("--------------------Testing the supply piles have not changed---------------------\n\n");

for(i=0; i < 16; i++) {

tests++;

printf("Card = %d supply count = %d, expected = %d\n", cardPiles[i], G.supplyCount[cardPiles[i]], prevCardPilesAmnt[i]);

if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){

                acceptableCounter++;

}

}

 

printf ("\n******Testing choice as discarding 2 cards from hand (2 players)  When all cards in hand are copper ******\n\n\n");

 

//clears game

memset(&G, 23, sizeof(struct gameState));

// initialize a game state and player cards

initializeGame(numPlayers, k, 50, &G);

 

//for previous values

prevHandCount = G.handCount[player];

prevDeckCount = G.deckCount[player];

prevDiscardCount = G.discardCount[player]; 

prevHandCountP2 = G.handCount[1];

prevDeckCountP2 = G.deckCount[1];

prevDiscardCountP2 = G.discardCount[1];

int prevSupplyCount = G.supplyCount[copper];

 

// create different deck for user
for (j = 0; j < 10; j++) {
	  		G.hand[player][j] = copper;
	  }
 

//to discard is 1
choice2 = 1;

cardEffect(ambassador, choice1, choice2, choice3, &G, handpos, &bonus);

 

 

printf ("--------------------Testing Hand count for player---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[player],  prevHandCount-3); if(G.handCount[player] == prevHandCount-3){

                acceptableCounter++;

}

 

printf ("--------------------Testing Deck count for  player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount);

if(G.deckCount[player] == prevDeckCount){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for player has changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[player], prevDiscardCount+1);

if(G.discardCount[player] == prevDiscardCount+1){

acceptableCounter++;

}

 

 

printf ("--------------------Testing Hand count for other player has changed---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[1], prevHandCountP2+1);

if(G.handCount[1] == prevHandCountP2+1){

acceptableCounter++;

}

printf ("--------------------Testing Deck count for other player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[1], prevDeckCountP2);

if(G.deckCount[1] == prevDeckCountP2){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count other for player has not changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[1], prevDiscardCountP2);

if(G.discardCount[1] == prevDiscardCount){

acceptableCounter++;

}

 

printf ("--------------------Testing the supply pile of copper has changed---------------------\n\n");

tests++;

printf("supply count = %d, expected = %d\n",  prevSupplyCount+1, G.supplyCount[copper]);

if(prevSupplyCount+1 == G.supplyCount[copper]){

                acceptableCounter++;

}

printf ("\n******Testing choice as discarding 1 cards from hand (3 players)  When all cards in hand are that card ******\n\n\n");

 

//clears game

memset(&G, 23, sizeof(struct gameState));

// initialize a game state and player cards

initializeGame(3, k, 50, &G);

 

//for previous values

prevHandCount = G.handCount[player];

prevDeckCount = G.deckCount[player];

prevDiscardCount = G.discardCount[player]; 

prevHandCountP2 = G.handCount[2];

prevDeckCountP2 = G.deckCount[2];

prevDiscardCountP2 = G.discardCount[2];

for(i=0; i < 16; i++) {
	prevCardPilesAmnt[i] = G.supplyCount[cardPiles[i]];
}

 // create different deck for user
for (j = 0; j < 10; j++) {
            G.hand[player][j] = copper;
      }

//to discard is 1

choice2 = 1;

cardEffect(ambassador,  choice1, choice2, choice3, &G, handpos, &bonus);

 

 

printf ("--------------------Testing Hand count for player---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[player],  prevHandCount-2); if(G.handCount[player] == prevHandCount-3){

                acceptableCounter++;

}

 

printf ("--------------------Testing Deck count for  player has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[player], prevDeckCount);

if(G.deckCount[player] == prevDeckCount){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for player has changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[player], prevDiscardCount+2);

if(G.discardCount[player] == prevDiscardCount+2){

acceptableCounter++;

}

 

 

printf ("--------------------Testing Hand count for player 3 has not changed---------------------\n\n");

tests++;

printf("hand count = %d, expected = %d\n", G.handCount[2], prevHandCountP2);

if(G.handCount[1] == prevHandCountP2){

acceptableCounter++;

}

printf ("--------------------Testing Deck count for player 3 has not changed---------------------\n\n");

tests++;

printf("deck count = %d, expected = %d\n", G.deckCount[2], prevDeckCountP2);

if(G.deckCount[1] == prevDeckCountP2){

acceptableCounter++;

}

 

printf ("--------------------Testing Discard count for player 3 has not changed---------------------\n\n");

tests++;

printf("discard count = %d, expected = %d\n", G.discardCount[2], prevDiscardCountP2);

if(G.discardCount[1] == prevDiscardCount){

acceptableCounter++;

}

 

printf ("--------------------Testing the supply piles have not changed---------------------\n\n");

for(i=0; i < 16; i++) {

tests++;

printf("Card = %d supply count = %d, expected = %d\n", cardPiles[i], G.supplyCount[cardPiles[i]], prevCardPilesAmnt[i]);

if(prevCardPilesAmnt[i] == G.supplyCount[cardPiles[i]]){

                acceptableCounter++;

}

}

   printf("\n%d/%d tests passed!\n", acceptableCounter, tests);

return 0;

}

 
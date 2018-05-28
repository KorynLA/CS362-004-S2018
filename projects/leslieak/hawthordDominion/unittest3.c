/*int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//Spec description: Validates the card being played can be played then calls cardEffect to play the
//card.
int main(){
  struct gameState G;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
   //cards to be checked
  int cardsToCheck[4] = {estate, copper, council_room, province};
  int numPlayers = 2;
  int acceptableCounter =0;
  int i, j;
  int tests = 0;
  printf ("--------------------Testing fullDeckCount---------------------\n\n");
  
    for(i=0; i < 3; i++) {
  //none of it in any deck
  tests++;
   //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game
  initializeGame(numPlayers, k, 50, &G);
for (j = 0; j < 10; j++) {
    G.hand[1][j] = cardsToCheck[i+1];
}
for (j = 0; j < 10; j++) {
  G.deck[1][j]= cardsToCheck[i+1];
      G.discard[1][j] =cardsToCheck[i+1];
     }

if(fullDeckCount(1, cardsToCheck[i], &G) == 0) {
acceptableCounter++;
}
  //only in deck count
tests++;
//clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game
  initializeGame(numPlayers, k, 50, &G);
G.handCount[1] = 10;
G.discardCount[1] = 10;
G.deckCount[1] = 10;
for (j = 0; j < 10; j++) {
    G.hand[1][j] = cardsToCheck[i+1];
}
for (j = 0; j < 10; j++) {
G.deck[1][j]= cardsToCheck[i+1];
if(j %2  == 0) {
  G.deck[1][j]= cardsToCheck[i];
  }
      G.discard[1][j] =cardsToCheck[i+1];
     }
     //there will be a result of 5
     if(fullDeckCount(1, cardsToCheck[i], &G) == 5) {
      acceptableCounter++;
     }

//in hand and discard
tests++;
//clears game
memset(&G, 23, sizeof(struct gameState));
//initializes game
initializeGame(numPlayers, k, 50, &G);
G.handCount[1] = 10;
G.discardCount[1] = 10;
G.deckCount[1] = 10;

for (j = 0; j < 10; j++) {
G.deck[1][j]= cardsToCheck[i+1];
}
for (j = 0; j < 10; j++) {
G.hand[1][j] = cardsToCheck[i+1];
G.discard[1][j] =cardsToCheck[i+1];
if(j %2 == 0) {
G.hand[1][j] = cardsToCheck[i];
  G.discard[1][j]= cardsToCheck[i];
  }
     }
     //there will be a result of 10
     if(fullDeckCount(1, cardsToCheck[i], &G) == 10) {
      acceptableCounter++;
     }
  //in all decks
tests++;
//clears game
memset(&G, 23, sizeof(struct gameState));
//initializes game
initializeGame(numPlayers, k, 50, &G);
G.handCount[1] = 10;
G.discardCount[1] = 10;
G.deckCount[1] = 10;

for (j = 0; j < 10; j++) {
G.deck[1][j]= cardsToCheck[i];
G.hand[1][j] = cardsToCheck[i];
  G.discard[1][j]= cardsToCheck[i];
}
     //there will be a result of 10
     if(fullDeckCount(1, cardsToCheck[i], &G) == 30) {
      acceptableCounter++;
     }
 }
printf("\n%d/%d tests passed!\n", acceptableCounter, tests);
  return 0;
}
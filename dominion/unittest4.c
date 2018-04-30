/*int isGameOver(struct gameState *state) {
  int i;
  int j;
  
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
  {
    j++;
  }
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}*/

 // int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//spec description: Checks the number of provinces or if three supply piles are empty to determine if
//the game is over.
int main(){
  struct gameState G;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  int numPlayers = 2;
  int acceptableCounter =0;
  int i;
  int tests = 4;
   printf ("--------------------Testing isGameOver---------------------\n\n");
  //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game & fills all supplies
  initializeGame(numPlayers, k, 50, &G);

//when province cards are empty & supply is filled
  G.supplyCount[province] = 0;
  if(isGameOver(&G) == 1) {
    acceptableCounter++;
  }
  else{
    printf("Game isn't over even though there are no province cards\n");
  }

//when supply is empty but province cards are empty
//clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game & fills all supplies
  initializeGame(numPlayers, k, 50, &G);
  for(i=0; i < 25; i++) {
    G.supplyCount[i] = 0;
  }
  if(isGameOver(&G) == 1) {
    acceptableCounter++;
  }
   else{
    printf("Game isn't over even though there are no supply cards left\n");
  }
//there are 3 empty deck supplies
  //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game & fills all supplies
  initializeGame(numPlayers, k, 50, &G);
  for(i=0; i < 25; i++) {
    G.supplyCount[i] = 1;
  }

  G.supplyCount[0] = 0;
  G.supplyCount[1] = 0;
  G.supplyCount[2] = 0;
   if(isGameOver(&G) == 1) {
    acceptableCounter++;
  }
   else{
    printf("Game isn't over even though there are 3 supply card decks empty\n");
  }

  //when province cards are filled and supply cards are filled
  memset(&G, 23, sizeof(struct gameState));
  //initializes game & fills all supplies
  initializeGame(numPlayers, k, 50, &G);
  if(isGameOver(&G) == 0) {
    acceptableCounter++;
  }
   else{
    printf("Game is over even though there are supply cards and province cards available.\n");
  }
  printf("\n%d/%d tests passed!\n", acceptableCounter, tests);
   return 0;
}

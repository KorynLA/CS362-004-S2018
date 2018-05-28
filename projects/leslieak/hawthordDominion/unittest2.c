#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Spec Description: Adds a specific card to a players hand, deck, or trash. Checks for enough
//supply of the card then puts the card in the directed location.
int main(){
  struct gameState G;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, minion, baron, great_hall};
  int numPlayers = 2;
  int acceptableCounter =0;
  int i;
  int tests = 0;
  printf ("--------------------Testing gainCard---------------------\n\n");
  //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game
  initializeGame(numPlayers, k, 50, &G);
  
  //gainCard(supplyPos, struct gameState *state, int toFlag, int player);
  //checks correctly if supply is empty or not (of card)
  //supply card to gain not in the pile: village
  assert(gainCard(village, &G, 0, 1) == -1);

//checks correctly if supply is empty or not 
  int j[10] = {};
  //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game 
  initializeGame(numPlayers, j, 50, &G);
  //set all supplies to 0 to see if function catches that
  G.supplyCount[estate] = 0;
  G.supplyCount[duchy] = 0;
  G.supplyCount[province] = 0;
  G.supplyCount[copper] = 0;
  G.supplyCount[silver] = 0;
  G.supplyCount[gold] = 0;
  G.supplyCount[curse] = 0;
 

//checks flags to determine if correct addition was done/ make sure all other states remained the same after.
for(i=0; i <4; i++) {
  tests++;
  printf("Testing flag %d\n", i);
 //clears game
  memset(&G, 23, sizeof(struct gameState));
  //initializes game 
  initializeGame(numPlayers, k, 50, &G);

  //set previous values to compare
  int prevDiscardCount = G.discardCount[whoseTurn(&G)];
  int prevDiscard = G.discard[whoseTurn(&G)][whoseTurn(&G)];
  int prevDeckCount = G.deckCount[whoseTurn(&G)];
  int prevDeck = G.deck[whoseTurn(&G)][whoseTurn(&G)];
  int prevHandCount = G.handCount[whoseTurn(&G)];
  int prevHand = G.hand[whoseTurn(&G)][whoseTurn(&G)];
  int prevSupplyCount = G.supplyCount[copper];
  //counters
  int discard =0;
  int hand = 0;
  int deck = 0;

///determine if gainCard was successful with enough supplies available.
  if(gainCard(copper, &G, i, whoseTurn(&G)) == 0) {

    //look if discard was changed -> 0
    if((prevDiscardCount != G.discardCount[whoseTurn(&G)]) && (prevDiscard != G.discard[whoseTurn(&G)][whoseTurn(&G)])){
      discard++;
    }

    //look if hand was changed -> 2
    if((prevHandCount != G.handCount[whoseTurn(&G)]) && (prevHand != G.hand[1][1])){
      hand++;
    }

    //look if deck was changed -> 1
    if((prevDeckCount != G.deckCount[whoseTurn(&G)]) || (prevDeck != G.deck[G.whoseTurn][G.whoseTurn])){
      deck++;
    }

    switch(i) {
      case 0:
        if((hand > 0) || (deck > 0)) {
          printf("Hand or deck was changed, when only the discard should have changed. \n");
        }
        if(discard == 0) {
          printf("Discard was not changed when it should have been.\n");
        }
        if((discard > 0) && (hand == 0) && (deck == 0)) {
          printf("Success!\n");
          acceptableCounter++;
        }
        break;
     case 1:
       if((hand > 0) || (discard > 0)) {
          printf("Hand or discard was changed, when only the deck should have changed. \n");
        }
        if(deck == 0) {
          printf("Deck was not changed when it should have been.\n");
        }
        if((deck > 0) && (hand == 0) && (discard == 0)) {
          printf("Success!\n");
          acceptableCounter++;
        }
        break;
      case 2:
       if((discard > 0) || (deck > 0)) {
          printf("Discard or deck was changed, when only the hand should have changed. \n");
        }
        if(hand == 0) {
          printf("Hand was not changed when it should have been.\n");
        }
        if((hand > 0) && (discard == 0) && (deck == 0)) {
          printf("Success!\n");
          acceptableCounter++;
        }
        break;
      case 3:
       if((hand > 0) || (deck > 0) || (discard > 0)) {
          printf("Hand, deck, or discard was changed, when nothing should have changed. \n\n");
        }
        if((discard == 0) && (hand == 0) && (deck == 0)) {
          acceptableCounter++;
          printf("Success!\n");
        }
        break;
    }
    //check supply
    if(G.supplyCount[copper] != prevSupplyCount-1) {
      printf("Supply amount was not changed.\n");
      tests++;
    }
    else{
      tests++;
      acceptableCounter++;
    }

  }
  else{
    printf("Failed for low supply-- but there was enough\n");
  }
  }
  printf("\n%d/%d tests passed!\n", acceptableCounter, tests);

  return 0;
}
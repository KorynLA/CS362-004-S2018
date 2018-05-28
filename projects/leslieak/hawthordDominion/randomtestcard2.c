//baron
//1. Current player can recieve 4 coins (with discard) or gain another estate card (in hand)
//2. estate card can be taken from victory pile 
//discard should not change if gains another estate card.
//increases player buys by 1
//3. No state change should occur for other players.
//4. No state change should occur to the kingdom card piles.

#include "dominion.h"
#include "test.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

void otherPlayer(struct gameState *orig, struct gameState *new, int player, int numPlayers, int functionCall, int choice1) {
    int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province, copper, silver, gold};
    int n = sizeof(cardPiles) / sizeof(int);
    int i;
    printf("Testing Baron\n\n");
    printf("Choice and function call\n", choice1, functionCall);
        //check if hand for other players have not changed
        //check the player new values
        printf("Player buys count = %d, expected = %d\n", new->numBuys, orig->numBuys+1); 
        assertTrue(new->numBuys, orig->numBuys+1);
        if(choice1 <= 0) {
            printf("Player coin count = %d, expected = %d\n", new->coins, orig->coins+4); 
            assertTrue(new->coins, orig->coins+4);
            //takes away estate and baron card
            printf("Player hand count = %d, expected = %d\n", new->handCount[player], orig->handCount[player]-2);
            assertTrue(new->handCount[player], orig->handCount[player]-2);
            printf("Player deck count = %d, expected = %d\n", new->deckCount[player], orig->deckCount[player]);
            assertTrue(new->deckCount[player], orig->deckCount[player]);
            printf("Player: discard count = %d, expected = %d\n", new->discardCount[player], orig->discardCount[player]+1);
            assertTrue(new->discardCount[player], orig->discardCount[player]+1);
            printf("Supply count of estate= %d, expected = %d\n", new->supplyCount[estate], orig->supplyCount[estate]);
            assertTrue(new->supplyCount[estate], orig->supplyCount[estate]);
        }
        else{
            printf("Player coin count = %d, expected = %d\n", new->coins, orig->coins); 
            assertTrue(new->coins, orig->coins);
            //takes away baron card and adds estate card
            printf("Player hand count = %d, expected = %d\n", new->handCount[player], orig->handCount[player]);
            assertTrue(new->handCount[player], orig->handCount[player]);
            printf("Player deck count = %d, expected = %d\n", new->deckCount[player], orig->deckCount[player]);
            assertTrue(new->deckCount[player], orig->deckCount[player]);
            printf("Player: discard count = %d, expected = %d\n", new->discardCount[player], orig->discardCount[player]);
            assertTrue(new->discardCount[player], orig->discardCount[player]);
            printf("Supply count of estate= %d, expected = %d\n", new->supplyCount[estate], orig->supplyCount[estate]-1);
            assertTrue(new->supplyCount[estate], orig->supplyCount[estate]-1);
        }
    for(i=0; i < numPlayers; i++) {
        if(i != player) {
            printf("Player %d: hand count = %d, expected = %d\n", i, new->handCount[i], orig->handCount[i]);
            assertTrue(orig->handCount[i], new->handCount[i]);
        }
    }

    //check that deck for other player has not changed
    for(i=0; i < numPlayers; i++){
        if(i != player) {
            printf("Player %d: deck count = %d, expected = %d\n", i, new->deckCount[i], orig->deckCount[i]);
            assertTrue(orig->deckCount[i], new->deckCount[i]);
        }
    }
    //check that the victory and kingdom cards have not changed (in supply).
    for(i=0; i < n; i++) {
        if(cardPiles[i] != estate) {
            printf("Supply count = %d, expected = %d\n", new->supplyCount[cardPiles[i]], orig->supplyCount[cardPiles[i]]);
            assertTrue(orig->supplyCount[cardPiles[i]], new->supplyCount[cardPiles[i]]);
        }
    }
    printf("\n ALL TESTS COMPLETED\n");
}

int main() {
    struct gameState G, testG;
    int cardPiles[] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, estate, duchy, province, copper, silver, gold};
    int n = sizeof(cardPiles) / sizeof(int);
    int m=0;
    int i, j, l;
    for(m =0; m < 10; m++) {
        int numPlayers = randomizePlayers(); 
        //choice 1 is the only one that should matter
        int choice1 = rand()%3-1, choice2 = 0, choice3 = 0, bonus = 0; 
        //whose turn it is 
        int player = rand() % numPlayers; 
        int functionCall = rand() % 2;
        int num = rand() % 51;
        //set the kingdom cards
        int *k;
        k = setKingdomCards();

        // initialize a game state and player cards 
        initializeGame(numPlayers, k, num, &G); 
        
        //randomize decks, hands, and discard
        //randomize the cards in the deck & amount of cards in the deck
        G.deckCount[player] = randDeckCount();
         //changing players deck
        for (j = 0; j < G.deckCount[player]; j++) {
            G.deck[player][j] = randCard();
         }
         //randomize the cards in the hand 
        G.handCount[player] = randHandCount();
        for (j = 0; j < G.handCount[player]; j++) {
            G.hand[player][j] = randCard();
            if(j==0) {
                G.hand[player][j] = baron;
            }
        }
        //randomize the cards in discard
        G.discardCount[player] = randDeckCount();
        for (j = 0; j < G.discardCount[player]; j++) {
            G.discard[player][j] = randCard();
        }
        G.numBuys = rand() % 50;
        G.coins = rand() % 50;

        //retrieve the previous values
        memcpy(&testG, &G, sizeof(struct gameState));
        //calling the functions
        if(functionCall == 1) {
 cardEffect(baron, choice1, choice2, choice3, &G, randHandPos(G.handCount[player]), &bonus);
        }
        else{
            cardEffect(baron, choice1, choice2, choice3, &G, randHandPos(G.handCount[player]), &bonus);
        } 

        //otherPlayer(&testG, &G, player, numPlayers, functionCall, choice1);
        memset(&G, 23, sizeof(struct gameState));
        memset(&testG, 23, sizeof(struct gameState));
    }
    return 0; 
}

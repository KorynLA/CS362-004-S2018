#ifndef _TEST_H
#define _TEST_H

#include "dominion.h"

void assertTrue(int a, int b);
int randomizePlayers();

//randomize hand count
int randHandCount();

//randomize kingdom cards available
enum CARD randKingdom();

//randomize handposition
//need to use numHandCards(struct gameState *state) beforehand
int randHandPos(int numHand);

//randomize deck count
int randDeckCount();

//randomly choose a card
enum CARD randCard();

//randomize discard count
int randDiscardCount();

//randomize played cards count
int randPlayedCount();
int * setKingdomCards();
#endif
int smithyFunction(struct gameState *state, int currentPlayer, int handPos) {
   //+3 Cards
  int i;
      for (i = 0; i < 4; i++)
  {
    drawCard(currentPlayer, state);
  }
      handPos = handPos-1;
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 1);
  return 0;
}

int adventurerFunction(struct gameState *state, int currentPlayer, int drawntreasure, int cardDrawn, int z){
  int temphand[200];
    while(drawntreasure<2){
  if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    shuffle(currentPlayer, state);
  }
  drawCard(currentPlayer, state);
  cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];//top card of hand is most recently drawn card.
  if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    drawntreasure++;
  else{
    temphand[z]=cardDrawn;
    state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    z++;
  }
      }
      while(z-1>=0){
  //state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
  z=z-1;
      }
  return 0;
}

int ambassadorFunction(int choice1, int choice2, int handPos, struct gameState *state, int currentPlayer) {
  int i;
  int j = 0;   //used to check if player has enough cards to discard

      if (choice1 > 2 || choice1 < 0)
  {
    return -1;        
  }

      if (choice1 == handPos)
  {
    return -1;
  }

      for (i = 0; i < state->handCount[currentPlayer]; i++)
  {
    if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
      {
        j++;
      }
  }
      if (j < choice2)
  {
    return -1;        
  }

      if (DEBUG) 
  printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

      //increase supply count for choosen card by amount being discarded
      state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;
      
      //each other player gains a copy of revealed card
      for (i = 0; i < state->numPlayers; i++)
  {
    if (i != currentPlayer)
      {
        gainCard(state->hand[currentPlayer][choice1], state, 0, i);
      }
  }

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);      

      //trash copies of cards returned to supply
      for (j = 0; j < choice2; j++)
  {
    for (i = 0; i < state->handCount[currentPlayer]; i++)
      {
        if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
    {
      discardCard(i, currentPlayer, state, 1);
      break;
    }
      }
  }     

  return 0;
}


int baronFunction(struct gameState *state, int currentPlayer, int choice1){
      state->numBuys++;//Increase buys by 1!
      if (choice1 > 0){//Boolean true or going to discard an estate
        int p = 1;//Iterator for hand!
        int card_not_discarded = 1;//Flag for discard set!
        while(card_not_discarded){
          if (state->hand[currentPlayer][p] == estate){//Found an estate card!
            state->coins += 4;//Add 4 coins to the amount of coins
            state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
            state->discardCount[currentPlayer]++;
            for (;p < state->handCount[currentPlayer]; p++){
              state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
            }
          state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
          state->handCount[currentPlayer]--;
          card_not_discarded = 0;//Exit the loop
          }
        else if (p < state->handCount[currentPlayer]){
          if(DEBUG) {
            printf("No estate cards in your hand, invalid choice\n");
            printf("Must gain an estate if there are any\n");
          }
          if (supplyCount(estate, state) > 0){
            gainCard(duchy, state, 0, currentPlayer);
            state->supplyCount[estate]--;//Decrement estates
            if (supplyCount(estate, state) == 0){
              isGameOver(state);
            }
          }
      card_not_discarded = 0;//Exit the loop
    }
          
    else{
      p++;//Next card
    }
  }
      }
          
      else{
  if (supplyCount(estate, state) > 0){
    gainCard(estate, state, 0, currentPlayer);//Gain an estate
    state->supplyCount[estate];//Decrement Estates
    if (supplyCount(estate, state) == 0){
      isGameOver(state);
    }
  }
      }
      
  return 0;
}
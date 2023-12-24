/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for (int i = 51; i > 0; i--)
  {
    int j = rand() % (i + 1); 
    int temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
  cout << type[id % 13] << "-" << suit[int(id / 13)];
  //type[id % 13] = card type
  //suit[int(id / 13)] = card suit
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int index = id % 13;
  return value[index];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for (int i = 0; i < numCards; i++)
  {
    printCard(hand[i]);
    cout << " ";
  }
  cout << "\n";
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum = 0;
  for (int i = 0; i < numCards; i++) //summing all cards in hand
  {
    sum += cardValue(hand[i]);
  }
  while (sum > 21)
  {
    for (int j = 0; j < numCards; j++)
    {
      if (hand[j] % 13 == 12) //if card is an ace, remove 10 from sum.
      {
        sum -= 10;
        if (sum == 21) //if sum = 21, player has backjack, exit function
        {
          return sum;
        }
      }
    }
    if (sum > 21) //after all aces are exhausted, return bust score
    {
      return sum;
    }
  }
  return sum; //return sum
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  char playagain = 'y'; //initialize game
  while (playagain == 'y') //while player presses yes to play again
  {
    for(int i = 0; i < NUM_CARDS; i++) // initializing cards
    {
    cards[i] = i;
    }
    //reset hands
    for(int i = 0; i < 9; i++){phand[i] = 0;}
    for(int i = 0; i < 9; i++){dhand[i] = 0;}
    //shuffle
    shuffle(cards);
    //initial deal
    phand[0] = cards[0];
    phand[1] = cards[2];
    dhand[0] = cards[1];
    dhand[1] = cards[3];
    //number of cards in player and dealer hand
    int pcards = 2;
    int dcards = 2;
    //print first hands
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << "\n";
    cout << "Player: ";
    printHand(phand, pcards);
    bool playerBusts = 0; //checking whether player busts
    //If player starts with Blackjack, dealer starts playing
    if (getBestScore(phand, pcards) == 21)
    {
      while (getBestScore(dhand, dcards) < 17)
      {
        dhand[dcards] = cards[dcards + pcards];
        dcards += 1;
      }
    }
    else //if player doesn't start with blackjack, player can hit or stay
    {
      char move = 's';
      cout << "Type 'h' to hit and 's' to stay:\n";
      cin >> move;
      while (move == 'h')
      {
        phand[pcards] = cards[dcards + pcards]; //add card to phand
        pcards += 1;
        cout << "Player: ";
        printHand(phand, pcards);
        if((getBestScore(phand, pcards)) == 21) //blackjack, dealer starts playing
        {
          move = 's';
        }
        else if (getBestScore(phand, pcards) > 21) //bust
        {
          cout << "Player busts\n";
          playerBusts = 1; //boolean set to true
          move = 's'; //dealer plays
        }
        else //another option
        {
          cout << "Type 'h' to hit and 's' to stay:\n";
          cin >> move;
        }
      }
      if (move != 's') //exits program if not hit or stay
      {
        abort();
      }
      if(!playerBusts) //if player doesn't bust, dealer starts playing
      {
        while (getBestScore(dhand, dcards) < 17) //dealer plays
        {
         dhand[dcards] = cards[dcards + pcards];
         dcards += 1;
        }
      }
    }
    //ending
    if (!playerBusts) //if player doesn't bust, dealer hand is shown
    {
      cout << "Dealer: ";
      printHand(dhand, dcards);
    }
    //if player score is higher and doesn't bust, OR dealer busts, player wins
    if ((getBestScore(phand, pcards) > getBestScore(dhand, dcards) && !playerBusts) || getBestScore(dhand, dcards) > 21)
    {
      if (getBestScore(dhand, dcards) > 21)
      {
        cout << "Dealer busts\n";
      }
      cout << "Win " << getBestScore(phand, pcards) << " " << getBestScore(dhand, dcards) << "\n\n";
    }
    //if player score is lower than dealer score OR player busts, player loses
    else if (getBestScore(phand, pcards) < getBestScore(dhand, dcards) || playerBusts)
    {
      cout << "Lose " << getBestScore(phand, pcards) <<  " " << getBestScore(dhand, dcards) << "\n\n";
    }
    //if none of the above conditions are true, the players tie
    else
    {
      cout << "Tie " << getBestScore(phand, pcards) <<  " " << getBestScore(dhand, dcards) << "\n\n";
    }
    cout << "Play again? [y/n]\n";
    cin >> playagain; //prompt user to play again
  }
  return 0; //end of program
}

#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
using namespace std;

//Card Set
string cards[] = {"1","2","3","4","5","6","7","8","9","10","Ace","Jack","Queen","King"};

//Stack of Cards
class Deck{
private:
Deck* head;
Deck* tail;
Deck* NextCard;
Deck* PrevCard;

public:
int cardNum = 0;
int score = 0;
string suite;
int suiteVal;

void setNextCard(Deck* node){
  NextCard = node;
}

void setPrevCard(Deck* node){
  PrevCard = node;
}

void setVal(string o){
  suite = o;
}

//Initialize Deck
Deck(){
  head = NULL;
  tail = NULL;
  NextCard = NULL;
  PrevCard = NULL;
}

//set head node
void setHead(Deck* node){
        head = node;
    }

//Set tail node
void setTail(Deck* node){
    tail = node;
}

//Add Card to Hand
void pullCard(string type){
  Deck* newcard = new Deck();
  newcard->setVal(type);
  newcard->setNextCard(NULL);
  newcard->setPrevCard(NULL);

  if (head == NULL) {
    setHead(newcard);
  }
  else {
    tail->setNextCard(newcard);
    newcard->setPrevCard(tail);
}
  setTail(newcard);
  cardNum+=1;
    }

//Dispaly what cards you have in hand
void showHand(){
  if(head != NULL){
  Deck* handNode = head;
    while(handNode != NULL){
      cout << handNode->suite << endl;
      if(handNode->suite == "Ace")
        cout << " +1 Card!" << endl;
      else if(handNode->suite == "Jack")
        cout << " -1 Card!" << endl;
      else if(handNode->suite == "Queen")
        cout << " -1 Face Card from opponent!" << endl;
      else if(handNode->suite == "King")
        cout << " +1 Card, -1 Face Card from opponent!" << endl;
          
      handNode = handNode->NextCard;
      }
    } 
  }

//Prints the value of top card
string cardVal(){
  string value;
  if(head != NULL){
    Deck* handNode = head;
    value = handNode->suite;
  }
  return value;
}

//Remove a card from deck
void discard(){
  if ( head != NULL){
    Deck* card = head;
    head = head->NextCard;
    if(head != NULL)
      head->PrevCard = NULL;
    else
      tail = NULL;
    delete card;
    cardNum--;
  }
}

//Remove Face cards from deck
void eliminate(){
  if(head != NULL){
  Deck* handNode = head;
    while(handNode != NULL){
      if(handNode->suite == "King")
        discard();
      else if(handNode->suite == "Queen")
        discard();
      else if(handNode->suite == "Jack")
        discard();
      else if(handNode->suite == "Ace")
        discard();
      handNode = handNode->NextCard;
      }
    } 
  }

//Add points
int addPoints(Deck& hand){
  string p = cardVal();
  if(p == "1")
    score+=1;
  else if(p == "2")
    score+=2;
  else if(p == "3")
    score+=3;
  else if(p == "4")
    score+=4;
  else if(p == "5")
    score+=5;
  else if(p == "6")
    score+=6;
  else if(p == "7")
    score+=7;
  else if(p == "8")
    score+=8;
  else if(p == "9")
    score+=9;
  else if(p == "10")
    score+=10;
  else if(p == "Ace"){
    pullCard(cards[rand()% 13]);
  }
  else if(p == "Jack"){
    discard();
  }
  else if(p == "Queen"){
    hand.eliminate();
  }
  else if(p == "King"){
    hand.discard();
    pullCard(cards[rand()% 13]);
  }
  else
    score = score;

  return score;
}

};

//Compare card values
void compareCard(string a, string b){
  if(a == b)
    cout << "Clash!!" << endl;
  else if(a > b)
    cout << "W" << endl;
  else if(b > a)
    cout << "L" << endl;
};




// Main Function
int main() {
  
  int turn;
  int maxTurns = 9;
  string card;
  string option;
  Deck HandB;
  Deck HandA;

  //Introduction
  cout << "***Welcome to Card Clash!***" << endl << endl;;
  cout << "In this turn-based game, you will face off against the computer, taking turns collecting cards trying to get the highest score based on the vaule of your han.d" << endl << endl;
  cout << "**Cards with a number represent how many pooints its worth" << endl << "i.e. Card with a 4 on it = 4 points" << endl << endl;
  cout << "**Aces allow you to pick up another card" << endl << endl;
  cout << "**Jacks allows you to remove a card from your hand" << endl << endl;
  cout << "**Queens force the opponent to remove a card from their hand, prioritizing special cards" << endl << endl;
  cout << "**Kings allow you to pick up another card from the deck and remove one from your opponenet's hand" << endl << endl;

  cout << "Ready...Begin!" << endl << endl << endl;

  //Game begin
  srand(time(NULL));
  for(int turn = 0; turn <= maxTurns; turn++){
    cout << "Turn " << turn + 1 << ": " << endl << endl;
    //Player Pulls card
    card = cards[rand() % 14];
    HandA.pullCard(card);
    if(card == "King" || card == "Ace"){
      card = cards[rand() % 14];
      HandA.pullCard(card);
    }
    else if(card == "Jack"){
      HandA.discard();
    }
    cout << "Player 1 Turn: You got a " << card;
    cout << endl;
    cout << "Continue?(C)" << endl;
    cin >> option;
    if(option == "C" || option =="Continue" || option =="c"){
      //Opponent pulls card
      card = cards[rand() % 14];
      HandB.pullCard(card);
      if(card == "King" || card == "Ace"){
        card = cards[rand() % 14];
        HandB.pullCard(card);
      }
      else if(card == "Jack"){
      HandB.discard();
    }
      cout << "Player 2 Turn: They got a " << card;
    }
    else {
      cout << "I'm sorry, what was that? ";
      cin >> option;
    }
    cout << endl << endl;
  };
  

  //Game Conclude
  cout << "OK! Let's take a look at your cards!" << endl << endl;

  cout << "Player's Hand: " << endl;
  HandA.showHand();
  cout << endl << endl;
  cout << "Opponent's Hand: " << endl;
  HandB.showHand();
  cout << endl << endl;

  for(int k = 1; k <= 10; k++){
    HandA.addPoints(HandB);
    HandB.addPoints(HandA);
    HandA.discard();
    HandB.discard();
  }

  cout << endl << "Your final score is: " << HandA.score << endl;
  cout << endl << "Opponent final score is: " << HandB.score << endl;

  if(HandA.score > HandB.score){
    cout << endl << endl;
    cout << "Congratulations! You win!";
  }
  else{
    cout << endl << endl;
    cout << "Sorry. You lose.";
      };
};


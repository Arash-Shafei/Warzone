#include <iostream>

//#include "Order.h"
#include "Order.h"
#include "Cards.h"
#include "GameEngine.h"
#include "CardsDriver.h"

using namespace std;

void testCards() {

	////Create some players
	Player_Demo* p1 = new Player_Demo();
	Player_Demo* p2 = new Player_Demo();
	Player_Demo* p3 = new Player_Demo();
	cout << endl;

	//For demo i will set deck size to 20
	Deck* myDeck = new Deck(20);

	//Create deck 
	myDeck->createDeck();

	//Player draw random card from deck, remove from deck, add to hand (3x for demo purposes)
	myDeck->draw(p1->players_hand);
	myDeck->draw(p2->players_hand);
	myDeck->draw(p3->players_hand);

	myDeck->draw(p1->players_hand);
	myDeck->draw(p2->players_hand);
	myDeck->draw(p3->players_hand);

	myDeck->draw(p1->players_hand);
	myDeck->draw(p2->players_hand);
	myDeck->draw(p3->players_hand);

	//Print the hand for each player
	p1->players_hand->printHand();
	p2->players_hand->printHand();
	p3->players_hand->printHand();

	//Play first card for player 1
	(p1->players_hand->getCards()->front())->play(p1->players_hand, myDeck, p1);


}
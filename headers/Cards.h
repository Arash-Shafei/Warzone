#pragma once
#include <iostream>
#include <vector>
#include "Order.h"


using namespace std;

class Hand;
class Deck;
class Player_Demo;

class Card {

private:
	string cardType;

public:

	Card();
	Card(string s);
	void play(Hand* someHand, Deck* someDeck, Player_Demo* somePlayer);
	string getCardName();

	friend ostream& operator << (ostream& strm, Card& o);
	Card& operator=(const Card& e);
	Card(const Card& e);
};


class Hand {
	//TODO: this should just be a vector that exists in player, not its own class
private:
	vector<Card*>* cards;

public:
	Hand();
	vector<Card*>* getCards();
	int getNumCards();
	void printHand();

	friend ostream& operator << (ostream& strm, Hand& o);
	Hand& operator=(const Hand& e);
	Hand(const Hand& e);
};


class Deck {

private:
	vector<Card*>* list_cards_in_deck;
	int deck_size;

public:
	Deck();
	Deck(int x);
	void draw(Hand* someHand);
	void createDeck();
	vector<Card*>* getDeck();

	friend ostream& operator << (ostream& strm, Deck& o);
	Deck& operator=(const Deck& e);
	Deck(const Deck& e);
};




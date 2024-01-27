#include "Cards.h"
#include "Order.h";



//
// Card class
//

class Player_Demo;

//Default Constructor
Card::Card() {
	cardType = "default";
}

//Parameterized constructor
Card::Card(string s) {
	cardType = s;
}

//Play the card
void Card::play(Hand* someHand, Deck* someDeck, Player_Demo* somePlayer) {
	cout << endl;
	int x = rand() % ((someDeck->getDeck()->size()) + 1);
	if (cardType == "Bomb") {
		cout << "Making bomb" << endl;
		somePlayer->player_order_list->add_to_order_list(new Bomb());
		someDeck->getDeck()->insert(someDeck->getDeck()->begin() + x, someHand->getCards()->front());
		someHand->getCards()->erase(someHand->getCards()->begin());
	}
	if (cardType == "Reinforcement") {
		cout << "Making Reinforcement" << endl;
		someDeck->getDeck()->insert(someDeck->getDeck()->begin() + x, someHand->getCards()->front());
		someHand->getCards()->erase(someHand->getCards()->begin());
	}
	if (cardType == "Blockade") {
		cout << "Making Blockade" << endl;
		somePlayer->player_order_list->add_to_order_list(new Blockade());
		someDeck->getDeck()->insert(someDeck->getDeck()->begin() + x, someHand->getCards()->front());
		someHand->getCards()->erase(someHand->getCards()->begin());
	}
	if (cardType == "Airlift") {
		cout << "Making Airlift" << endl;
		somePlayer->player_order_list->add_to_order_list(new Airlift());
		someDeck->getDeck()->insert(someDeck->getDeck()->begin() + x, someHand->getCards()->front());
		someHand->getCards()->erase(someHand->getCards()->begin());
	}
	if (cardType == "Diplomacy") {
		cout << "Making Diplomacy" << endl;
		somePlayer->player_order_list->add_to_order_list(new Negotiate());
		someDeck->getDeck()->insert(someDeck->getDeck()->begin() + x, someHand->getCards()->front());
		someHand->getCards()->erase(someHand->getCards()->begin());
	}
}

//Get the the card name (a.k.a the type)
string Card::getCardName() {
	return cardType;
}

//Stream Insertion Operator
ostream& operator << (ostream& strm, Card& o) {
	strm << "This card: " << o.getCardName() << endl;
	return strm;
}

//Assignment Operator
Card& Card::operator=(const Card& e) {
	this->cardType = e.cardType;
	return *this;
}

//Copy Constructor
Card::Card(const Card& e) {
	cardType = e.cardType;
}



//
// Deck class
//

//Default Constructor
Deck::Deck() {
	list_cards_in_deck = new vector<Card*>();
	deck_size = 5;
	cout << "Default deck created" << endl;
}

//Parameterized constructor
Deck::Deck(int x) {
	list_cards_in_deck = new vector<Card*>();
	deck_size = x;
	cout << "Empty deck of size " << x << " created" << endl;
	cout << endl;
}

//Randomly adding cards to the deck 
void Deck::createDeck() {
	//Ensuring that each card type is included in my deck due to RNG
	(*list_cards_in_deck).push_back(new Card("Bomb"));
	(*list_cards_in_deck).push_back(new Card("Reinforcement"));
	(*list_cards_in_deck).push_back(new Card("Blockade"));
	(*list_cards_in_deck).push_back(new Card("Airlift"));
	(*list_cards_in_deck).push_back(new Card("Diplomacy"));

	for (int i = 0; i < deck_size - 5; i++)
	{
		int j = rand() % 5;
		switch (j)
		{
		case 0:
			(*list_cards_in_deck).push_back(new Card("Bomb"));
			break;
		case 1:
			(*list_cards_in_deck).push_back(new Card("Reinforcement"));
			break;
		case 2:
			(*list_cards_in_deck).push_back(new Card("Blockade"));
			break;
		case 3:
			(*list_cards_in_deck).push_back(new Card("Airlift"));
			break;
		case 4:
			(*list_cards_in_deck).push_back(new Card("Diplomacy"));
			break;
		}
	}
	cout << "Initial cards added to deck" << endl;
	cout << endl;
}

//Drawing a card from the deck
void Deck::draw(Hand* someHand) {
	if ((*list_cards_in_deck).size() == 0)
	{
		cout << "Empty Deck" << endl;
		cout << endl;
		return;
	}
	else
	{
		int y = rand() % ((*list_cards_in_deck).size());

		(*(someHand->getCards())).push_back((*list_cards_in_deck).at(y)); // y=2 then 3rd card
		(*list_cards_in_deck).erase((*list_cards_in_deck).begin() + y); // y=2 then 3rd card	
		cout << "Player drew: " << (*(someHand->getCards())).back()->getCardName() << endl;
	}
}

//Getting a pointer to the Deck
vector<Card*>* Deck::getDeck() {
	return list_cards_in_deck;
}

//Stream Insertion Operator
ostream& operator << (ostream& strm, Deck& o) {
	strm << "This is your current deck" << endl;
	return strm;
}

//Assignment Operator
Deck& Deck::operator=(const Deck& e) {
	this->list_cards_in_deck = new vector<Card*>(*(e.list_cards_in_deck));
	this->deck_size = e.deck_size;
	return *this;
}

//Copy Constructor
Deck::Deck(const Deck& e) {
	this->list_cards_in_deck = new vector<Card*>(*(e.list_cards_in_deck));
	this->deck_size = e.deck_size;
}


//
// Hand class
//

//Default Constructor
Hand::Hand() {
	cards = new vector<Card*>();
	cout << "Hand created" << endl;
}

//Get the pointer to my list of cards of the player
vector<Card*>* Hand::getCards() {
	return (cards);
}

int Hand::getNumCards()
{
	return cards->size();
}

//Print the hand
void Hand::printHand() {
	cout << endl;
	cout << "Player hand" << endl;
	for (int i = 0; i < (*cards).size(); i++)
	{
		cout << i + 1 << ". " << (*((*cards).at(i))).getCardName() << endl;
	}
}

//Stream Insertion Operator
ostream& operator << (ostream& strm, Hand& o) {
	strm << "This is you hand" << endl;
	return strm;
}

//Assignment Operator
Hand& Hand::operator=(const Hand& e) {
	this->cards = new vector<Card*>(*(e.cards));
	return *this;
}

//Copy Constructor
Hand::Hand(const Hand& e) {
	this->cards = new vector<Card*>(*(e.cards));
}

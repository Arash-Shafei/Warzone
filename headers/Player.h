#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Order.h"
#include "Cards.h"

class Card;
class Hand;

//---------------- Player Class --------------//
class Player{

private:
    //  Data member
    int playerId;
   
    // Vector for territories owned
    std::vector<Territory*> territoriesOwned;

    // Pointer of type OrderList
    OrdersList *orders;

    // Pointer of type Hand that contains a vector of ptr of cards
    Hand *cards;

public:

    // constructors
    Player();
    Player(int playerId,std::vector<Territory*> territoriesOwned,OrdersList *orders,Hand *cards);
    Player(const Player &obj);

    // destructor
    ~Player();

    // Accessor methods
    int getPlayerId();
    std::vector<Territory *> getTerritoriesOwned();
    OrdersList *getOrders();
    Hand *getCards();


    // Mutator methods
    void setPlayerId(int playerId);
    void setTerritoriesOwned(std::vector<Territory *> territoriesOwned);
    void setOrders(OrdersList *orders);
    void setCards(Hand *cards);
    void addTerritoryOwned(Territory*);

    // toDefend method for the player to return territories to be defended
    std::vector<Territory *> toDefend();

    // toDAttack method for the player to return territories to be defended
    std::vector<Territory *> toAttack(Map *map);

    // issueOrder method to add the order to player's orderList
    void issueOrder(Order *order);

    //    Assignment operator
    Player &operator=(const Player &obj);

    //    Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Player &e);
   
};

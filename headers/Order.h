#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"

using namespace std;

class Hand;


//Order Baseclass
class Order {

private:
    bool* is_valid;
    bool* is_executed;
    int* order_type;
    string name;

public:
    Order();
    ~Order();

    void set_order_type_id(int id);
    int get_order_type_id();

    void set_validity_status(bool b);
    bool get_validity_status();

    void set_execute_status(bool b);
    bool get_execute_status();

    void setName(const string&);
    string get_order_name();

    friend ostream& operator << (ostream& strm, Order& o);
    Order& operator=(const Order& e);
    Order(const Order& e);
};

// Deploy Subclass
class Deploy : public Order {

public:
    Deploy();
    ~Deploy();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Deploy& deploy);
    Deploy& operator=(const Deploy& e);
    Deploy(const Deploy& e);
};

// Advance Subclass
class Advance : public Order {

public:
    Advance();
    ~Advance();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Advance& advance);
    Advance& operator=(const Advance& e);
    Advance(const Advance& e);
};

// Bomb Subclass
class Bomb : public Order {

public:
    Bomb();
    ~Bomb();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Bomb& bomb);
    Bomb& operator=(const Bomb& e);
    Bomb(const Bomb& e);
};

// Blockade Subclass
class Blockade : public Order {

public:
    Blockade();
    ~Blockade();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Blockade& blockade);
    Blockade& operator=(const Blockade& e);
    Blockade(const Blockade& e);
};

// Airlift Subclass
class Airlift : public Order {

public:
    Airlift();
    ~Airlift();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Airlift& airlift);
    Airlift& operator=(const Airlift& e);
    Airlift(const Airlift& e);
};

// Negotiate Subclass
class Negotiate : public Order {

public:
    Negotiate();
    ~Negotiate();

    void validate();
    void execute();

    friend ostream& operator << (ostream& strm, Negotiate& negotiate);
    Negotiate& operator=(const Negotiate& e);
    Negotiate(const Negotiate& e);
};



// OrdersList class
class OrdersList {

private:
    vector<Order*>* list_of_orders;

public:
    OrdersList();
    ~OrdersList();

    void add_to_order_list(Order* someOrder);
    void remove(Order* anOrder);
    void move(int old_position, int new_position);
    void printList();

    Order* get_order_from_list(int i);
    void execute_list();

    OrdersList& operator=(const OrdersList& e);
    OrdersList(const OrdersList& e);
};


class Player_Demo {

public:
    OrdersList* player_order_list;
    Hand* players_hand;

    Player_Demo();
    ~Player_Demo();
    void createOrder(int id);

    Player_Demo& operator=(const Player_Demo& e);
    Player_Demo(const Player_Demo& e);

};

#include <iostream>
#include <vector>
#include "../Headers/Player.h"


//--------------- Constructors ------------------//
Player::Player()
{
}


Player::Player(int playerId, std::vector<Territory *> territoriesOwned, OrdersList *orders,Hand *cards): playerId(playerId), territoriesOwned(territoriesOwned), orders(orders),cards(cards)
{        
}

//--------------- Copy Constructor ---------------//
Player::Player(const Player &obj) : playerId(obj.playerId), orders(new OrdersList(*obj.orders)) ,cards(new Hand(*obj.cards))
{
    for (int i = 0; i < obj.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(obj.territoriesOwned[i])));
    }
    
}

//--------------- Assignment Operator -------------// 
Player &Player::operator=(const Player &obj)
{
    this->playerId = obj.playerId;
    this->orders = new OrdersList(*(obj.orders));
    this->cards=new Hand(*(obj.cards));
    
    for (int i = 0; i < obj.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(obj.territoriesOwned[i])));
    }
        
    return *this;
}

//--------------- Player Destructor -----------------//
Player::~Player()
{

    delete orders;
    orders = nullptr;

    delete cards;
    orders= nullptr;
    
}


//-------------Accessor methods----------------//

int Player::getPlayerId()
{
    return playerId;
}

std::vector<Territory *> Player::getTerritoriesOwned()
{
    return territoriesOwned;
}

OrdersList *Player::getOrders()
{
    return orders;
}

Hand *Player::getCards()
{
    return cards;
}

//-------------Mutator methods-------------------//

void Player::setPlayerId(int playerId)
{
    this->playerId = playerId;
}

void Player::setTerritoriesOwned(std::vector<Territory *> territoriesOwned)
{
    this->territoriesOwned = territoriesOwned;
}

void Player::setOrders(OrdersList *orders)
{
    this->orders = orders;
}

void Player::setCards(Hand *cards)
{
    this->cards=cards;
}


// toAttack() method to return territories that should be attacked by player
std::vector<Territory *> Player::toAttack(Map *map)
{
    vector<Territory*> territoriesToAttack;

//    iterate through all adjacent territories to make them available for player to attack
    for (Territory *owned : getTerritoriesOwned())
    {
        for(Territory* terr : owned->getAdjacencies()){
            territoriesToAttack.push_back(terr);
        }        
    }
    
    return territoriesToAttack;
}

// method to return territories that should be defended by player
std::vector<Territory *> Player::toDefend()
{
    return this->getTerritoriesOwned();
}

//  issueorder() method to create the object of order and add it to orderList of players

void Player::issueOrder(Order* order) {
    WRITE_LOG("Issuing Order " + order->get_order_name() + 
        "to Player"+to_string(getPlayerId()));
}

/*OLD CODE
void Player::issueOrder(Map *map)
{

    int orderType;
    
    cout << "---------issueOrder--------" << endl;

    do {
        cout << "Player" << this->getPlayerId() << ", what order would you like to issue? " << endl;
        cout << "1. Deploy \n2.Advance \n3. Bomb \n4. Blockade \n5. Airlift \n6. Negotiate " << endl;

       // Player will give order he wants to execute
        cin >> orderType;
        switch (orderType) { ;
            // adding deploy order to the list of orders
            case 1: {
                cout << "Issuing deploy order..." << endl;
                orders->add_to_order_list(new Deploy());
                break;
            }
                // adding advance order to the list of orders
            case 2: {
                cout << "Issuing advance order..." << endl;
                orders->add_to_order_list(new Advance());
                break;
            }
                // adding bomb order to the list of orders
            case 3: {
                cout << "Issuing bomb order..." << endl;
                orders->add_to_order_list(new Bomb());
                break;
            }
                // adding blockade order to the list of orders
            case 4: {
                cout << "Issuing blockade order..." << endl;
                orders->add_to_order_list(new Blockade());
                break;
            }
                // adding Airlift order to the list of orders
            case 5: {
                cout << "Issuing airlift order..." << endl;
                orders->add_to_order_list(new Airlift());
                break;
            }
                // Issuing negotiate order
            case 6: {
                cout << "Issuing negotiate order..." << endl;
                orders->add_to_order_list(new Negotiate());
                break;
            }
            default: {
                cout << "Invalid !!!\n" << endl;

            }
        }
    }while(orderType>6);

}*/

//--------- stream insertion operator --------------//
 std::ostream &operator<<(std::ostream &out, const Player &e)
 {
     out << "\nPlayer" << e.playerId << ":" << endl;
     out << "Territories owned: " << to_string(e.territoriesOwned.size()) << endl;
     if (e.territoriesOwned.size() == 0) {
         out << "None" << endl;
     }else{
//     printing territories owned
         for (int i=0;i<e.territoriesOwned.size();i++){
             cout << e.territoriesOwned[i]->getName() << endl;
         }
     }
     //TODO someone help im tired
     /*
     out << "Cards in hand:"<< to_string(e.getCards().size()) << endl;
     if (e->cards-geysize() == 0) {
         out << "None" << endl;
     }
     else {
     for (int i = 0; i < e.cards.size(); i++) {
         cout << e.territoriesOwned[i]->getName() << endl;
     }*/
     return out;
 }

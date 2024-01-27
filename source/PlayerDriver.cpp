#include <iostream>
#include <list>
#include "Player.h"
#include "PlayerDriver.h"
#include "Map.h"
#include "Order.h"

using namespace std;

void testPlayers(){
    WRITE_LOG("Creating Test Map");
    // using Map class to test Player's features
    Map testMap = Map();
    testMap.setName("Example");

    // taking example territories
    //The player names should be more explicitly meaningful,
    //for readability

    //TODO: automatically assign +increment in constuctor
    // player ids
    const int player1 = 1;
    const int player2 = 2;
    const int player3 = 3;
    const int player4 = 4;
    const int player5 = 5;
    //arbitrary number of armies
    const int armies = 10;
    Territory* ter1 = new Territory("TestTerritory1", "TestContinent1", armies, player1);
    Territory* ter2 = new Territory("TestTerritory2", "TestContinent1", armies, player2);
    Territory* ter3 = new Territory("TestTerritory3", "TestContinent2", armies, player3);
    Territory* ter4 = new Territory("TestTerritory4", "TestContinent2", armies, player4);
    Territory* ter5 = new Territory("TestTerritory5", "TestContinent1", armies, player5);

    //  adding territories to map using addTerritory method
    testMap.addTerritory(ter2);
    testMap.addTerritory(ter3);
    testMap.addTerritory(ter4);
    testMap.addTerritory(ter5);

    // Adding adjacent territories to test toAttack() for the plalyer
    ter1->addAdjTerritory(ter3);
    ter1->addAdjTerritory(ter5);
    ter2->addAdjTerritory(ter1);
    ter2->addAdjTerritory(ter4);



    // Creating vector for territories owned for player
    vector<Territory*> territoriesOwnedTest;

    WRITE_LOG("Assigning Territories to Player 1")
    // giving some random territories to player
    territoriesOwnedTest.push_back(ter1);
    territoriesOwnedTest.push_back(ter2);
    territoriesOwnedTest.push_back(ter5);
    
    WRITE_LOG("Creating player 1, with an empty Hand and OrdersList")
    // Creating player object by assigning relevant information
    Player p(player1, territoriesOwnedTest, new OrdersList(), new Hand());

    // Taking territories that should be attacked using toAttack() method
    vector<Territory *> territoriesForAttack = p.toAttack(&testMap);

    // Taking territories that should be defended using toDefend() method
    vector<Territory *> territoriesOwnedgot = p.toDefend();


    // Printing territories to be defended , all territories that player owned just for now
    cout << "\nTerritories that need to be Defended:\n";
    for (int i=0;i<territoriesOwnedgot.size();i++){
        cout << territoriesOwnedgot[i]->getName() << "\n";
    }

    // Printing territories to be attacked , all territories that are adjacent to player's owned territories just for now
    cout << "\nTerritories that need to be attacked:\n";
    for (int i=0;i<territoriesForAttack.size();i++){
        cout << territoriesForAttack[i]->getName() << "\n";
    }

    // Creating object of order and adding it to player's order's list
    Order dummyOrder;
    p.issueOrder(&dummyOrder);

    cout << p;

}



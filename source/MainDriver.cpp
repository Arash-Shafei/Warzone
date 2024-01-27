
#include "MapDriver.h"
#include "PlayerDriver.h"
#include "CardsDriver.h"
#include "OrdersDriver.h"
#include "GameEngineDriver.h"
#include "Logger.h"
#include <iostream>

int main() {

	//test part1
	WRITE_LOG("Entering TestLoadMaps from main");
	testLoadMaps();
	//test part2
	WRITE_LOG("\nEntering TestPlayers from main");
	testPlayers();
	//test part3
	WRITE_LOG("\nEntering TestOrdersList from main");
	testOrdersList();
	//test part4
	WRITE_LOG("\nEntering TestCards from main");
	testCards();
	//test part5
	WRITE_LOG("\nEntering TestGameStates from main");
	testGameStates(); 
	
	

	std::cin.get();//keep the console from closing immediately in Visual Studio

}
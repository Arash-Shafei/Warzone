#include "GameEngine.h";
#include "GameEngineDriver.h"

void testGameStates() {

	// Creating our GameEngine object
	GameEngine* game_engine = new GameEngine();
	cout << "Game engine created" << endl;

	// Creating our States
	State* start = game_engine->createState("start");
	State* map_loaded = game_engine->createState("map_loaded");
	State* map_validated = game_engine->createState("map_validated");
	State* players_added = game_engine->createState("players_added");
	State* assign_reinforcement = game_engine->createState("assign_reinforcement");
	State* issue_orders = game_engine->createState("issue_orders");
	State* execute_orders = game_engine->createState("execute_orders");
	State* win = game_engine->createState("win");
	cout << "States created" << endl;


	//Creating our Transitions
	game_engine->createTransition(start, map_loaded, "loadmap");
	game_engine->createTransition(map_loaded, map_loaded, "loadmap");
	game_engine->createTransition(map_loaded, map_validated, "validatemap");
	game_engine->createTransition(map_validated, players_added, "addplayer");
	game_engine->createTransition(players_added, players_added, "addplayer");
	game_engine->createTransition(players_added, assign_reinforcement, "assigncountries");
	game_engine->createTransition(assign_reinforcement, issue_orders, "issueorder");
	game_engine->createTransition(issue_orders, issue_orders, "issueorder");
	game_engine->createTransition(issue_orders, execute_orders, "endissueorders");
	game_engine->createTransition(execute_orders, execute_orders, "execorder");
	game_engine->createTransition(execute_orders, assign_reinforcement, "endexecorders");
	game_engine->createTransition(execute_orders, assign_reinforcement, "endexecorders");
	game_engine->createTransition(execute_orders, win, "win");
	game_engine->createTransition(win, start, "play"); //demo
	game_engine->createTransition(start, win, "test");
	cout << "Transitions created" << endl;
	cout << endl;

	//set the start of game
	game_engine->currentState_of_Game = start;

	//Game Loop
	string user_input = "";

	while (user_input != "end")
	{
		cout << "You are currently at: " << game_engine->currentState_of_Game->stateName << endl;
		cout << "Enter Command" << endl;
		cin >> user_input;
		cout << endl;
		while (!game_engine->changeState(user_input))
		{
			cout << "incorrect command" << endl;
			cin >> user_input;
			cout << endl;
		}
	}
	cout << "Thanks for playing!" << endl;
	game_engine->gameOver();
}
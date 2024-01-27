#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class State {

public:
	string stateName;

	State();
	~State();
	State(string s);
	State(const State& e);
	State& operator=(const State& e);
	friend ostream& operator << (ostream& strm, const State& e);
};


class Transition {

public:
	State* current;
	State* next;
	string command;

	Transition();
	~Transition();
	Transition(State* initial, State* final, string cmd);
	Transition(const Transition& e);
	Transition& operator=(const Transition& e);
	friend ostream& operator << (ostream& strm, const Transition& e);
};



class GameEngine {

public:
	vector<Transition*>* vector_transitions;
	vector<State*>* vector_states;
	State* currentState_of_Game;

	GameEngine();
	~GameEngine();
	GameEngine(const GameEngine& e);
	GameEngine& operator = (const GameEngine& e);
	friend ostream& operator << (ostream strm, const GameEngine& e);

	State* createState(string s);
	void createTransition(State* initial, State* final, string cmd);
	bool changeState(string& cmd);
	void gameOver();


};

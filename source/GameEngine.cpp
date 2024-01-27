#include "GameEngine.h";
#include "GameEngineDriver.h"
//
// State Class
//

//Default Constructor
State::State() {
	stateName = "";
}

//Destructor
State::~State() {}

//Parameterized constructor
State::State(string s) : stateName(s) {
}

//Copy constructor
State::State(const State& e) {
	this->stateName = e.stateName;
}

//Assignment operator
State& State::operator=(const State& e) {
	this->stateName = e.stateName;
	return *this;
}

//stream insertion operator
ostream& operator << (ostream& strm, State& e) {
	strm << "Current State: " << e.stateName << endl;
	return strm;
}







//
// Transition Class
//

//Default constructor
Transition::Transition() {
	current = NULL;
	next = NULL;
	command = "";
}

//Destructor
Transition::~Transition() {}

//Parameterized constructor
Transition::Transition(State* currentState, State* finalState, string someCommand) {
	current = currentState;
	next = finalState;
	command = someCommand;
}

//Copy constructor
Transition::Transition(const Transition& e) {
	this->current = new State(*(e.current));
	this->next = new State(*(e.next));
	this->command = e.command;
}


//Assignment operator
Transition& Transition::operator=(const Transition& e) {
	this->current = new State(*(e.current));
	this->next = new State(*(e.next));
	this->command = e.command;
	return *this;
}

//Stream insertion operator
ostream& operator << (ostream strm, const Transition& e) {
	strm << "[From: " << e.current->stateName << ", To: " << e.next->stateName << "]" << endl;
	return strm;
}







//
// GameEngine Class
//

//Default constructor
GameEngine::GameEngine() {
	vector_transitions = new vector<Transition*>();
	vector_states = new vector<State*>();
	currentState_of_Game = NULL;
}

//Destructor
GameEngine::~GameEngine() {}

//Copy constructor
GameEngine::GameEngine(const GameEngine& e) {
	this->vector_transitions = new vector<Transition*>(*(e.vector_transitions));
	this->vector_states = new vector<State*>(*(e.vector_states));
	this->currentState_of_Game = new State(*(e.currentState_of_Game));
}

//Assignment operator
GameEngine& GameEngine::operator = (const GameEngine& e) {
	this->vector_transitions = new vector<Transition*>(*(e.vector_transitions));
	this->vector_states = new vector<State*>(*(e.vector_states));
	this->currentState_of_Game = new State(*(e.currentState_of_Game));
	return *this;
}
//Stream insertion operator
ostream& operator << (ostream strm, const GameEngine& e) {
	strm << "Current state is " << e.currentState_of_Game->stateName;
	return strm;
}

// Creating my STATES and returning them, so it can be assigned to a STATE object in main driver
State* GameEngine::createState(string s) {
	State* new_state = new State(s);
	(*vector_states).push_back(new_state);
	return new_state;
}

// Creating my TRANSITIONS and inserting them in my VECTOR of TRANSITIONS
void GameEngine::createTransition(State* initial, State* final, string cmd) {
	Transition* new_transition = new Transition(initial, final, cmd);
	(*vector_transitions).push_back(new_transition);
}


//Changing the STATE based on the input COMMAND, returns "true" if successful
bool GameEngine::changeState(string& cmd) {
	for (int i = 0; i < ((*vector_transitions).size()); i++)
	{
		if (currentState_of_Game->stateName == (*vector_transitions).at(i)->current->stateName &&
			cmd == (*vector_transitions).at(i)->command)
		{
			currentState_of_Game = (*vector_transitions).at(i)->next;
			cout << "Change State successful" << endl;
			return true;
		}
		else
		{
			if (currentState_of_Game->stateName == "win" && cmd == "end")
			{
				return true;
			}
		}
	}
	return false;
}

// Once the game is over, I deallocate everything
void GameEngine::gameOver() {
	delete currentState_of_Game;
	currentState_of_Game = NULL;
	cout << "CurrentState destroyed" << endl;

	for (int i = 0; i < (*vector_transitions).size(); i++)
	{
		delete (*vector_transitions).at(i);
		(*vector_transitions).at(i) = NULL;
	}
	delete vector_transitions;
	vector_transitions = NULL;
	cout << "vector transitions destroyed" << endl;

	for (int j = 0; j < (*vector_states).size(); j++)
	{
		// delete (*vector_states).at(j); //WHY DOES THIS LINE NOT WORK
		(*vector_states).at(j) = NULL;
	}
	delete vector_states;
	vector_states = NULL;
	cout << "vector states destroyed" << endl;
	cout << "GameEngine destroyed" << endl;
}


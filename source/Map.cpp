#include "Map.h"
#include "Constants.h"
#include "Logger.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm> // to use find
#include <iterator> // to use distance

//TODO: Global variable warning
//Logger logger;

using WZMap::bool_toString;
using WZMapLoader::open_sqrbracket;
using WZMapLoader::equal_sign;
using WZMap::is_pos_number;
using WZMap::max_territories;
using WZMap::max_adjacencies;
using WZMap::not_owned;

/*Continent equality operator
* Continents are equal if their names are equal*/
bool Continent::operator==(const Continent rhs) {
	return (name == rhs.name);
}
std::ostream& operator<<(std::ostream& o_stream, Continent const& c){
	o_stream << "Contient name :" << c.name << "," <<
		"territories: " << std::to_string(c.territories.size()) << "," <<
		"control bonus : " << c.bonus << "," <<
		"owner : " << std::to_string(c.owner);

		return o_stream;
}


/*
------------------------------------------------------------

	TERRITORY

------------------------------------------------------------
*/

/*					CONSTRUCTORS						*/
Territory::Territory(std::string name, const Continent* c) :visited(false), name(name), continent(c), armies(0),owner(not_owned), continentName(c->name) {

}
								
//Copy constructpr
Territory::Territory(const Territory& t) : visited(t.visited), name(t.name),continent(t.continent), armies(t.armies), owner(t.owner), continentName(t.continentName) {
//TODO check that the vectors copy 
}

//Constructor used for player tests
Territory::Territory(std::string tname, std::string continentname, int armies, int owner) :
	visited(false), name(tname),continentName(continentName), armies(armies), owner(owner) {
}

Territory::~Territory() { //TODO Territory Destructor
	
}


/*					PUBLIC METHODS						 */
/* Overloaded == operator 
* two territories are equal if their names match
* Can't have 2 different territories with the same name
*/

/*						OPERATORS							 */
bool Territory::operator==(const Territory& rhs){
	//TODO make sure this is accessing the right thing
	WRITE_LOG(" LHS name "+name +" == RHS name "+rhs.name)
	return (name == rhs.name);
}
Territory& Territory::operator=(const Territory& t){
	// TODO
	//should there be a null check
	return *this;
}

std::ostream& operator<<(std::ostream& o_stream, Territory const& t){
	o_stream << "Territory name: " << t.name << ", " <<
		"continent: " << t.continent->name << ", " <<
		"owner: " << std::to_string(t.owner) << ", " <<
		"armies: " << std::to_string(t.armies) << ", " <<
		"adjacent territories: " << std::to_string(t.adjacencies.size());
	return o_stream;
}

/*					GETTERS & SETTERS					 */
std::string Territory::getName(){
	return this->name;
}
std::vector<Territory*> Territory::getAdjacencies(){
	return this->adjacencies;
}

/*					PRIVATE METHODS						 */

bool Territory::addAdjTerritory(Territory* territory) {
	bool success = false;
	adjacencies.push_back(territory);
	return success;
}

/*
------------------------------------------------------------

	MAP

------------------------------------------------------------
*/

/*					CONSTRUCTORS						*/

Map::Map() :valid(false) {

	WRITE_LOG("Map default constructor");
}
Map::Map(const Map& m) : valid(m.valid), name(m.name), continents(m.continents), 
						 territories(m.territories) {
	//TODO this should copy territories and continents from vector class behaviour
	//TODO MAP Copy Constructor
	WRITE_LOG("Map copy constructor");
}
Map::~Map() { //TODO Map Destructor
	//delete territories
	WRITE_LOG("Map destructor");	
	for (auto c : continents) {
		delete c;
		c = NULL;
	}
	for (auto t : territories) {
		delete t;
		t = NULL;
	}

}



/*					PUBLIC METHODS						 */


bool Map::continent_exists(std::string s) {
	for (auto& c : continents) {
		if (c->name == s)
			return true;
	}
	return false;
}

Continent* Map::getContinent(const std::string& s) {
	for (auto& c : continents) {
		if (c->name == s)
			return c;
	}
	return nullptr;
}

bool Map::isValid(){
	return valid;
}

void Map::addTerritory(Territory* territory) {
	//TODO using new in maploader, is that a problem for deleting
	//for debugging
	//std::stringstream s_stream;
	//s_stream << *territory;
	//WRITE_LOG("map adding territory " + s_stream.str() );
	territories.push_back(territory);
}
void Map::addContinent(Continent* continent) {
	continents.push_back(continent);
}

void Map::test() {
	//function for looking at maps content
	std::stringstream s_stream;
	WRITE_LOG("Testing Map");
	s_stream << *this;//print map 
	WRITE_LOG(s_stream.str());
	s_stream.str(std::string()); //clear ss
	WRITE_LOG("Map Continents:");
	for (Continent* c : continents) {
		s_stream << *c;//print continent 
		WRITE_LOG(s_stream.str());
		s_stream.str(std::string()); //clear ss
	}
	WRITE_LOG("Map Territories:");
	for (Territory* t : territories) {
		s_stream << *t;//print territory 
		WRITE_LOG(s_stream.str());
		s_stream.str(std::string()); //clear ss
	}
}
void Map::printContinentList(){
	for (auto c : continents)
		std::cout << *c << std::endl;
}
void Map::printVisited(){
	for(auto t : territories)
		std::cout << t->name <<" - " << t->visited << std::endl;
}

/*					OPERATORS					 */
std::ostream& operator<<(std::ostream& o_stream, Map const& m) {

	o_stream << "Map name: " << m.name << ", " <<
		"valid :" << bool_toString(m.valid) << ", " <<
		"continents: " << std::to_string(m.continents.size()) << ", " <<
		"territories: " << std::to_string(m.territories.size());

	return o_stream;
}
Map& Map::operator=(const Map& m){
	//TODO should this have null check
	return *this;
}

/*					GETTERS & SETTERS					 */

void Map::setName(std::string s) {
	name = s;
}

std::string Map::getName(){
	return std::string();
}


/*
	Depth First Search: A well known map searching algorithm. This is a helper function for the
	validate function. It will visit all the nodes it can from it's the starting node and mark them as visited.
	If it cannot visit one of the nodes and leaves it as unvisited this means that the map is not connected
*/


void Map::DFS(Territory* t) {
	t->visited = true;
	// Go through the adjacency
	for (auto it = t->adjacencies.begin(); it != t->adjacencies.end(); it++) {
		if (!(*it)->visited) {
			DFS(*it);
		}
	}
}

/*
   Similar to DFS but it will only visit territories that are in the same continent as the starting territory.
   Therefore if DFS does not reach one of the nodes in the continent (therefore leaving one of the continent's nodes
   as unvisited) then we know that it is not complete. We compare the returned int value to the number of actual
   nodes in a continent.
*/

void Map::DFS_Continent(Territory* t, Continent* c) {
	t->visited = true;
	// Iterates through the adjacent territories
	for (auto it = t->adjacencies.begin(); it != t->adjacencies.end(); it++) {
		if (!(*it)->visited && c->name.compare((*it)->continentName) == 0) { //if they are not visited and from the same continent
			DFS_Continent(*it, c);//we visit the chosen territory
		}
	}
}

void Map::resetVisited(){
	for (auto t : territories)
		t->visited = false;
}

bool Map::validate() {
	//Checks if entire map is connected
	//Use Depth First Search. We will mark every visited node as visited 	

	DFS(territories.front());
	for (Territory* t : territories) {
		if (!t->visited) {
			WRITE_LOG("Invalid Map " + name + ": territories are not a connected graph.");
			valid = false;
			return false;
		}
	}

	resetVisited();
	WRITE_LOG("Territories form a connected graph");
	for (Continent* c : continents)
	{
		DFS_Continent(c->territories.front(), c);
		for (Territory* t : c->territories) {
			if (!t->visited) {
				WRITE_LOG("Invalid Map " + name + ": continents are not connected subgraphs.");
				valid = false;
				return false;
			}
		}
		resetVisited();
	}

	WRITE_LOG("Continents form a connected graph");
	WRITE_LOG("Map "+ name+ " territories form a connected graph with connected continent subgraphs");
	valid = true;
	return true;
}
/*					PRIVATE METHODS						 */



/*
------------------------------------------------------------

	MAP LOADER

------------------------------------------------------------
*/
	// - - - MAP LOADER - - - //
	/*
	http://www.windowsgames.co.uk/conquest_create.html
	The .map file is just a text file which can be edited with simple programs like Notepad

	First section in the .map file:

	- describes what the name of the graphics file is
		- whether it wraps around like the World does (yes or no)
		- if you can scroll the map (horizontal, vertical or none)
		- your name as the author
		- set whether to show warnings if the game finds problems with the .map file.

	[Map]
	image=world.bmp
	wrap=yes
	scroll=horizontal
	author=Your name
	warn=yes

	Second section:

		- describes the Continent names
		- and the scores for owning them completely.

	The maximum number of continents that a map can have is 32

	[Continents]
	North America=5
	South America=2
	Africa=3
	Europe=5
	Asia=7
	Australia=2

	Final section describes the territories

		- First parameter is the territory's name,
		- 2nd the "x" and "y" coordinates of the center of the territory in pixels from the top left corner of the bitmap,
		- 3rd the continent that the territory is in
		- 4th list all the territories that this territory connects to.

	[Territories]
	Siam,270,139,Asia,China,India,Indonesia
	Japan,322,104,Asia,Kamchatka,Mongolia
	Ural,241,68,Asia,Siberia,China,Afghanistan,Ukraine

	The maximum number of territories that any territory can connect to is 10.
	The maximum number of territories that a map can have is 255.
	*/



/*					CONSTRUCTORS						*/

MapLoader::MapLoader() {
	WRITE_LOG("MapLoader default construtor") 		
}
MapLoader::~MapLoader(){
	WRITE_LOG("MapLoader destructor");
	if (inputFile.is_open()) {
		inputFile.close();
	}
}



/*					PUBLIC METHODS						 */

bool MapLoader::loadMap(const std::string& filename) {
	/*
	*Order is important
	Continents need to be populated before territories
	we dont use the information in the [map] section, so we find it or dont find it
	and it doesnt affect anything
	Implemented this way the sections need to be in order [continent] [territory]
	
	once the map was loaded sucessfully, it is tested as a connected graph by the map.validate method.

	*/
	//flags for if the [section header] was found
	bool fileFlag = false;
	bool mapFlag = false;
	bool continentFlag = false;
	bool territoryFlag = false;

	//TODO pass along exceptions
	//TODO should return empty map object if invalid

	WRITE_LOG("Loading map from file " + filename);
	fileFlag = openFile(filename);
	WRITE_LOG("File opened: " + bool_toString(fileFlag));

	mapFlag = loadMapSettings();
	WRITE_LOG("Map settings loaded: "+ bool_toString(mapFlag));

	continentFlag = loadContinents();
	WRITE_LOG("Continent settings loaded: " + bool_toString(continentFlag));

	territoryFlag = loadTerritories();
	WRITE_LOG("Territory settings loaded: " + bool_toString(territoryFlag));
	
	inputFile.close();//TODO: is this safe
	bool loaded_sections = (fileFlag && territoryFlag && continentFlag);
	WRITE_LOG("All settings loaded: " + bool_toString(loaded_sections));
	if (!loaded_sections) {
		//TODO: does it need to return empty map?
		WRITE_LOG("Map could not be loaded correctly - Returning");
		return loaded_sections;
	}

	
	return map.validate();
}

MapLoader& MapLoader::operator=(const MapLoader& ml){
	// todo Null check?
	return *this;
}
std::ostream& operator << (std::ostream& o_stream, MapLoader& ml) {

	o_stream << "Map name :" << ml.map.getName() << ", valid =" << bool_toString(ml.map.isValid());

		return o_stream;
}
/*					PRIVATE METHODS						 */

bool MapLoader::openFile(const std::string& file) {
	try {
		WRITE_LOG("Opening file");
		inputFile.open(file);

		if (!inputFile.is_open()) {
			WRITE_LOG("Map file could not be opened by MapLoader");
			return false;
		}
	}
	catch (const char* message) {//TODO: real error stuff
		std::cout << "An error has occured: \n" << message << std::endl;
	}
	return true;
}

bool MapLoader::loadMapSettings() {
	//this doesnt have to work so it does nothing
	bool success =true;
	const std::string noname = "No Name";
	const std::string section = "map";
	const char delim = '=';
	const char ext = '.'; // to remove file extension
	std::string line;

	if (!findSection(section)) {
		//doesnt matter if it doesnt exist
		map.setName(noname);
		WRITE_LOG( "Section " + section + " not found - continuing");
		return !success;
	}

	//TODO: what if name is empty?
	while (inputFile.peek() != open_sqrbracket && inputFile.peek() != EOF) {
		//TODO: Not solid
		//TODO: so messy
		std::string name;
		std::string value;

		getline(inputFile, line);
		size_t equal = line.find(delim);

		if (equal == std::string::npos) {
			continue;//not a valid line if theres no equals
			//for example a blank line will be skipped
		}
		if (line.size() < equal + 1) {
			//to avoid value = line.substr equal+1
			WRITE_LOG("Invalid setting " + name + " - value is blank");
			continue; //it doesnt matter
		}

		name = line.substr(0, equal);
		value = line.substr(equal+1);

		if (name.find("image") != std::string::npos){

			size_t end = value.find(ext);
			std::string mapname = (end != std::string::npos) ? value.substr(0,end): value;
			WRITE_LOG("Map name: " + mapname);
			map.setName(mapname);
			return success;
			
		}
		//TODO: what does peek do at the end of the file

	}
	map.setName(noname);
	return !success;
}

bool MapLoader::loadContinents(){
	//TODO: test is_number more 
	//TODO: Bonus should prob be an int not uint to make math easier

	bool success = true;
	const std::string section = "continents";
	const char delim = '=';
	std::string line;
	std::vector<std::string> names;
	std::vector<unsigned int> bonuses;

	if (!findSection("continents")){
		return !success;
	}

	while (inputFile.peek() != open_sqrbracket && inputFile.peek() != EOF) {
		
		std::string name;
		std::string value;
		unsigned int bonus; //cant be negative

		getline(inputFile, line);
		size_t equal = line.find(delim);

		if (equal == std::string::npos) { 
			//if theres no equals sign, its not a valid line
			continue;
		}
		if (names.size() == WZMap::max_continents) {
			WRITE_LOG("Invalid Map - Maximum number of continents is: " + WZMap::max_continents);
		}
		if (line.size() < equal + 1) {
			//to avoid value = line.substr equal+1
			WRITE_LOG("Invalid Continent " + name + " - bonus is blank");
			return !success;
		}

		name = formatInput(line.substr(0, equal));
		value = line.substr(equal + 1);

		if (name.size() == 0) {
			WRITE_LOG("Invalid Continent - name is blank");
			return !success;
		}

		if (!is_pos_number(value)) {
			WRITE_LOG("Invalid Continent " + name +" - bonus " + value + "is not a number.");
			return !success;
		}else {//TODO check that it is not too big to be an uint
			try {
				//TODO std::stoul doesnt have great checks
				//should report if out of range
				bonus =std::stoul(value.c_str(), nullptr, 10);
			}
			catch (std::out_of_range) {
				WRITE_LOG("Invalid Continent " + name + " - bonus " + value + "is out of the valid range (max = 255)");
				return !success;
			}
		}

		if (std::find(names.begin(), names.end(), name) != names.end()) {
			//Check if name is a duplicate - not allowed
			// == of continent  struct is based on their names.
			// im pretty sure " blah" wont be a duplicate of "blah" which is ugly but okay 
			// as long as string == does not return true
			// 
			//TODO: does this work if data.end is the one that matches
			WRITE_LOG("Invalid Continent - " + name + " is a duplicate");
			return !success;
		}
		
		names.push_back(name);
		bonuses.push_back(bonus);
		
	}
	for (int i = 0; i < names.size(); i++) {
		//TODO: Uses new
		Continent *c = new Continent();
		c->name = names[i];
		c->bonus = bonuses[i];
		c->owner = WZMap::not_owned;
		map.addContinent(c);
		//logger.WRITE_LOG("Added continent to map - " + c->name + " = " + std::to_string(c->bonus));
	}

	WRITE_LOG(std::to_string(names.size()) +" continents added to map.");
	
	return success;
		//TODO: what does peek do at the end of the file
}

bool MapLoader::loadTerritories(){

	bool success = true;
	const std::string section = "territories";
	std::string line;
	std::regex rgx(WZMapLoader::between_commas);
	std::vector<std::string> matches;

	std::vector<std::string> names;
	std::vector<Continent*> continents;
	std::vector<std::vector<std::string>> adjacent_t;

	int name_pos = 0;// territory name is first value on line
	//int x = 1; int y = 2; //not used 
	int continent_pos = 3;//continent is 4th value on line 
	int adjacent_pos = 4; //start of adjacent territory names, min 1, max of 10
	
	if (!findSection(section)) {
		//if territory section not found
		return !success;
	}
	while (getline(inputFile, line)) {

		if (line.find(',') == std::string::npos) {
			//if theres no comma, skip, its not a valid line
			continue;
		}			
		matches = split(line , ',');

		if (matches.size() < adjacent_pos) {
			//Protects against throwing an out of bounds error
			WRITE_LOG("Invalid territory initialisation list: " + line + ". Only has " + std::to_string(matches.size()) + "arguments (min " + std::to_string(adjacent_pos) + ").");
			return !success;
		}
		if (names.size() >= max_territories) {
		// doesnt check for duplicates before 
			WRITE_LOG("Territory could not be added: Maximum number of territories" + std::to_string(max_territories) + " exceeded.");
			return !success;
		}

		//put to lowercase, Arabia shouldnt be distinct from arabia
		std::string name = formatInput(matches[name_pos]);

		if (std::find(names.begin(), names.end(), name) != names.end()) {
			//Check if name is a duplicate - not allowed
			// im pretty sure " blah" wont be a duplicate of "blah" which is ugly but okay 
			// as long as string == does not return true
			WRITE_LOG("Invalid Territory - " + matches[name_pos] + " is a duplicate ");
			return !success;
		}
		//check if is valid after more basic checks.
		// store lowercase
		
		names.push_back(name);
		//check if continent is valid

		std::string cname = formatInput(matches[continent_pos]);


		Continent* c = map.getContinent(cname);
		if (c==nullptr) {//if continent does not exist
			//TEST
			map.printContinentList();
			WRITE_LOG("Invalid Territory - Continent " + matches[continent_pos] + " does not exist");
			return !success;
		}
		continents.push_back(c);
		std::vector<std::string> adj_list;

		//Requirement on Warzone website: Territories can only have 10 adjacencies
		//Assignment 1 says any number of adjacencies
		/*
		if (matches.size() - adjacent_pos > 10) {
			//territories can only have 10 adjacencies
			WRITE_LOG("Invalid territory " + name+ ": exceeded maximum of " + std::to_string(max_adjacencies) + " adjacent territories.");
			return !success;
		}*/

		for (int i = adjacent_pos; i < matches.size(); i++) {
			//populate adjacent territories with lowercased version
			std::string adj_name = formatInput(matches[i]);
			adj_list.push_back(adj_name);
		}
		//check for the territory name in the list
		if (std::find(adj_list.begin(), adj_list.end(), name) != adj_list.end()) {
			//check if name is included in adjacency list;
			//territory shouldnt be adjacent to itself
			WRITE_LOG("Invalid Territory " +name +":  Cannot be adjacent to itself ");
			return !success;
		}
		//uncomment to write every territory value
		//logger.WRITE_LOG("Territory: " + name + " on continent "+ c->name + "with "+ std::to_string(adj_list.size()) + "adjacent territories.");
		adjacent_t.push_back(adj_list);//by value because itll be overwritten
	}
	/*
	for (int i = 0; i < names.size(); i++) {
		//check if the adjacecy list contain valid territory names
		//TODO: this does not work
		std::vector<std::string> adj_list = adjacent_t[i];

		for (std::string t : adj_list) {
			//check if adjacent territory name in list of adj names
			//is it in the list of names

			// Iterator stores the position of searched element
			std::vector<std::string>::iterator it = std::find(adj_list.begin(), adj_list.end(), t);
			if (std::find(adj_list.begin(), adj_list.end(), t) != adj_list.end()) {
				//check if name is repeated;
				logger.WRITE_LOG("Invalid Territory " + names[i] + ": adjacency list contains duplicates");
				return false;
			}

		}
	}*/
	return initialise_territories(names,continents,adjacent_t);
}

bool MapLoader::findSection(const std::string& name) {

	/* Helper function to find section headers in file
	* Uses a regex to find words in brackets
	* Then sees if they match the header we are searching for
	* Seperated in this way to make it easy to ignore the case and whitespaces
	*
	* Note: if there are several section headers on the same line, it wont find the second
	*
	returns success(true) if found, otherwise !success(false)
	*/

	bool success = true;
	std::regex rgx(WZMapLoader::in_sqrbrackets);
	std::smatch matches;
	std::string line;
	std::string match;

	while (getline(inputFile, line)){

		if (std::regex_search(line, matches, rgx)){
			//the fist match, matches[0]' will be "[map", but matches[1] will be "map""
			if (matches.size() < 2) {
				//Protects against throwing an error matches[1] if somehow the matches is size 1
				//for now just moves on
				WRITE_LOG("Invalid Header: " + line);
			}
			
			match = formatInput(matches[1]);
			std::regex r(match);

			if (std::regex_match(name, r)) {
				WRITE_LOG("Header found in line: " + line);
				return success;
			}
		}
	}
	return (!success); //got to EOF without finding header
}
	
			
void MapLoader::toLowercase(std::string& s) {//TODO make sure this is ok to pass by value vs returning a copy
	/* Changes string case in place*/
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
}
std::string MapLoader::trimWhitespace(const std::string& s){
	/*trims leading and trailing whitespace
	* finds first and last non whitespace
	* finds the length 
	* then returns the substring
	*/
	const std::string whitespace = " \t"; // spaces and tabs
	const auto begin = s.find_first_not_of(whitespace);
	if (begin == std::string::npos) //empty string
		return "";
	const auto end = s.find_last_not_of(whitespace);
	return s.substr(begin, end-begin+1);
}

std::string MapLoader::formatInput(const std::string& s) {
	/*format input for consistency- remove leading and trailing whitespace 
	and put it to lowercase*/
	std::string result = trimWhitespace(s);
	toLowercase(result);
	return (result);

}
std::vector<std::string> MapLoader::split(const std::string& line, char deliminator){
		// if there is a line 
		// "duck, quack, quacky"
		//  ^   ^
		// start = 0  end = 4
		// finds comma at position = 4
		// so the substr(0, 4) is "duck"
		// start = 4+1 
		// 
		// "duck, quack, quacky"
		//       ^     ^
		// start = 5  end =11
		// finds comma at position = 11
		// so the substr(5,11) is " quack"
		// start = 11+1
		// 
		// "duck, quack, quacky"
		//              ^
		//				start =12
		// end = npos (no more commas found)
		// size of the string:20 (last position is 19)
		// 20 > 12  
		// subst(12, 19) is " quacky"
	std::vector<std::string> tokens;
	
	if (line.empty()) {
		return tokens;
	}

	size_t start = 0, end = 0;
	while ((end = line.find(deliminator, start)) != std::string::npos){

		tokens.push_back(line.substr(start, end - start));
		start = end + 1;
	}
	if (line.size()> start) {
		tokens.push_back(line.substr(start, line.size()-1));
	}

	return tokens;
}



bool MapLoader::initialise_territories(std::vector<std::string>& names, std::vector<Continent*>&continents, std::vector<std::vector<std::string>> adjacent_t){
	/*
	These territories have been checked for validity
	(minus is the map connected using these adjacencies)
	
	Poplulate the territory lists
	*/
	bool success = true;
	std::vector<Territory*> territories;

	for (int i = 0; i < names.size(); i++) {
		Continent* c = continents[i];
		//create the valid territory
		//TODO: uses new here		
		Territory* t = new Territory(names[i],c);
		territories.push_back(t);
		//add territory pointer to its continent's territory list
		c->territories.push_back(t);
		//add territory pointer to the map's territory list
		map.addTerritory(t);
	}

	for (int i = 0; i < territories.size(); i++) {
		Territory* t = territories[i];
		std::vector<std::string> adj_list= adjacent_t[i];

		for(std::string t_name : adj_list){
			//get index of adjacent territory in names list
			auto position = find(names.begin(),names.end(), t_name );
			int index = distance(names.begin(), position);
			territories[i]->addAdjTerritory(territories[index]);

		}
	}
	return success;
}



/*
int main() {

	Map mp = Map("Example");//70,126,North America,Northwest Territory,Alberta,Kamchatka
	Territory alaska = Territory("Alaska", "North America", 1, 0);
	Territory NT = Territory("Northwest Territory", "a", 1, 1);
	Territory alb = Territory("Alberta", "North America", 3, 2);
	Territory greenland = Territory("Greenland", "North America", 4, 2);
	Territory ontario = Territory("Ontario", "North America", 5, 2);
	Territory quebec = Territory("Quebec", "a", 2, 2);
	Territory wUS= Territory("Western United States", "a", 2, 2);
	Territory eUS = Territory("Eastern United States", "North America", 2, 2);
	Territory cAmerica = Territory("Central America", "North America", 2, 2);
	
	alaska.addAdjTerritory(&NT);
	alaska.addAdjTerritory(&alb);
	mp.addTerritory(&alaska);

	NT.addAdjTerritory(&alaska);
	NT.addAdjTerritory(&alb);
	NT.addAdjTerritory(&ontario);
	NT.addAdjTerritory(&greenland);
	mp.addTerritory(&NT);

	alb.addAdjTerritory(&alaska);
	alb.addAdjTerritory(&NT);	
	alb.addAdjTerritory(&ontario);
	alb.addAdjTerritory(&wUS); 
	mp.addTerritory(&alb);

	greenland.addAdjTerritory(&NT);
	greenland.addAdjTerritory(&ontario);
	greenland.addAdjTerritory(&quebec); 
	mp.addTerritory(&greenland);

	ontario.addAdjTerritory(&greenland);
	ontario.addAdjTerritory(&NT);
	ontario.addAdjTerritory(&alb);
	ontario.addAdjTerritory(&quebec);
	ontario.addAdjTerritory(&wUS);
	ontario.addAdjTerritory(&eUS);
	mp.addTerritory(&ontario);

	wUS.addAdjTerritory(&alb);
	wUS.addAdjTerritory(&ontario);
	wUS.addAdjTerritory(&eUS);
	wUS.addAdjTerritory(&cAmerica);
	mp.addTerritory(&wUS);

	eUS.addAdjTerritory(&ontario);
	eUS.addAdjTerritory(&quebec);
	eUS.addAdjTerritory(&wUS);
	eUS.addAdjTerritory(&cAmerica);
	mp.addTerritory(&eUS);

	cAmerica.addAdjTerritory(&wUS);
	cAmerica.addAdjTerritory(&eUS);
	mp.addTerritory(&cAmerica);

	quebec.addAdjTerritory(&ontario);
	quebec.addAdjTerritory(&greenland);
	quebec.addAdjTerritory(&eUS);
	mp.addTerritory(&quebec);

	Continent a = { {&NT, &wUS, &quebec}, 2, "a"};
	Continent NorthAmerica = { {&alaska, &alb, &greenland, &ontario, &cAmerica, &eUS}, 2, "North America" };
	//Continent b = { {&NT, &alb, &wUS, &quebec}, 2, "b" };
	mp.addContinent(&NorthAmerica);
	mp.addContinent(&a);
	mp.validate();

	return 0;
}*/
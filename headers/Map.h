#ifndef MAP_H // include guard
#define MAP_H

#include "Logger.h"

#include <string>
#include <vector>
#include <fstream>

//forward declarations
class Territory;

//TODO:  logger - global variables are usually bad



struct Continent {//TODO:Make sure continents destruct
	//TODO should be lowercase c?
	//TODO review public/private as needed
public:
	std::vector<Territory*> territories; //TODO refactor to territories
	std::string name;
	int bonus,owner;
	bool operator==(const Continent rhs); 
	friend std::ostream& operator<<(std::ostream&, Continent const&);
};

class Territory {	//TODO: Make sure Territories destruct
	friend class Map;
private:
	// coordinates of the center of the territory in pixels from the top left corner of the bitmap
	//float coord[2]; //Not used- theres no GUI
	std::string name, continentName;
	const Continent* continent;
	int armies, owner;
	std::vector<Territory*> adjacencies;
	bool visited; //TODO for DFS look into more efficient ways later, for now is working

public:	
	
	//constructors
	//Territory () not possible because to reference continent it must be initialised.
	Territory(std::string, const Continent*, const std::vector<Territory*>&);
	Territory(std::string, const Continent*);
	Territory(std::string, std::string, int, int);
	Territory(const Territory&);
	~Territory();//destructor

	//operators
	bool operator==(const Territory& rhs);
	friend std::ostream& operator<<(std::ostream&, Territory const&);
	Territory& operator=(const Territory& e);

	//getters &setters
	//TODO clean up,
	
	std::string getName();
	std::vector<Territory*> getAdjacencies();
	/*
	void setName(std::string);
	int getOwner();
	void setOwner(int);
	int getArmies();
	void setArmies(int);
	Continent& getContinent();
	void setContinent(Continent&);*/

	//methods
	bool addAdjTerritory(Territory*);

};

/*
Information from [Map] section
We wont need this information in the project
struct Settings {
	// Map setting
	public:
		std::string image; //name of image ie world.bmp
		bool wrap =true;			// = yes
		std::string scroll; //= horizontal
		std::string author; //= Your name
		bool warn =true;			// = yes
};
*/


class Map {	
private:
	//members
	std::string name;
	//unsigned int numTerritories; //max is 255 TODO, not necessary territories.sizw
	//Settings settings; //Not needed for this project
	std::vector<Territory*> territories;
	std::vector <Continent*> continents;
	bool valid;
	//methods

public:	
	
	
	//constructors
	Map();
	Map(const Map&);
	~Map();

	//operators
	friend std::ostream& operator<<(std::ostream&, Map const&);
	Map& operator=(const Map& m);
	
	//getters & setters
	void setName(std::string);
	std::string getName();
	Continent* getContinent(const std::string&);
	bool isValid();
	
	//int getNumTerritories();
	//void setNumTerritories(int);

	//methods
	
	void resetVisited();
	bool continent_exists(std::string);
	void addTerritory(Territory* territory);
	void addContinent(Continent* continent);
	void DFS(Territory* t);
	void DFS_Continent(Territory* t, Continent* c);
	bool validate();	
	void test();
	void printContinentList();
	void printVisited();
};

//}
class MapLoader {
	//
private:
	std::ifstream inputFile;
	Map map;

	bool loadMapSettings();
	bool loadContinents(); 
	bool loadTerritories();
	
	//TODO 
	// WZMapLoader::headers checkHeader(std::string);
	//std::string formatHeader(std::string);
	void toLowercase(std::string&);
	std::string trimWhitespace(const std::string&);
	std::string formatInput(const std::string&);
	bool findSection(const std::string&);
	bool openFile(const std::string&);
	std::vector<std::string> split(const std::string&, char);
	bool has_duplicates(std::vector<std::string>&);
	bool initialise_territories(std::vector<std::string>&, std::vector<Continent*>&, std::vector<std::vector<std::string>>);

	
public:
	
	//	//constuctors
	MapLoader();
	//TODO: Copy constructor
	//TODO: Constructor MapLoader::MapLoader(std::string);
	~MapLoader();//TODO: Call destructors for continent and territory and close files if applicable
	//	
	//	//getters & setters
	//
	//	//methods
	bool loadMap(const std::string&);
	void test();
	//operators
	friend std::ostream& operator << (std::ostream&, MapLoader&);
	MapLoader& operator=(const MapLoader&);

};

#endif 


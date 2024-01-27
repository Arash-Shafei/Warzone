#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


namespace WZMap { //constants for Warzone map
	const int max_continents = 32;
	const unsigned int max_territories = 255;// NOTE: this is maximum value of uint type
	const int max_adjacencies = 10;
	const int not_owned = -1; //TODO: Is this needed
	
	//convert pesky bools to string
	static inline const std::string bool_toString(bool b) {return b ? "true" : "false";}
	//check that it is only positive numbers, no ., no -....
	static inline bool is_pos_number(const std:: string& s) { return s.find_first_not_of("0123456789") == std::string::npos;}
}

namespace WZMapLoader {
	//MapLoader Constants
	const std::string in_sqrbrackets = R"((?:\[)(.+?)(?=\]))";
	/* regex for matching text inside square brackets
	* expected behaviour: match one or more characters between brackets
	* [this]:
	* first match is "[this"
	* second match is "this"
	* does not match: []
	* newlines will not be accepted inside the brackets
	sources:
	https://regexr.com/
	https://regex101.com/
	https://stackoverflow.com/questions/2403122/regular-expression-to-extract-text-between-square-brackets

	* Positive lookbehind not supported, but this is the better match:
	* const std::string in_sqrbrackets = "(?<=\[).+?(?=\])";
	* Only takes the contents inside the brackets
	*/
	//(?:([^,\n]*)(?:[^,]|$))
	//TODO
	const std::string between_commas = R"((?:([^,\n]*)(?:[^,]|$)))";
	/*Regex for matching string between commas
	* will match blank spaces
	* https://regex101.com/
	* https://stackoverflow.com/questions/19512586/regex-to-match-text-between-commas
	*/
	const char open_sqrbracket = '[';
	const char equal_sign = '=';
	

	//to check whether the string is even worth looking at
	const int header_max = 25;

	const std::vector<std::string> header_string = { "map","continents","territories" };
	const enum header_sections {MAP,CONTINENTS,TERRITORIES};
	
	/*can only use enum or int in switch statements..
	const std::map< std::string,header_sections > headers_map{ {"map",MAP},
															{"continents",CONTINENTS},
															{"territories",TERRITORIES} };*/
	
	//for pathing
	const std::string map_folder_path = "maps\\";
}


#endif

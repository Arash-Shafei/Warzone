#ifndef LOGGER_H // include guard
#define LOGGER_H

#include <vector>
#include <string>

#define WRITE_LOG(msg) Logger::addEntry(__FUNCTION__, msg);// TODO this might not run? but __func__ only gives the function name not the class name

//struct Log{
//	unsigned int ID;
//	std::string name;
//	std::vector<std::string> messages;
//};

class Logger {
	/*
	This is a simple logger class.
	For now, it prints to command line, but it can be made to print to a file later on.
	Easily could add modes like print to command line or print to file etc
	could do different logs and store in a struct by program id

	TO USE:

	use macro by calling : WRITE_LOG(string message)
	TODO: can add line number with __LINE__?
	*/
private:

public:
	//std::vector<Log> logs;

	std::vector<std::string> log;
	Logger();
	~Logger();//TODO Destructor
	//bool newLog{};
	static void addEntry(const char* functionName, std::string message);
};


#endif
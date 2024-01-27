#include "Logger.h"

#include <chrono>
#include <iomanip> // put_time
#include <iostream>
#include <sstream>

using time_ = std::chrono::system_clock;

Logger::Logger(){
}

Logger::~Logger(){
}

void Logger::addEntry(const char* functionName, std::string message){
	auto entryTime = time_::to_time_t(time_::now());
	std::stringstream timeString;
	timeString << std::put_time(std::localtime(&entryTime), "%T") << " - ";
	//std::cout << timeString.str() << functionName << ":\n" << message << std::endl;
	std::cout << timeString.str() << functionName << " - " << message << std::endl;

	return;
}

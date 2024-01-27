#include "MapDriver.h"
#include "Map.h"
#include "Constants.h"
#include "Logger.h"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <exception>

using WZMapLoader::map_folder_path;
namespace fs = std::filesystem;

void testLoadMaps() {
	try {
		for (auto& entry : fs::directory_iterator(map_folder_path)) {
			//iterate through the maps/ folder for map files
			std::cout << "Map file found: " + entry.path().string() << std::endl;
			MapLoader ml;

			bool loadSuccess = ml.loadMap(entry.path().string());
			if (!loadSuccess) {
				WRITE_LOG("Map :" + entry.path().string() +" was not loaded successfully");
				//TODO: what to do
			}
			else
				WRITE_LOG("Map :" + entry.path().string() + " loaded successfully ");
		}
	}
	catch (std::exception e) {//TODO better error handling
		std::cout << e.what() << std::endl;
	}
}

#include "WZExceptions.h"
#include <string>


InvalidMapFile::InvalidMapFile(const char* m) : msg(m) {}

//MapFileNotLoaded
const char* InvalidMapFile::getMessage() {
     return msg;
}
const char* InvalidMapFile::what() const throw() {
    return description;
}
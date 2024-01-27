#ifndef WZ_EXCEPTIONS_H
#define WZ_EXCEPTIONS_H

#include <exception>

class InvalidMapFile : public std::exception {
    //very basic, look  at 
    // https://cplusplus.com/reference/exception/exception/
    // https://learn.microsoft.com/en-us/cpp/standard-library/exception-class?view=msvc-170
    //https://stackoverflow.com/questions/67873720/c-custom-exception-classes
    //to make more meaningful subclasses
    private:
        const char* msg;
        const char* description = "Invalid .map file";
    public:
        InvalidMapFile(const char* m);
        const char* getMessage();
        const char* what() const throw();
};

#endif // !WZ_EXCEPTIONS_H

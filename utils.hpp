#include <string>


std::string trim(std::string value){
    if(value.empty()) return value;
    value.erase(0, value.find_first_not_of(" \n\r"));
    value.erase(value.find_last_not_of(" \n\r") + 1);
    return value;
}
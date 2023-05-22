#include "Ini.h"
#include "utils.hpp"

#include <fstream>
#include <string>

Value::Value(){}

Value::Value(bool value){
    m_value = value ? "true" : "false";
}

Value::Value(std::string& value){
    m_value = value;
}

Value::Value(int val){
    m_value = std::to_string(val);
}

Value::Value(const char* value){
    m_value = value;
}

Value::Value(double value){
    m_value = std::to_string(value);
}

std::ostream& operator << (std::ostream& os, Value& v){
    os << v.m_value;
    return os;
}

Value& Value::operator = (const bool& value){
    m_value = value ? "true" : "false";
    return *this;
}

Value& Value::operator = (const std::string& value){
    m_value = value;
    return *this;
}

Value& Value::operator = (const int& value){
    m_value = std::to_string(value);
    return *this;
}

Value& Value::operator = (const double& value){
    m_value = std::to_string(value);
    return *this;
}

Value::operator bool(){
    return m_value == "true" ? true : false;
}

Value::operator std::string(){
    return m_value;
}

Value::operator int(){
    return stoi(m_value);
}

Value::operator double(){
    return std::stod(m_value);
}

IniLoader::IniLoader(){}

IniLoader::IniLoader(std::string && name) : m_filename(name) {}

bool IniLoader::load(std::string&& filename){
    std::ifstream ifs(filename.c_str());
    if(!ifs.is_open() || ifs.fail()) return false;

    std::string line;
    std::string sec_name = "";

    while(std::getline(ifs, line)){
        if(line == "") continue;

        line = trim(line);

        if(line[0] == '['){
            int idx = line.find(']');
            sec_name = line.substr(1, idx - 1);
            m_sections[sec_name] = {};
        }else{
            int idx = line.find('=');
            auto key = trim(line.substr(0, idx));
            auto value = trim(line.substr(idx + 1));
            std::cout << key << "=" << value << std::endl;
            m_sections[sec_name][key] = value;
        }

    }
    ifs.close();
    return true;
}

Value& IniLoader::get(const std::string& section, const std::string& key) try {
    return m_sections.at(section).at(key);
}catch (const std::exception& e) {
    std::cout << "**************" << std::endl;
    std::cout << "IniLoader get error, check the section and key is exist!" << std::endl;
    std::cout << "**************" << std::endl;
}



Section& IniLoader::operator [] (const std::string& section) try {
    return m_sections.at(section);
}catch (const std::exception& e) {
    std::cout << "**************" << std::endl;
    std::cout << "IniLoader [] error, check the section and key is exist!" << std::endl;
    std::cout << "**************" << std::endl;
    std::terminate(); // 中断程序运行
    static Section static_section;
    return static_section;
}
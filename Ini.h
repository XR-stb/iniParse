#pragma once

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>


class Value {
private:
    std::string m_value;

public:
    Value();
    Value(bool);
    Value(std::string&);
    Value(int);
    Value(const char*);
    Value(double);

public:
    friend std::ostream& operator << (std::ostream& os, Value& v);
    Value& operator = (const bool&);
    Value& operator = (const std::string&);
    Value& operator = (const int&);
    Value& operator = (const double&);

public:
    operator bool();
    operator std::string();
    operator int();
    operator double();
};

using Section = std::unordered_map<std::string, Value>;

class IniLoader {
private:
    std::string m_filename;
    std::unordered_map<std::string, Section> m_sections;

public:
    IniLoader();
    IniLoader(std::string&& filename);

public:
    bool load(std::string&& filename);
    Value& get(const std::string& section, const std::string& key);
    template<typename T>
    bool set(const std::string& section, const std::string& key, T value);

public:
    Section& operator [] (const std::string& section);
};


template<typename T>
bool IniLoader::set(const std::string& section, const std::string& key, T value){
    m_sections[section][key] = value;
}
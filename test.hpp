#pragma once

#include "Ini.h"


void test(){
    Value val = "123";
    Value val2 = 123;
    Value val3 = 1.23;
    std::string ss = "456";

    Value val4 = ss;

    std::cout << val << std::endl;
    val = 123;
    
    int a = val;
    val = 1.23;
    double b = val;
    val = "test";
    std::string s = val;

    IniLoader loader;
    loader.load("./config.ini");
    std::cout << loader.get("redis", "ip") << std::endl;
    //std::cout << loader.get("redis", "pwd") << std::endl;//error key not exist
    loader["redis"]["port"] = 1231;
    std::cout << loader["redis"]["port"] << std::endl;

    loader.set("redis", "user", "root");
}
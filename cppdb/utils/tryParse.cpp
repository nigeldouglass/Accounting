#include "tryParse.h"

dataType TryParse::Int32(std::string parse){
    dataType ret;
    try {
        int no;
        no=stoi(parse);
        ret.passed = true;
    }catch(std::exception e){
        TryParse::log(parse, "int");
    }
    return ret;
}

dataType TryParse::ToInt32(std::string parse){
    dataType ret;
    if(TryParse::Int32(parse).passed){
        std::cout << "BSC------------------------" << std::endl;
        ret.passed = true;
        ret.integer = stoi(parse);
    }
    return ret;
}
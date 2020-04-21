#ifndef TRYPARSE_H
#define TRYPARSE_H

#include <iostream>
#include <string>
#include <exception>
#include "../database/structures/column.h"

struct dataType{
    bool passed = false;
    int integer;
    bool boolean;
    double doub;
    std::string varchar;
    column col;
};

class TryParse{

    public:
        static dataType Int32(std::string parse);

        static dataType ToInt32(std::string parse);

    private:
    static void log(std::string parse, std::string type){
        std::cout<<"Cannot convert "+parse+" to an "+type<<std::endl;
    }
};

#endif
#ifndef COLUMN_H
#define COLUMN_H

#include <string>

enum type { integer, doub, varchar, datetime, NUL};

class column{

    public:
        bool canIncrement = false;
        bool primary = false;
        std::string name;
        type columnType;
        type convert(std::string token){
            if(token == "integer") return integer;
            else if(token == "doub") return doub;
            else if(token == "varchar") return varchar;
            else if(token == "datetime") return datetime;
            else return NUL;
        };
    private:
};

#endif
#ifndef ROW_H
#define ROW_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "column.h"
#include "../../utils/tryParse.h"
#include "../../utils/Serialization/Object.h"

class row{

    public:
        row(std::vector<std::string> columns);
        bool addData(std::string column, std::string data, type t);
        void removeColumn(std::string column);
        std::string getDataAsString(std::string column) const;
        dataType getDataAsType(std::string column, type t);
        dataType getValueAsType(std::string value, type t);
        std::vector<std::string> getColumns();
        Object* save();
    private:
        std::map<std::string, std::string> data;
        bool addData(std::string column, std::string data);
};

struct RowCompare
{
    std::string col;
    int direction = -1;
    RowCompare(std::string col, int direction){
        this->col = col;
        this->direction = direction;
        std::cout << col << " : " << std::to_string(direction) << std::endl;
    }

	bool operator ()(const row & r1, const row & r2){
		if(r1.getDataAsString(col) == r2.getDataAsString(col))
			return false;

        if(direction == -1){
		    return r1.getDataAsString(col) > r2.getDataAsString(col);
        }else{
            std::cout<<"ASC"<<std::endl;
            return r1.getDataAsString(col) < r2.getDataAsString(col);
        }
	}
};

#endif
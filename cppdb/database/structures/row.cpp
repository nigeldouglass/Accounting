#include "row.h"

row::row(std::vector<std::string> columns){
    for (const auto& column : columns){
        this->data.insert(std::make_pair(column, ""));
    }
}

bool row::addData(std::string column, std::string data, type t){
    std::cout<<"Data is "+data<<std::endl;
    auto it = this->data.find(column);
    if ( it != this->data.end() ) {
        bool canAdd = false;
        switch(t){
            case integer:
                if(TryParse::Int32(data).passed)
                    canAdd = true;
                break;
            case varchar:
                canAdd = true;
                break;
            case doub:
                break;
            case datetime:
                break;
            case NUL:
                break;
        };
        if(canAdd)
            return this->addData(column, data);
    }else{
        std::cout << "Error: Cannot find column "+column<<std::endl;
        return false;
    }
    return false;
}

bool row::addData(std::string column, std::string data){
    std::map<std::string, std::string>::iterator it = this->data.find(column); 
    if (it != this->data.end())
        it->second = data;

    return true;
}

std::string row::getDataAsString(std::string column) const{
    if(this->data.count(column)){
        return this->data.find(column)->second;
    }
    return "";
}

dataType row::getDataAsType(std::string column, type t){
    dataType ret;
    if (this->data.count(column)) {
        std::string value = this->data.find(column)->second;
        return this->getValueAsType(value, t);
    }
    
    ret.passed = false;
    return ret;
}


dataType row::getValueAsType(std::string value, type t){
    dataType ret;
    switch(t){
        case integer:
            return TryParse::ToInt32(value);
            break;
        case varchar:
            ret.passed = true;
            ret.varchar = value;
            break;
         case doub:
            ret.passed = true;
            ret.varchar = value;
            break;
        case datetime:
            ret.passed = true;
            ret.varchar = value;
            break;
        case NUL:
            ret.passed = false;
            break;
    };
    return ret;
}

std::vector<std::string> row::getColumns(){
    std::vector<std::string> ret;
    for(std::map<std::string, std::string>::iterator it = this->data.begin(); it != this->data.end(); ++it) {
    ret.push_back(it->first);
    }
    return ret;
}
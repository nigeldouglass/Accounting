#include "table.h"
#include <fstream>

table::table(std::string name){
    this->name = name;
}

std::string table::getName(){
    return this->name;
}

bool table::setPrimary(std::string column){
    std::vector<std::string> temp;
    for ( std::map<int, row>::iterator it = this->rows.begin(); it != this->rows.end(); it++ ){
        std::string newPrime = this->rows.find(it->first)->second.getDataAsString(column);
        if (std::find(temp.begin(), temp.end(), newPrime) != temp.end()){
            return false;
        }else{
            temp.push_back(newPrime);
        }
    }
    this->primaryColumn = column;
    if(temp.size()!=0)
        this->primaryValues = temp;
    return true;
}

template <typename T>
bool table::containsPrimary(T t){
    if(std::find(this->primaryValues.begin(), this->primaryValues.end(), t) != this->primaryValues.end()){
        return true;
    }
    return false;
}

bool table::containsColumn(std::string column){
    if(columns.find(column) != this->columns.end()){
        return true;
    }
    return false;
}

std::vector<std::string> table::getColumnNames(){
    return this->columnOrder;
}

dataType table::getColumn(std::string column){
    dataType ret;
    if(this->containsColumn(column)){
        ret.passed = true;
        ret.col = columns[column];
    }
    else {
        ret.passed = false;
    }
    return ret;
}

std::map<std::string, column> table::getColumns(){
    return this->columns;
}

type table::getColumnType(std::string column){
    dataType val = this->getColumn(column);
    if(val.passed)
        return val.col.columnType;
    return NUL;
}

void table::addColumn(std::string name, column column){
    if(!this->containsColumn(name)){
        this->columns.insert(std::make_pair(name, column));
        this->columnOrder.push_back(name);
    }
}

void table::removeColumn(std::string column){
    if(this->containsColumn(column)){
        this->columns.erase(column);
        for(auto &r : this->rows){
           // r.second.removeColumn(column);
        }
    }
}

void table::addRow(row row){
    this->addRow(this->nextRowID,row);
}

void table::addRow(int id, row newRow){
    if(!this->primaryColumn.empty()){
        if(this->containsPrimary(newRow.getDataAsString(this->primaryColumn))){
            return;
        }
        if(newRow.getDataAsString(this->primaryColumn)==""&&this->columns.find(this->primaryColumn)->second.columnType==integer){
            int primary = 1;
            if(id!=0){
                if (this->rows.count(id-1)) {
                    dataType prior = this->rows.find(id-1)->second.getDataAsType(this->primaryColumn, integer);
                    if (prior.passed) {
                        primary = prior.integer + 1;
                    }
                    else {
                        std::cout << "Primary: FAILED" << std::endl;
                    }
                }
            }
                
            newRow.addData(this->primaryColumn, std::to_string(primary), integer);
        }
    }
    this->rows.insert(std::make_pair(id, newRow));
    if(this->nextRowID==id){
        this->nextRowID++;
    }
}

std::map<int, row> table::getData(){
    return this->rows;
}

std::list<row> table::getDataVec(){
    std::list<row> ret;
    for(std::map<int, row>::iterator it = this->rows.begin(); it != this->rows.end(); ++it) {
        ret.push_back(it->second);
    }
    return ret;
}

void table::save(std::string path){
    std::vector<std::byte> stream;
    std::unique_ptr<Database> db(new Database(this->name));
    for( auto& [key, val] : this->getColumns()){
        db->push_object(val.save());
    }
    for( auto& [key, val] : this->rows){
        db->push_object(val.save());
    } 
    
    db->getBytes(&stream, 0);
    std::cout<<std::to_string(stream.size())<<std::endl;
    File::save(path+"/"+this->name+".txt", stream);
    //serialization::Serialization::printBytes(&stream);
    
    unsigned char cbuffer[stream.size()];
    for(int i =0; i<stream.size();i++){
        cbuffer[i] = (char)stream[i];
    }
    std::cout<<"["+std::to_string(stream.size())+"]"<<std::endl;
    int len = sizeof(cbuffer)/sizeof(cbuffer[0]);
    std::string test(reinterpret_cast<const char*>(cbuffer), sizeof(cbuffer)/sizeof(cbuffer[0]));
//     std::cout<<test<<std::endl;
//     std::cout<<"Test ["+std::to_string(test.size())+"] "+test<<std::endl;
    
//    std::cout<<"Encrypt: "<<encrypt(test)<<std::endl;
//    std::cout<<"Size: "<<std::to_string(encrypt(test).size())<<std::endl;
//    std::cout<<"Decrypt: "<<decrypt(encrypt(test))<<std::endl;
//    std::cout<<"Size: "<<std::to_string(decrypt(encrypt(test)).size())<<std::endl;
//    std::cout<<"END-+"<<std::endl;

    std::ofstream myfile;
  myfile.open (path+"/"+this->name+"-enc.txt");
  myfile << encrypt(test);
  myfile.close();

  myfile.open (path+"/"+this->name+"-dec.txt");
  myfile << decrypt(encrypt(test));
  myfile.close();
  

     stream.clear();
}
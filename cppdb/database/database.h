#include "./structures/table.h"
#include "../utils/tryParse.h"

#include <filesystem>
#include <fstream> 
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

struct executeReturn{
    bool passed = false;
    std::string err;
    std::list<row> rows;
};

class database{
    public:
        std::map<std::string, table> getTables(){
            return tables;
        };
        database(){};
        database(std::string databasePath): database(databasePath, "db"){};
        database(std::string databasePath, std::string format);
        void create();
        void create(std::string password);
        void create(std::string password, std::string username);
        executeReturn execute(std::string sql);
        bool connect(std::string username, std::string password);
    private:
        std::map<std::string, table> tables;
        std::string format = ".";
        std::string databasePath = "";
        bool bootingUp = false;
        bool connected = false;
        enum OPERATORS {
            SELECT,
            DELETE,
            INSERT,
            UPDATE,
            ALTER,
            CREATE,
            NUL
        };
        OPERATORS convert(std::string token){
            std::cout << "Token: "+token <<std::endl;
            if(token == "SELECT") return SELECT;
            else if(token == "DELETE") return DELETE;
            else if(token == "INSERT") return INSERT;
            else if(token == "UPDATE") return UPDATE;
            else if(token == "ALTER") return ALTER;
            else if(token == "CREATE") return CREATE;
            return NUL;
        };
        executeReturn createSQL(std::string sql);
        executeReturn createTable(std::string name, std::string variables);
        executeReturn insertSQL(std::string sql);
        executeReturn addData(std::string table, std::vector<std::string> what, std::vector<std::string> where);
        executeReturn selectSQL(std::string sql);
        executeReturn selectData(std::string table, std::vector<std::string> what, std::string where);
        executeReturn orderData(std::list<row> data, std::string what, int direction);
        bool deleteSQL(std::string sql);
        bool updateSQL(std::string sql);
        bool alterSQL(std::string sql);
        bool tableExists(std::string table);
};
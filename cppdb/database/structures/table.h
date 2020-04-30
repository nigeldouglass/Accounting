#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>

#include "column.h"
#include "row.h"

#include "../../utils/Serialization/Database.h"
#include "../../utils/Serialization/Array.h"
#include "../../utils/Serialization/Object.h"
#include "../../utils/Serialization/Field.h"
#include "../../utils/Serialization/File.h"

#include "../encrypt.h"

class table{

    public:
        table(std::string name);
        std::string getName();
        bool setPrimary(std::string column);
        std::string getPrimary();
        
        template <typename T>
        bool containsPrimary(T t);

        bool containsColumn(std::string column);
        std::vector<std::string> getColumnNames();
        dataType getColumn(std::string column);
        std::map<std::string, column> getColumns();
        type getColumnType(std::string column);
        void addColumn(std::string name, column column);
        void removeColumn(std::string column);

        void addRow(row row); 
        void addRow(int id, row row);        
        std::map<int, row> getData();
        std::list<row> getDataVec();
        void getRow(int id);

        void save(std::string location);

    private:
        std::string name;
        int nextRowID = 0;
        std::string primaryColumn;
        std::map<std::string, column> columns;
        std::vector<std::string> columnOrder;
        std::map<int, row> rows;
        std::vector<std::string> primaryValues;
};

#endif
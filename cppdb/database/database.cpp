#include "database.h"

bool fileExists(std::string file){
    return std::filesystem::exists(file);
}

int findLastIndex(std::string& str, char x) 
{ 
    int index = -1; 
    for (size_t i = 0; i < str.length(); i++) 
        if (str[i] == x) 
            index = i; 
    return index; 
} 

int findLastIndex(std::string& str, std::string find) 
{ 
    int n = find.length(); 
    char * char_array = new char[n+1];
    //std::strcpy_s(char_array, (n+1), find.c_str()); WINDOWS
    strcpy(char_array, find.c_str()); 

    int foundIndex = -1;
    int index = -1;
    int curChar = 0; 
    for (size_t i = 0; i < str.length(); i++) {
        if(index!=-1){
            for(int j = 1;j<n+1;j++){

                if(i+j>str.length())
                    return -1;

                if(str[i+j-1] == char_array[curChar]){
                    curChar++;
                    if(curChar == n){
                        foundIndex = index;
                        index = -1;
                        curChar = 0;
                        break;
                    }
                }else{
                    index = -1;
                    curChar = 0;
                    break;
                }
            }
        }
        if (str[i] == char_array[0] && index==-1) {
            index = i; 
            curChar++;
        }
    }
    delete[] char_array;
    return foundIndex; 
} 

std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter){
	std::vector<std::string> splittedString;
	size_t startIndex = 0;
	size_t endIndex = 0;
	while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() ){
		std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();
	}
	
    if(startIndex < stringToBeSplitted.size()){
		std::string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}

    return splittedString;
}

std::string remove(std::string & str, const std::string & toErase){
	size_t pos = std::string::npos;

	while ((pos  = str.find(toErase) )!= std::string::npos){
		str.erase(pos, toErase.length());
	}

    return str;
}

std::string replace(std::string & str, const std::string & toErase, const std::string & toReplace){
    std::string::size_type n = 0;
    while ( ( n = str.find( toErase, n ) ) != std::string::npos ){
        str.replace( n, toErase.size(), toReplace );
        n += toReplace.size();
    }
    return str;
}

database::database(std::string databasePath, std::string format){
    this->format += format;
    this->databasePath = databasePath;
    if(!std::filesystem::is_directory(this->databasePath)){
        std::filesystem::create_directories(this->databasePath);
    }
    if(!fileExists(this->databasePath+"DB.info")){
        std::ofstream outfile (this->databasePath+"DB.info");
        outfile << "[Version=1.0]" << std::endl;
        outfile.close();
    }
    
}

void database::create(){
    database::create("","root");
}

void database::create(std::string password){
    database::create(password,"root");
}

void database::create(std::string password, std::string username){
    if(!username.compare("")){
        username = "root";
    }
    if(!fileExists(this->databasePath+"SETUP"+this->format)){
        this->execute("CREATE TABLE SETUP (rootUsername varchar PRIMARY, rootPassword varchar)");
        this->execute("INSERT INTO SETUP (rootUsername, rootPassword) VALUES ('"+ username +"','"+ password+"')");
        this->execute("CREATE TABLE USERS (id integer PRIMARY AUTOINCREMENT, username varchar, password varchar)");
        this->execute("INSERT INTO USERS (username, password) VALUES ('"+ username +"','"+ password+"')");
    }
}

bool database::connect(std::string username, std::string password){
    this->bootingUp = true;

    return false;
}

executeReturn database::execute(std::string sql){
   /* if(sql.compare("") || sql.length == 0 || (!connected && !bootingUp)){
        return;   
    }
    */
    executeReturn ret;
    auto token = split(sql, " ")[0];
    switch (convert(token)){
        case CREATE:
            return this->createSQL(sql);
            break;
        case INSERT:
            return this->insertSQL(sql);
            break;
        case SELECT:
            return this->selectSQL(sql);
            break;
        case DELETE:
            break;
        case UPDATE:
            break;
        case ALTER:
            break;
        case NUL:
            ret.err = "Unable to find sql function for ["+sql+"]";
            break;
    }
    return ret;
}

executeReturn database::createSQL(std::string sql){
    std::vector<std::string> token = split(sql, " ");
    if(token.size()>=3){
        if(token[1] == "TABLE"){
            std::string table = token[2];
            int start = 15+table.size();
            int end = sql.size()-16-table.size();
            std::string variables = "";
            if(start < start+end){
                variables = sql.substr(15+table.size(), sql.size()-16-table.size());
            }
            return this->createTable(table, variables);
        }
    }
    return {false, "Create sql failed because there is not enough tokens. Try: CREATE TABLE [NAME]"};
}

executeReturn database::createTable(std::string name, std::string variables){
    std::for_each(name.begin(), name.end(), [](char & c) {
		c = ::toupper(c);
	});
    std::string tableFile = this->databasePath + name + this->format;
    if(fileExists(tableFile)){
        return {false, "Table "+name+" already exists!"};
    }else{
        table newTable(name);
        bool failed = false;
        if(variables.size()!=0){
            variables = replace(variables, ", ", ",");
            std::vector<std::string> columns = split(variables, ",");
            for(size_t i = 0; i < columns.size(); i++){
                std::vector<std::string> data = split(columns[i], " ");
                column newColumn;
                newColumn.name = data[0];
                for(size_t j = 1; j < data.size(); j++){
                    if(data[j]=="PRIMARY"){
                        newColumn.primary = true;
                        if(!newTable.setPrimary(newColumn.name)){
                            return {false, "Cannot set primary key as "+newColumn.name+" due to conflicting primary values in table "+name};
                            break;
                        }
                    }else if(data[j] == "AUTOINCREMENT" && newColumn.primary){
                        newColumn.canIncrement = true;
                    }else{
                        newColumn.columnType = newColumn.convert(data[j]);
                    }
                }
               newTable.addColumn(newColumn.name, newColumn);
            }
        }
        if(!failed){
            this->tables.insert(std::make_pair(name, newTable));
            std::cout<<"SAVE"<<std::endl;
            newTable.save(this->databasePath);
        return {true};
        }
        return {false, "Create table was never set to true."};
    }
    return {false, "Create table because of unknown error."};
}

executeReturn database::insertSQL(std::string sql){
    std::vector<std::string> token = split(sql, " ");
    if(token.size()>=3){
        if(token[1] == "INTO"){
            std::string table = token[2];
            if(sql.find("VALUES") != std::string::npos){
                sql = replace(sql, "INSERT INTO "+table+" ", "");
                int end = sql.find("VALUES")-3;

                std::vector<std::string> columns;
                if(0<end){
                    std::string columnString = sql.substr(1, end);
                    sql = replace(sql, "("+columnString+") ","");
                    columnString.erase(remove_if(columnString.begin(), columnString.end(), isspace), columnString.end());
                    columns = split(columnString, ",");
                }
                
                sql = replace(sql, "VALUES ", "");
                sql = replace(sql, "', '", "','");
                std::vector<std::string> values = split(sql, "','");
                values[0] = values[0].substr(2);    //Remove first '
                values[values.size()-1] = values[values.size()-1].substr(0,values[values.size()-1].size()-2);   //Remove last '
                return this->addData(table, columns, values);
            }else{
                return {false, "values never set."};
            }
        }else{
            return {false, "2nd token is not INTO. Should be INSERT INTO ...."};
        }
    }
    return {false, "INSERT called but never executed."};
}

executeReturn database::addData(std::string table, std::vector<std::string> columns, std::vector<std::string> values){
    std::vector<std::string> tableColumns;
    auto it = this->tables.find(table);
    if ( it != this->tables.end() ) {
        tableColumns = it->second.getColumnNames();
    }else{
        return {false, "Cannot find table "+table};
    }

    if(columns.size()==0){
        columns = tableColumns;
    }

    if(columns.size()>=values.size()){
        bool failed = false;

        row newRow(tableColumns);
        int i = 0;
        for (const auto& column : columns){
            if(!this->tables.find(table)->second.containsColumn(column)){
                failed = true;
                return {false, "Table "+table+" does not have column "+column};
            }else{
                std::string value = "";
                if(values.size()>i){
                    value = values[i];
                }
                type t = tables.find(table)->second.getColumnType(column);        
                if(newRow.addData(column, value, t)){
                    failed = false;
                }else{
                    failed = true;
                    return {false, "Cannot add "+value+" into "+column+" as type has to be " +std::to_string(t)};
                    break;
                }
            }
            i++;
        }
        if(!failed){
            tables.find(table)->second.addRow(newRow);
            //SAVE
            tables.find(table)->second.save(this->databasePath);
            return {true};
        }
    }
    return {false, "Specified less columns than there is values"};
}

executeReturn database::selectSQL(std::string sql){
    std::vector<std::string> token = split(sql, " ");
    std::string table;
    std::vector<std::string> what;
    std::string where;
    int orderBy = findLastIndex(sql, "ORDER BY ");
    int lastQuotation = -1;
    executeReturn temp;
    if(token.size()>=4){
        if(token[1] == "*" && token[2] == "FROM"){
            what.push_back(token[1]);
            table = token[3];
            lastQuotation = orderBy-2;

            int end = replace(sql, "SELECT * FROM "+table+" ", "").find("WHERE");
            if(0==end){
                sql = replace(sql, "WHERE ", "");
                int lastQuotation = findLastIndex(sql, '\'')+1;
                where = sql.substr(0,lastQuotation);
            }else{
                where = "";
            }
        }else{
            int end = sql.find("FROM")-8;
            if(0<end){
                std::string whatString = sql.substr(7, end);
                table = split(replace(sql, "SELECT "+whatString+" FROM ", ""), " ")[0];
                whatString.erase(remove_if(whatString.begin(), whatString.end(), isspace), whatString.end());
                what = split(whatString, ",");
                if(!this->tableExists(table))
                    return temp;


                int end = replace(sql, table+" ", "").find("WHERE");
                if(0==end){
                    sql = replace(sql, "WHERE ", "");
                    int lastQuotation = findLastIndex(sql, '\'')+1;
                    where = sql.substr(0,lastQuotation);
                }
            }
        }
        temp = this->selectData(table, what, where);
        if(!temp.passed){
            return temp;
        }
        if(orderBy!=-1 && lastQuotation<orderBy){
            std::string orderByString = sql.substr(9+((where.size()!=0)?where.size()+1:0));
            std::vector<std::string> orderByTokens = split(orderByString, ", ");
            for(auto &order : orderByTokens){
                std::vector<std::string> ordering = split(order, " ");
                int direction = 1;
                if(ordering.size()==2) 
                    direction = ((ordering[1]=="ASC")?1:-1);
               // temp = this->orderData(temp.rows, ordering[0], direction);
                if(!temp.passed)
                    return temp;
            }
        }
        if(temp.passed)
            return temp;
    }
    return temp;
}

executeReturn database::selectData(std::string table, std::vector<std::string> what, std::string where){
    executeReturn ret;
    if(tableExists(table)){
        std::list<row> temp = this->tables.find(table)->second.getDataVec();
        if(what[0]!="*"){
            std::list<row> newTemp;
            std::vector<std::string> columnAvailable = tables.find(table)->second.getColumnNames();
            for(auto &r : temp){
                row tempRow(what);
                for(auto &c : what){
                    if (std::find(columnAvailable.begin(), columnAvailable.end(), c) != columnAvailable.end()){
                        type t = tables.find(table)->second.getColumnType(c);  
                        tempRow.addData(c, r.getDataAsString(c), t);
                    }else{
                        ret.err = "Unable to find column "+c+" in table "+table; 
                        return ret;
                    }
                }
                newTemp.push_back(tempRow);
            }
            temp = newTemp;
        }
        if(where!=""){
            std::list<row> newTemp;
            std::vector<std::string> token = split(where, "' AND ");
            for(auto &t : token){
                std::vector<std::string> whereToken = split(t, "='");
                int lastQuotation = findLastIndex(whereToken[1], '\'');
                if(lastQuotation!=-1 && lastQuotation==whereToken[1].size()-1){
                    whereToken[1] = whereToken[1].substr(0,lastQuotation);
                }
                for(auto &r: temp){
                    if(r.getDataAsString(whereToken[0])==whereToken[1]){
                        newTemp.push_back(r);
                    }
                }
                temp = newTemp;
            }
        }
        ret.rows = temp;
        ret.passed = true;
        return ret;
    }
    ret.err = "Unable to find table "+table;
    return ret;
}

executeReturn database::orderData(std::list<row> data, std::string what, int direction){
    bool found = false;
    std::vector<std::string> columnAvailable = data.front().getColumns();
    for (auto& vec : columnAvailable) {
        if (vec == what) {
            found = true;
            break;
        }
    }
    if (found){
        data.sort(RowCompare(what, direction));
        return { true,"", data };
    }
    return {false, "Unable to order data. Unable to find "+what};
}

bool database::tableExists(std::string table){
    if(this->tables.count(table))
        return true;
    return false;
}
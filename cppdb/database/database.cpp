#include "database.h"

bool fileExists(std::string file){
    return std::filesystem::exists(file);
}

int findLastIndex(std::string& str, char x) 
{ 
    int index = -1; 
    for (int i = 0; i < str.length(); i++) 
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
    for (int i = 0; i < str.length(); i++) {
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
	int startIndex = 0;
	int  endIndex = 0;
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
            std::cout<<this->databasePath+"\n";
            std::cout<<fileExists(this->databasePath+"DB.info")+"\n";
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
    std::cout<<"User: "+username<<std::endl;
    std::cout<<"Pass: "+password<<std::endl;
    if(!fileExists(this->databasePath+"SETUP"+this->format)){
       // this->createTable("SETUP", "rootUsername varchar, rootPassword varchar");
        this->execute("CREATE TABLE SETUP (rootUsername varchar PRIMARY, rootPassword varchar)");
        this->execute("INSERT INTO SETUP (rootUsername, rootPassword) VALUES ('"+ username +"','"+ password+"')");
        this->execute("CREATE TABLE USERS (id integer PRIMARY AUTOINCREMENT, username varchar, password varchar)");
        this->execute("INSERT INTO USERS (username, password) VALUES ('"+ username +"','"+ password+"')");
        
        //std::cout << std::format("Created db with username {} and password {}", username, password) << std:endl;
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
            std::cout<<"Create\n";
            ret.passed = this->createSQL(sql);
            return ret;
            break;
        case INSERT:
            ret.passed = this->insertSQL(sql);
            return ret;
            break;
        case SELECT:
            return {this->selectSQL(sql)};
            break;
        case DELETE:
            std::cout << "DELETE SQL"<<std::endl;
            break;
        case UPDATE:
            std::cout << "UPDATE SQL"<<std::endl;
            break;
        case ALTER:
            std::cout << "ALTER SQL"<<std::endl;
            break;
        case NUL:
            std::cout << "DON'T EXECUTE SQL"<<std::endl;
            break;
    }
    return ret;
}

bool database::createSQL(std::string sql){
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
    return false;
}

bool database::createTable(std::string name, std::string variables){
    std::cout<<"0"<<std::endl;
    std::for_each(name.begin(), name.end(), [](char & c) {
		c = ::toupper(c);
	});
    std::cout<<"1"<<std::endl;
    std::string tableFile = this->databasePath + name + this->format;
    std::cout<<"2"<<std::endl;
    if(fileExists(tableFile)){
        std::cout<<"Unable to create table with name "+name+" as it already exists"<<std::endl;
        //loadTable();
        return false;
    }else{
         std::cout<<"3"<<std::endl;
        table newTable(name);
                 std::cout<<"4"<<std::endl;
        bool failed = false;
        if(variables.size()!=0){
            variables = replace(variables, ", ", ",");
            std::vector<std::string> columns = split(variables, ",");
            for(int i = 0; i < columns.size(); i++){
                std::vector<std::string> data = split(columns[i], " ");
                column newColumn;
                newColumn.name = data[0];
                std::cout<<"COL NAME: "+newColumn.name<<std::endl;
                for(int j = 1; j < data.size(); j++){
                    if(data[j]=="PRIMARY"){
                        newColumn.primary = true;
                        if(!newTable.setPrimary(newColumn.name)){
                            std::cout<<"Error: Cannot set primary key as "+newColumn.name+" due to conflicting primary values in table "+name<<std::endl;
                            failed = true;
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
        return true;
        }
        return false;
    }
    return false;
}

bool database::insertSQL(std::string sql){
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
            }
        }
    }
    return false;
}

bool database::addData(std::string table, std::vector<std::string> columns, std::vector<std::string> values){
    std::cout<<table<<std::endl;
    std::vector<std::string> tableColumns;
    auto it = this->tables.find(table);
    if ( it != this->tables.end() ) {
        tableColumns = it->second.getColumnNames();
    }else{
        std::cout<<"Error: Cannot find table "+table;
        return false;
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
                std::cout<<"Error: Table "+table+" does not have column "+column;
                break;
            }else{
                std::string value = "";
                if(values.size()>i){
                    value = values[i];
                }
                std::cout<<value<<std::endl;
                type t = tables.find(table)->second.getColumnType(column);        
                if(newRow.addData(column, value, t)){
                    failed = false;
                }else{
                    failed = true;
                    break;
                }
            }
            i++;
        }
        if(!failed){
            tables.find(table)->second.addRow(newRow);
            //SAVE
            std::cout<<"Inserting data"<<std::endl;
            return true;
        }
    }
    return false;
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
        std::cout<<"SQL: "+sql<<std::endl;
        temp = this->selectData(table, what, where);
        if(!temp.passed){
            return temp;
        }
        std::cout<<"--DEBUG--\n"
                <<orderBy<<"\n"
                <<lastQuotation<<"\n";
                std::cout<<where+"\n";
        if(orderBy!=-1 && lastQuotation<orderBy){
            std::cout<<sql+"\n";
            std::string orderByString = sql.substr(9+((where.size()!=0)?where.size()+1:0));
            std::cout<<orderByString+"\n";
            std::vector<std::string> orderByTokens = split(orderByString, ", ");
            std::cout<<"--END--\n";
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
        std::cout<<"--E2--\n";
        if(temp.passed)
            return temp;
    }
    return temp;
}

executeReturn database::selectData(std::string table, std::vector<std::string> what, std::string where){
    std::cout<<table<<"\n"<<where<<std::endl;
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
        return { true, data };
    }
    executeReturn ret;
    return ret;
}

bool database::tableExists(std::string table){
    if(this->tables.count(table))
        return true;
    return false;
}
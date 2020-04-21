#include <string>
#include <iostream>
#include <napi.h>
#include "database/database.h"

database *db;

class dbJSON{
    public:
        std::string location;
        std::string name;  
        std::string type;
        std::string username;
        std::string password;
        std::string os;
};

Napi::String JSONStringify(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object json_object = info[0].As<Napi::Object>();
  Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
  Napi::Function stringify = json.Get("stringify").As<Napi::Function>();
  return stringify.Call(json, { json_object }).As<Napi::String>();
}

Napi::Object JSONParse(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String json_string = info[0].As<Napi::String>();
  Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
  Napi::Function parse = json.Get("parse").As<Napi::Function>();
  return parse.Call(json, { json_string }).As<Napi::Object>();
}

Napi::Object CreateDatabase(const Napi::CallbackInfo& info) {
    Napi::Object queryReturn = Napi::Object::New(info.Env());
    if (info.Length() < 1 || !info[0].As<Napi::String>()) {
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "Undefined parameters for CreateDatabase. Should be CreateDatabase({locaiton: [LOCATION], name: [NAME]})");
        return queryReturn;
    } 
    dbJSON dbOBJ;
    Napi::Object json = JSONParse(info);
    if(json.Has("location")){
        dbOBJ.location = json.Get("location").As<Napi::String>().Utf8Value();
        if(json.Has("name")){
            dbOBJ.name = json.Get("name").As<Napi::String>().Utf8Value();
        }else{
            queryReturn.Set("passed", false);
            queryReturn.Set("err", "DB Name was not set. Use name: '[NAME]'");
            return queryReturn;
        }
    }else{
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "DB Location was not set. Use location: '[LOCATION]'");
        return queryReturn;
    }
    if(json.Has("type")){
        dbOBJ.type = json.Get("type").As<Napi::String>().Utf8Value();
    }
    if(json.Has("username")){
        dbOBJ.username = json.Get("username").As<Napi::String>().Utf8Value();
    }
    if(json.Has("password")){
        dbOBJ.password = json.Get("password").As<Napi::String>().Utf8Value();
    }

    if(json.Has("os")){
        dbOBJ.os = json.Get("os").As<Napi::String>().Utf8Value();
    }


    if(!dbOBJ.location.empty()&&!dbOBJ.name.empty()){
        if(dbOBJ.os=="darwin"){
            dbOBJ.location += ((dbOBJ.location.back() == char('/')) ? "" : "/") + dbOBJ.name + "/";
        }else{
            dbOBJ.location.replace(dbOBJ.location.begin(), dbOBJ.location.end(), '/', '\\');
            dbOBJ.location += ((dbOBJ.location.back() == char('\\')) ? "" : "\\")+ dbOBJ.name + "\\";
        }
        if(!dbOBJ.type.empty()){
            db = new database(dbOBJ.location, dbOBJ.type);
        }else{
            db = new database(dbOBJ.location);
        }
    }else{
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "Unable to create database object.");
        return queryReturn;
    }
    if(db){
        if(!dbOBJ.username.empty()){
            db->create(dbOBJ.password, dbOBJ.username);
        }else{
            db->create(dbOBJ.password);
        }
    }else{
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "Unable to create database object.");
        return queryReturn;
    }
    queryReturn.Set("passed", true);
    return queryReturn;
}

Napi::Object Query(const Napi::CallbackInfo& info) {
    Napi::Object queryReturn = Napi::Object::New(info.Env());
    if (info.Length() < 1 || !info[0].As<Napi::String>()) {
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "Query is undefined. Should be for example Query('SELECT * FROM TABLE')");
        return queryReturn;
    } 
    if(db){
        executeReturn eR = db->execute(info[0].As<Napi::String>());
        std::cout<<"Size: "+std::to_string(eR.rows.size())<<std::endl;
        queryReturn.Set("passed", eR.passed);
        if(eR.passed&&eR.rows.size()!=0){
            Napi::Array data = Napi::Array::New(info.Env());
            int id = 0;
            for(auto &r : eR.rows){
                Napi::Object row = Napi::Object::New(info.Env());
                row.Set("id", id);
                int col = 0;
                for(const auto& column : r.getColumns()){
                    row.Set(column, r.getDataAsString(column));
                    col++;
                }
                data[id] = row;
                id++;
            }
            queryReturn.Set("data", data);
        }else{
            queryReturn.Set("err", eR.err);
        }
    }else{
        queryReturn.Set("passed", false);
        queryReturn.Set("err", "Database was never created. Use CreateDatabase function before any queries.");
    }
    return queryReturn;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports["jsonStringify"] =  Napi::Function::New(env, JSONStringify);
    exports["jsonParse"] = Napi::Function::New(env, JSONParse);  
    exports["CreateDatabase"] = Napi::Function::New(env, CreateDatabase);
    exports["Query"] = Napi::Function::New(env, Query);  

  return exports;
}

NODE_API_MODULE(CppDB, InitAll)
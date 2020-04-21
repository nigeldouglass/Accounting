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

Napi::Boolean CreateDatabase(const Napi::CallbackInfo& info) {
    dbJSON dbOBJ;
    Napi::Object json = JSONParse(info);
    if(json.Has("location")){
        std::cout<<"Has location"<<std::endl;
        dbOBJ.location = json.Get("location").As<Napi::String>().Utf8Value();
        if(json.Has("name")){
            std::cout<<"Has name"<<std::endl;
            dbOBJ.name = json.Get("name").As<Napi::String>().Utf8Value();
        }
    }
    if(json.Has("type")){
        std::cout<<"Has type"<<std::endl;
        dbOBJ.type = json.Get("type").As<Napi::String>().Utf8Value();
    }
    if(json.Has("username")){
        std::cout<<"Has username"<<std::endl;
        dbOBJ.username = json.Get("username").As<Napi::String>().Utf8Value();
    }
    if(json.Has("password")){
        std::cout<<"Has password"<<std::endl;
        dbOBJ.password = json.Get("password").As<Napi::String>().Utf8Value();
    }
    if(json.Has("os")){
        std::cout<<"Has os"<<std::endl;
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
        std::cout<<"Unable to create database obj"<<std::endl;
        return Napi::Boolean::New(info.Env(),false);
    }
    if(db){
        if(!dbOBJ.username.empty()){
            db->create(dbOBJ.password, dbOBJ.username);
        }else{
            db->create(dbOBJ.password);
        }
    }else{
        std::cout<<"Unable to create database"<<std::endl;
        return Napi::Boolean::New(info.Env(), false);
    }
    std::cout<<"Create database"<<std::endl;
    return Napi::Boolean::New(info.Env(),true);;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports["jsonStringify"] =  Napi::Function::New(env, JSONStringify);
    exports["jsonParse"] = Napi::Function::New(env, JSONParse);  
    exports["CreateDatabase"] = Napi::Function::New(env, CreateDatabase);  

  return exports;
}

NODE_API_MODULE(CppDB, InitAll)
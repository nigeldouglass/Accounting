#include "Field.h"

std::vector<std::byte> toByte(const std::string* str){
    std::vector<std::byte> ret;
    for(size_t i = 0; i < str->size(); i++){
        uint8_t x = str->at(i);
        ret.push_back((std::byte)x);
    }
    return ret;
}

std::vector<std::byte> toByte(const int integer){
    std::vector<std::byte> ret;
    ret.push_back((std::byte)integer);
    return ret;
}

int field::getSize(){
    return 1 + 2 + this->name.size() + 1 + this->data.size();
}

void field::setName(const std::string* name){
    assert(this->name.size() < SHRT_MAX);
    this->nameLength = (short)name->size();
    this->name = toByte(name);
}

int field::getBytes(std::vector<std::byte>* dest, int pointer){
    pointer = Serialization::writeBytes(dest, 0, this->storageType);
    pointer = Serialization::writeBytes(dest, 0, this->nameLength);
    pointer = Serialization::writeBytes(dest, 0, this->name);
    pointer = Serialization::writeBytes(dest, 0, this->dataType);
    pointer = Serialization::writeBytes(dest, 0, this->data);
    return pointer;
}

field* field::Byte(const std::string* name, std::byte* value){
    field* f = new field();
    f->setName(name);
    f->dataType = type::BYTE;
    f->data.reserve(type::getSize(type::BYTE));
    Serialization::writeBytes(&f->data, 0, *value);
    return f;
}

field* field::Short(const std::string* name, short value){
    field* f = new field();
    f->setName(name);
    f->dataType = type::SHORT;
    f->data.reserve(type::getSize(type::SHORT));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}

field* field::Char(const std::string* name, char value){
    field* f =new field();
    f->setName(name);
    f->dataType = type::CHAR;
    f->data.reserve(type::getSize(type::CHAR));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}

field* field::Int(const std::string* name, int value){
    field* f =new field();
    f->setName(name);
    f->dataType = type::INT;
    f->data.reserve(type::getSize(type::INT));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}
field* field::Double(const std::string* name, double value){
    field* f =new field();
    f->setName(name);
    f->dataType = type::DOUBLE;
    f->data.reserve(type::getSize(type::DOUBLE));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}
field* field::Boolean(const std::string* name, bool value){
    field* f =new field();
    f->setName(name);
    f->dataType = type::BOOLEAN;
    f->data.reserve(type::getSize(type::BOOLEAN));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}
field* field::Int64(const std::string* name, int64_t value){
    field* f =new field();
    f->setName(name);
    f->dataType = type::INT64;
    f->data.reserve(type::getSize(type::INT64));
    Serialization::writeBytes(&f->data, 0, value);
    return f;
}
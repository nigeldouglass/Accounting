#include "Serialization.h"

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, std::byte value){
    dest->at(pointer++) = value;
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, std::vector<std::byte> value){
    for(size_t i = 0; i < value.size();i++){
        pointer = Serialization::writeBytes(dest, pointer, value[i]);
    }
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, const char* value){
    for(size_t i = 0; i < std::strlen(value); i++){
        dest->at(pointer++) = (std::byte)value[i];
    }
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, short value){
    dest->at(pointer++) = (std::byte)((value>>8)&0xff);
    dest->at(pointer++) = (std::byte)((value>>0)&0xff);
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, int value){
    dest->at(pointer++) = (std::byte)((value>>24)&0xff);
    dest->at(pointer++) = (std::byte)((value>>16)&0xff);
    dest->at(pointer++) = (std::byte)((value>>8)&0xff);
    dest->at(pointer++) = (std::byte)((value>>0)&0xff);
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, int64_t value){
    dest->at(pointer++) = (std::byte)((value>>56)&0xff);
    dest->at(pointer++) = (std::byte)((value>>48)&0xff);
    dest->at(pointer++) = (std::byte)((value>>40)&0xff);
    dest->at(pointer++) = (std::byte)((value>>32)&0xff);
    dest->at(pointer++) = (std::byte)((value>>24)&0xff);
    dest->at(pointer++) = (std::byte)((value>>16)&0xff);
    dest->at(pointer++) = (std::byte)((value>>8)&0xff);
    dest->at(pointer++) = (std::byte)((value>>0)&0xff);
    return pointer;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, double value){
    //int64_t doub = value;
    //return Serialization::writeBytes(dest, pointer, doub);
    return 0;
}

int Serialization::writeBytes(std::vector<std::byte>*dest, int pointer, std::string value){
    pointer = Serialization::writeBytes(dest, pointer, (short)value.length());
    return Serialization::writeBytes(dest, pointer, value.c_str());
}

std::byte Serialization::readByte(std::vector<std::byte> src, int pointer){
    return src[pointer];
}

char Serialization::readChar(std::vector<std::byte> src, int pointer){
    return (char)(src[pointer+2]<<8|src[pointer+3]<<0);
}

short Serialization::readShort(std::vector<std::byte> src, int pointer){
    return (short)(src[pointer+2]<<8|src[pointer+3]<<0);
}

int Serialization::readInt(std::vector<std::byte> src, int pointer){
    return (int)(src[pointer]<<24|src[pointer+1]<<16|src[pointer+2]<<8|src[pointer+3]<<0);
}

int64_t Serialization::readInt64(std::vector<std::byte> src, int pointer){
    return (int)(src[pointer]<<56|src[pointer]<<48|src[pointer]<<40|src[pointer]<<32|src[pointer]<<24|src[pointer+1]<<16|src[pointer+2]<<8|src[pointer+3]<<0);
}


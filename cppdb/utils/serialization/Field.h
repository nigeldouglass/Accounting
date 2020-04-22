#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include "storageType.h"
#include "type.h"
#include "Serialization.h"

std::vector<std::byte> toByte(const std::string* str);
std::vector<std::byte> toByte(int integer);

class field{

    public:
        field(){};
        void setName(const std::string* name);
        int getBytes(std::vector<std::byte>* dest, int pointer);
        int getSize();
        static field* Byte(const std::string* name, std::byte* value);
        static field* Short(const std::string* name, short value);
        static field* Char(const std::string* name, char value);
        static field* Int(const std::string* name, int value);
        static field* Double(const std::string* name, double value);
        static field* Boolean(const std::string* name, bool value);
        static field* Int64(const std::string* name, int64_t value);
    private:
        std::byte storageType = storageType::FIELD;
        short nameLength;
        std::vector<std::byte> name;
        std::byte dataType;
        int64_t elementCount;
        std::vector<std::byte> data;
};

#endif
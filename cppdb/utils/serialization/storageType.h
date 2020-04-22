#ifndef STORAGE_TYPE_H
#define STORAGE_TYPE_H

#include <iostream>
#include <vector>
#include <string>

class storageType{

    public:
        static const std::byte UNKNOW     = (std::byte)0;
        static const std::byte FIELD      = (std::byte)1;
        static const std::byte ARRAY      = (std::byte)2;
        static const std::byte OBJECT     = (std::byte)3;
    private:
};

#endif
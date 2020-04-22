#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <vector>
#include <string>

class type{

    public:
        static const std::byte UNKNOWN    = (std::byte)0;
        static const std::byte BYTE       = (std::byte)1;
        static const std::byte SHORT      = (std::byte)2;
        static const std::byte CHAR       = (std::byte)3;
        static const std::byte INT        = (std::byte)4;
        static const std::byte INT64      = (std::byte)5;
        static const std::byte DOUBLE     = (std::byte)6;
        static const std::byte BOOLEAN    = (std::byte)7;

        static int getSize(std::byte type){
            switch (type)
            {
            case UNKNOWN:   assert(false);
            case BYTE:      return 1;
            case SHORT:     return 2;
            case CHAR:      return 2;
            case INT:       return 4;
            case INT64:     return 8;
            case DOUBLE:    return 8;
            case BOOLEAN:   return 1;
            
            default: assert(false);
            }
        }
    private:
};

#endif
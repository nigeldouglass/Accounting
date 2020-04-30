#include "column.h"

Object* column::save(){
    Object* o = new Object(this->name);
    field* type = field::Int("type", this->columnType);
    o->push_field(type);
    if(this->canIncrement){
        field* inc = field::Boolean("canIncremenet", this->canIncrement);
        o->push_field(inc);
    }
    if(this->primary){
    field* primary = field::Boolean("primary", this->primary);
    o->push_field(primary);
    }
    //field* columnType = field::String("canIncremenet", this->canIncrement);
    
    return o;
}
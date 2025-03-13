#ifndef FACTORY_H
#define FACTORY_H

#include "shapes.hpp"

class Factory {
    public:
        virtual Shape* createShape() = 0;
};



#endif
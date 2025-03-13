#ifndef ITERATOR_H
#define ITERATOR_H
#include "set.hpp"

template <typename T>
class Iterator {
    T* container_obj;

    public:
        Iterator(set<T> iterable);
        next();
        T value();
        
};

#endif
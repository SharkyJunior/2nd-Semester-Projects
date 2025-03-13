#ifndef ITERATOR_H
#define ITERATOR_H
#include "set.hpp"

template <typename T>
class Iterator {
    T* container_obj;

    public:
        Iterator(set<T> iterable);
        void next();
        T value();
        bool is_end();
        Iterator<T> operator++();
        T operator*();
        bool operator ==(Iterator<T> &b);
        bool operator !=(Iterator<T> &b);
};

#endif
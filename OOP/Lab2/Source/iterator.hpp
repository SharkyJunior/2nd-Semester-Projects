#ifndef ITERATOR_H
#define ITERATOR_H
#include "set.hpp"

template <typename T>
class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual void next() = 0;
        virtual T value() = 0;
        virtual bool is_end() = 0;
        virtual T operator*() = 0;
};

#endif
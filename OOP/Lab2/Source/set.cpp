#include "set.hpp"

#include <initializer_list>
#include <iostream>

using namespace std;

template <typename T>
set<T>::set(set<T>&& s) 
    : size(s.size), capacity(s.capacity)
{
    array = s.array;
    s.array = NULL;
}

template <typename T>
void set<T>::clear() {
    delete[] array;
    array = NULL;
    size = 0;
    capacity = 0;
}

template<typename T>
set<T>& set<T>::operator +=(const set<T>& s) {
    return this->sunion(s);
}

template<typename T>
set<T>& set<T>::operator *=(const set<T>& s) {
    return this->intersection(s);
}

template<typename T>
set<T>& set<T>::operator /=(const set<T>& s) {
    return this->difference(s);
}




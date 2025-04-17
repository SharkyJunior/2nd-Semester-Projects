#include <exception>
#include "set.hpp"

using namespace std;

template <typename T>
SetIterator<T>& SetIterator<T>::operator++() {
    this->next();
    return *this;
}
template <typename T>
SetIterator<T>& SetIterator<T>::operator++(int) {
    SetIterator temp = *this; 
    ++(*this);                
    return temp; 
}

template <typename T>
bool SetIterator<T>::operator !=(SetIterator<T> &b) {
    return !(*this == b);
}

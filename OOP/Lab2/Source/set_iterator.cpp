#include <exception>
#include "set.hpp"

using namespace std;

template <typename T>
T SetIterator<T>::value() {
    if (index >= container.get_length())
        throw out_of_range("Iterator is at end");
    T* arr = container.to_array();
    T val = arr[index];
    free(arr);
    return val;
}

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
bool SetIterator<T>::operator ==(SetIterator<T> &b) {
    const SetIterator<T>* otherIt = dynamic_cast<const SetIterator<T>*>(&b);
    if (!otherIt)
        return false;
    return (this->container == otherIt->container) && (this->index == otherIt->index);
}

template <typename T>
bool SetIterator<T>::operator !=(SetIterator<T> &b) {
    return !(*this == b);
}

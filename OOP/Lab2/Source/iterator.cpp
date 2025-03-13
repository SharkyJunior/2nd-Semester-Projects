#include <exception>
#include "iterator.hpp"

template <typename T>
Iterator<T>::Iterator(set<T> iterable) {
    if (iterable == NULL)
        throw std::exception("Container is empty");
    this->container_obj = &iterable;
}

template <typename T>
void Iterator<T>::next() {
    this->container_obj = this->container_obj->next;
}

template <typename T>
T Iterator<T>::value() {
    return this->container_obj->value;
}

template <typename T>
bool Iterator<T>::is_end() {
    return this->container_obj->next == NULL;
}

template <typename T>
Iterator<T> Iterator<T>::operator++() {
    this->container_obj = this->container_obj->next;
    return *this;
}

template <typename T>
T Iterator<T>::operator*() {
    return this->container_obj->value;
}

template <typename T>
bool Iterator<T>::operator ==(Iterator<T> &b) {
    return this->container_obj == b.container_obj;
}

template <typename T>
bool Iterator<T>::operator !=(Iterator<T> &b) {
    return this->container_obj != b.container_obj;
}

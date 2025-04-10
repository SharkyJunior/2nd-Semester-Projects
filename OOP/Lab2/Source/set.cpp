#include "set.hpp"

#include <initializer_list>
#include <iostream>

using namespace std;

template <typename T>
set<T>::set()
    : size(0), capacity(0)
{
    this->array = NULL;
}

template <typename T>
set<T>::set(T* arr) 
    : size(arr.size()), capacity(arr.size())
{   
    copy(arr, arr + this->size, this->array);
}

template <typename T>
set<T>::set(const set<T> &obj) 
    : size(obj.size), capacity(obj.capacity)
{
    copy(obj.array, obj.array + this->size, this->array);
}

template <typename T>
set<T>::set(set<T>&& s) 
    : size(s.size), capacity(s.capacity)
{
    array = s.array;
    s.array = NULL;
}

template <typename T>
set<T>::set(initializer_list<T> lst) 
    : size(lst.size()), capacity(lst.size())
{
    copy(lst.begin(), lst.end(), array);
}

template <typename T>
int set<T>::get_length() const {
    return size;
}

template <typename T>
bool set<T>::contains(const T& elem) {
    for (int i = 0; i < this->size; i++)
        if (array[i] == elem)
            return true;
    return false;
}

template <typename T>
void set<T>::add(const T& elem) {
    if (size == capacity) {
        capacity *= 2;
        T* new_array = new T[capacity];
        copy(array, array + size, new_array);
        delete[] array;
        array = new_array;
    }
    for (int i = 0; i < size; i++)
        if (array[i] == elem)
            return;
    array[size++] = elem;
}

template <typename T>
void set<T>::remove(const T& elem) {
    for (int i = 0; i < size; i++)
        if (array[i] == elem) {
            copy(array + i + 1, array + size, array + i);
            size--;
            return;
        }
}

template <typename T>
T* set<T>::to_array() {
    T* arr = new T[size];
    copy(array, array + size, arr);
    return arr;
}

template <typename T>
set<T>& set<T>::sunion(const set<T>& s) {
    for (int i = 0; i < s.size; i++)
        add(s.array[i]);
    return *this;
}

template <typename T>
set<T>& set<T>::intersection(const set<T>& s) {
    for (int i = 0; i < size; i++)
        if (!s.contains(array[i]))
            remove(array[i]);
    return *this;
}

template <typename T>
set<T>& set<T>::difference(const set<T>& s) {
    for (int i = 0; i < size; i++)
        if (s.contains(array[i]))
            remove(array[i]);
    return *this;
}

template <typename T>
Iterator<T> set<T>::begin() {
    return Iterator<T>(*this);
}

template <typename T>
Iterator<T> set<T>::end() {
    set<T> empty = set<T>();
    return Iterator<T>(*empty);
}

template <typename T>
void set<T>::clear() {
    delete[] array;
    array = NULL;
    size = 0;
    capacity = 0;
}

template <typename T>
set<T>& set<T>::operator=(const set<T> &obj) {
    this->size = obj.size;
    this->capacity = obj.capacity;
    delete[] this->array;
    this->array = new T[this->capacity];
    copy(obj.array, obj.array + this->size, this->array);
    return *this;
}

template<typename _T>
ostream& operator <<(ostream& os, const set<_T>& lst) {
    os << lst.array[0];
    for (int i = 1; i < lst.get_length(); i++)
        os << ", " << lst.array[i];
    return os;
}

template<typename T>
set<T>& operator +=(const set<T>& s) {
    
}



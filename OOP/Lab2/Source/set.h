#ifndef SET_H
#define SET_H

#include "iterator.hpp"
#include <initializer_list>
#include <iostream>

using namespace std;

template <typename T>
class SetIterator;

template <typename T>
class Set {
    T* array;
    size_t size;
    size_t capacity;

    friend T& SetIterator<T>::value();

    public:
    // constructors & destructor
        Set();
        Set(T* arr, size_t length);
        Set(const Set<T>& obj);
        Set(Set <T>&& s);
        explicit Set(initializer_list<T> lst);
        ~Set() = default;

    // methods
        int getLength() const;
        bool contains(const T& elem) const;
        void add(const T& elem);
        void remove(const T& elem);
        T* toArray() const;

        Set<T> sunion(const Set<T>& s);
        Set<T> intersection(const Set<T>& s);
        Set<T> difference(const Set<T>& s);
        SetIterator<T> begin() const;
        SetIterator<T> end() const;
        void clear();

    // operator overloads
        Set<T>& operator =(const Set<T> &obj);

        template<typename _T> friend 
        ostream& operator <<(ostream& os, const Set<_T>& lst);
        Set<T>& operator +=(const Set<T>& s);
        Set<T>& operator *=(const Set<T>& s);
        Set<T>& operator /=(const Set<T>& s);

        bool operator ==(const Set<T>& b) const;

        template<typename _T> friend 
        Set<_T> operator +(const Set<_T>& s1, const Set<_T>& s2);

        template<typename _T> friend 
        Set<_T> operator *(const Set<_T>& s1, const Set<_T>& s2);

        template<typename _T> friend 
        Set<_T> operator /(const Set<_T>& s1, const Set<_T>& s2);
        
};

template <typename T>
class SetIterator : public Iterator<T> {
    T* container;
    size_t len, index;

    public:
        SetIterator(const Set<T>& iterable, size_t index = 0);
        ~SetIterator();

        void next() override;
        T& value() override;
        bool is_end() override;

        SetIterator<T>& operator++();
        T& operator*() override;
        bool operator ==(SetIterator<T> &b);
        bool operator !=(SetIterator<T> &b);
}; 

#endif
#ifndef SET_H
#define SET_H

#include "iterator.hpp"

using namespace std;

template <typename T>
class set {
    T* array;
    size_t size;
    size_t capacity;

    public:
    // constructors & destructor
        set();
        set(T* arr);
        set(const set<T> &obj);
        set (set <T>&& s);
        explicit set(initializer_list<T> lst);
        ~set() = default;

    // methods
        int get_length() const;
        bool contains(const T& elem);
        void add(const T& elem);
        void remove(const T& elem);
        T* to_array();

        set<T>& sunion(const set<T>& s);
        set<T>& intersection(const set<T>& s);
        set<T>& difference(const set<T>& s);

        Iterator<T> begin();
        Iterator<T> end();

        void clear();

    // operator overloads
        set<T>& operator =(const set<T> &obj);

        template<typename _T>friend 
        ostream& operator <<(ostream& os, const set<_T>& lst);

        set<T>& operator +=(const set<T>& s);
        set<T>& operator *=(const set<T>& s);
        set<T>& operator /=(const set<T>& s);

        template<typename _T>friend set<_T> 
        operator +(const set<_T>& s1, const set<_T>& s2);

        template<typename _T>friend set<_T> 
        operator *(const set<_T>& s1, const set<_T>& s2);

        template<typename _T>friend set<_T> 
        operator /(const set<_T>& s1, const set<_T>& s2);

        
};

#endif
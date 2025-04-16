#ifndef SET_H
#define SET_H

#include "iterator.hpp"
#include <initializer_list>
#include <iostream>
#include <initializer_list>

#define DEFAULT_CAPACITY 16

using namespace std;

template <typename T>
class SetIterator;

template <typename T>
class set {
    T* array;
    size_t size;
    size_t capacity;

    public:
    // constructors & destructor
        set() : size(0), capacity(DEFAULT_CAPACITY) { this->array = NULL; }
        set(T* arr, size_t length)
            : capacity(length)
        {  
            array = new T[length]; 
            for (int i = 0; i < length; i++)
                if (!contains(arr[i]))
                    add(arr[i]);
        }
        
        set(const set<T> &obj)
            : size(obj.size), capacity(obj.capacity), array(nullptr)
        {
            if (capacity > 0) {
                array = new T[capacity];
                copy(obj.array, obj.array + size, array);
            } 
            else
                size = 0;
        }
        set (set <T>&& s);
        explicit set(initializer_list<T> lst)
            : capacity(lst.size())
        {
            array = new T[capacity];
            for (T i : lst) 
                if (!contains(i))
                    add(i);
        }
        ~set() = default;

    // methods
        int get_length() const{
            return size;
        }
        bool contains(const T& elem) const{
            for (int i = 0; i < this->size; i++)
                if (array[i] == elem)
                    return true;
            return false;
        }
        void add(const T& elem) {
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
        void remove(const T& elem) {
            for (int i = 0; i < size; i++)
                if (array[i] == elem) {
                    copy(array + i + 1, array + size, array + i);
                    size--;
                    return;
                }
        }
        T* to_array() const {
            T* arr = new T[size];
            copy(array, array + size, arr);
            return arr;
        }

        set<T> sunion(const set<T>& s) {
            set<T> result = *this;
            
            SetIterator<T> it = s.begin();
            while (!it.is_end()) {
                result.add(it.value());
                ++it;
            }

            return result;
        }
        set<T> intersection(const set<T>& s) {
            set<T> result;

            SetIterator<T> it = s.begin();
            while (!it.is_end()) {
                if (contains(it.value()))
                    result.add(it.value());
                ++it;
            }

            return result;
        }
        
        set<T> difference(const set<T>& s) {
            set<T> result;

            for (int i = 0; i < size; i++)
                if (!s.contains(array[i]))
                    result.add(array[i]);

            return result;
        }

        SetIterator<T> begin() const {
            return SetIterator<T>(*this);
        }
        SetIterator<T> end() const {
            return SetIterator<T>(*this, this->get_length());
        }

        void clear();

    // operator overloads
        set<T>& operator =(const set<T> &obj) {
            if (this == &obj)
                return *this;

            T* new_array = nullptr;
            if (obj.capacity > 0) {
                try {
                    new_array = new T[obj.capacity];
                } catch (const std::bad_alloc& e) {
                        throw;
                }
            }

            if (new_array) {
                SetIterator<T> it = obj.begin();
                SetIterator<T> end = obj.end();
                while (it != end) {
                    new_array[it.index] = it.value();
                    ++it;
                }
            }
                

            delete[] this->array;

            this->array = new_array;
            this->size = obj.size;
            this->capacity = obj.capacity;

            return *this;
        }

        template<typename _T> friend 
        ostream& operator <<(ostream& os, const set<_T>& lst)
        {
            SetIterator<_T> it = lst.begin();
            SetIterator<_T> end = lst.end();
            while (it != end) {
                os << it.value() << " ";
                ++it;
            }
        
            return os;
        };

        set<T>& operator +=(const set<T>& s);
        set<T>& operator *=(const set<T>& s);
        set<T>& operator /=(const set<T>& s);

        bool operator ==(const set<T>& b) const{
            if (this->size != b.size)
                return false;
            for (int i = 0; i < this->size; i++)
                if (!b.contains(this->array[i]))
                    return false;
            return true;
        }

        template<typename _T> friend 
        set<_T> operator +(const set<_T>& s1, const set<_T>& s2)
        {
            set<_T> res = s1;
            return res.sunion(s2);
        }

        template<typename _T> friend 
        set<_T> operator *(const set<_T>& s1, const set<_T>& s2)
        {
            set<_T> res = s1;
            return res.intersection(s2);
        }        

        template<typename _T> friend 
        set<_T> operator /(const set<_T>& s1, const set<_T>& s2)
        {
            set<_T> res = s1;
            return res.difference(s2);
        }
        
};

template <typename T>
class SetIterator : public Iterator<T> {
    const set<T>& container;
    size_t index;

    public:
        SetIterator(const set<T>& iterable, size_t index = 0) 
            : container(iterable), index(index) {}
        void next() override {
            if (index >= container.get_length())
                throw out_of_range("Iterator out of bounds");
            ++index;
        }
        T value() override {
            if (index >= container.get_length())
                throw out_of_range("Iterator is at end");
            return container.to_array()[index];
        }
        bool is_end() override {
            return index >= container.get_length();
        }
        SetIterator<T>& operator++() {
            this->next();
            return *this;
        }
        SetIterator<T>& operator++(int);
        T operator*() override {
            return this->value();
        }
        bool operator ==(SetIterator<T> &b) {
            const SetIterator<T>* otherIt = dynamic_cast<const SetIterator<T>*>(&b);
            if (!otherIt)
                return false;
            return (this->container == otherIt->container) && (this->index == otherIt->index);
        }
        bool operator !=(SetIterator<T> &b) {
            return !(*this == b);
        }
}; 

#endif
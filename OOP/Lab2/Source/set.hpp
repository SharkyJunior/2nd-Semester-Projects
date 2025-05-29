//#include "set.h"

#include "iterator.hpp"
#include <initializer_list>
#include <iostream>

#define DEFAULT_CAPACITY 16

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
        Set() : size(0), capacity(DEFAULT_CAPACITY) { this->array = new T[capacity]; }
        Set(T* arr, size_t length)
            : capacity(length)
        {  
            array = new T[length]; 
            for (int i = 0; i < length; i++)
                if (!contains(arr[i]))
                    add(arr[i]);
        }
        
        Set(const Set<T> &obj)
            : size(obj.size), capacity(obj.capacity), array(nullptr)
        {
            if (capacity > 0) {
                array = new T[capacity];
                copy(obj.array, obj.array + size, array);
            } 
            else
                size = 0;
        }
        Set (Set <T>&& s) 
            : size(s.size), capacity(s.capacity)
        {
            array = s.array;
            s.array = NULL;
        }
        explicit Set(initializer_list<T> lst)
            : capacity(lst.size())
        {
            array = new T[capacity];
            for (T i : lst) 
                if (!contains(i))
                    add(i);
        }
        ~Set() = default;

    // methods
        int getLength() const {
            return size;
        }
        bool contains(const T& elem) const{
            for (int i = 0; i < this->size; i++)
                if (array[i] == elem)
                    return true;
            return false;
        }
        void add(const T& elem) {
            for (int i = 0; i < size; i++)
                if (array[i] == elem)
                    return;
            if (size == capacity) {
                capacity *= 2;
                T* new_array = new T[capacity];
                copy(array, array + size, new_array);
                delete[] array;
                array = new_array;
            }
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
        T* toArray() const {
            T* arr = new T[size];
            copy(array, array + size, arr);
            return arr;
        }

        Set<T> sunion(const Set<T>& s) {
            Set<T> result = *this;
            
            for (T i : s) // foreach
                result.add(i);

            return result;
        }
        Set<T> intersection(const Set<T>& s) {
            Set<T> result;

            for (T i : s)
                if (contains(i))
                    result.add(i);

            return result;
        }
        
        Set<T> difference(const Set<T>& s) {
            Set<T> result;

            for (T i : *this)
                if (!s.contains(i))
                    result.add(i);

            for (T i : s)
                if (!contains(i))
                    result.add(i);

            return result;
        }

        SetIterator<T> begin() const {
            return SetIterator<T>(*this);
        }
        SetIterator<T> end() const {
            return SetIterator<T>(*this, this->getLength());
        }

        void clear() {
            delete[] array;
            array = new T[DEFAULT_CAPACITY];
            size = 0;
            capacity = DEFAULT_CAPACITY;
        }

    // operator overloads
        Set<T>& operator =(const Set<T> &obj) {
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
                while (!it.is_end()) {
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
        ostream& operator <<(ostream& os, const Set<_T>& lst)
        {
            for (_T i : lst)
                os << i << " ";
        
            return os;
        };

        Set<T>& operator +=(const Set<T>& s)  {
            return this->sunion(s);
        }

        Set<T>& operator *=(const Set<T>& s) {
            return this->intersection(s);
        }
        Set<T>& operator /=(const Set<T>& s) {
            return this->difference(s);
        }
        
        // obj1 == obj2       obj1.equals(obj2)
        bool operator ==(const Set<T>& b) const{
            if (this->size != b.size)
                return false;
            for (int i = 0; i < this->size; i++)
                if (!b.contains(this->array[i]))
                    return false;
            return true;
        }

        template<typename _T> friend 
        Set<_T> operator +(const Set<_T>& s1, const Set<_T>& s2)
        {
            Set<_T> res = s1;
            return res.sunion(s2);
        }

        template<typename _T> friend 
        Set<_T> operator *(const Set<_T>& s1, const Set<_T>& s2)
        {
            Set<_T> res = s1;
            return res.intersection(s2);
        }        

        template<typename _T> friend 
        Set<_T> operator /(const Set<_T>& s1, const Set<_T>& s2)
        {
            Set<_T> res = s1;
            return res.difference(s2);
        }
        
};

template <typename T>
class SetIterator : public Iterator<T> {
    const Set<T>& container;
    size_t len, index;

    public:
        SetIterator(const Set<T>& iterable, size_t index = 0) 
            : container(iterable), index(index), len(iterable.getLength()) {}
        
        ~SetIterator() = default;

        void next() override {
            if (index >= len)
                throw out_of_range("Iterator out of bounds");
            ++index;
        }
        T& value() override {
            if (index >= len)
                throw out_of_range("Iterator is at end");
            return container.array[index];
        }
        bool is_end() override {
            return len == 0 || index >= len;
        }
        SetIterator<T>& operator++() {
            this->next();
            return *this;
        }

        SetIterator<T>& operator++(int) {
            SetIterator temp = *this; 
            ++(*this);                
            return temp; 
        }

        T& operator*() override {
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
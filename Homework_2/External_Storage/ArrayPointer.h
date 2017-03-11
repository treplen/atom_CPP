//
// Created by sl on 11.03.17.
//

#ifndef ARRAY_ARRAYPOINTER_H
#define ARRAY_ARRAYPOINTER_H

#include <cstring>
#include <cstdint>
#include <iostream>

#define log(x) std::cout<<( x )<<std::endl

template <typename T>
class ArrayPointer
{
private:
    T * data_;
    size_t capacity_;
    size_t links_;
public:
    bool dislink();
    void link();
    bool ok() const;
    const uint32_t POISON = UINT32_MAX;
    explicit ArrayPointer(size_t capacity);
    ArrayPointer(const ArrayPointer<T>&);
    ~ArrayPointer();
    T& operator[](const size_t); //unsafe
    T& At(const size_t); //safe
    size_t capacity() const;
};



template <typename T>
ArrayPointer<T>::ArrayPointer(size_t capacity):data_(nullptr), capacity_(capacity), links_(1)
{
    if (capacity_ == 0) return;
    try
    {
        data_ = new T[capacity];
    }
    catch(std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
}

template <typename T>
ArrayPointer<T>::ArrayPointer(const ArrayPointer<T> & array_pointer):capacity_(array_pointer.capacity_), links_(1)
{
    try
    {
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
}

template <typename T>
ArrayPointer<T>::~ArrayPointer()
{
    delete[] data_;
    log("free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

template <typename T>
T& ArrayPointer<T>::operator[](const size_t index)
{
    return data_[index];
}

template <typename T>
T& ArrayPointer<T>::At(const size_t index)
{
    if (index<capacity_) return data_[index];
    throw std::out_of_range("bad value");
}

template <typename T>
bool ArrayPointer<T>::ok() const
{
    return (links_ != POISON) && (capacity_ != POISON);
}

template <typename T>
void ArrayPointer<T>::link()
{
    links_++;
    log("add link"+std::to_string(links_));
}

template <typename T>
bool ArrayPointer<T>::dislink()
{
    log("rem link"+std::to_string(links_-1));
    return !(--links_);
}

template <typename T>
size_t ArrayPointer<T>::capacity() const
{
    return capacity_;
}

/////////////////////
////    spec     ////
/////////////////////




template <>
class ArrayPointer<bool>
{
private:
    int access[8] = {0b00000001, 0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
    char * data_;
    size_t capacity_;
    size_t links_;
    bool helper_; //i'm useless here...
    bool & ret_val_;
    int index_;
    void _upd();
    inline size_t _capacity();
public:
    bool dislink();//same
    void link();//same
    bool ok() const;//same
    const uint32_t POISON = UINT32_MAX;
    explicit ArrayPointer(size_t capacity);
    ArrayPointer(const ArrayPointer<bool>&);
    ~ArrayPointer();
    bool& operator[](const size_t); //unsafe
    bool& At(const size_t); //safe
    size_t capacity() const; //same
};


void ArrayPointer<bool>::link()
{
    links_++;
    log("bool add link"+std::to_string(links_));
}

bool ArrayPointer<bool>::dislink()
{
    log("bool rem link"+std::to_string(links_-1));
    return !(--links_);
}

size_t ArrayPointer<bool>::capacity() const
{
    return capacity_;
}
size_t ArrayPointer<bool>::_capacity() {
    return (int)ceil(1. * capacity_ / 8);
}

ArrayPointer<bool>::ArrayPointer(size_t capacity): data_(nullptr), capacity_(capacity), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    if (capacity == 0) return;
    try
    {
        data_ = new char[_capacity()];
    }
    catch(std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
}

ArrayPointer<bool>::ArrayPointer(const ArrayPointer<bool> & array_pointer):capacity_(array_pointer.capacity_), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    try
    {
        int cap = _capacity();
        data_ = new char[cap];
        for (size_t i = 0; i < cap; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
}

void ArrayPointer<bool>::_upd()
{
    int i = index_ / 8;
    int j = index_ % 8;
    if (ret_val_) data_ [i] |=access[j];
}

bool& ArrayPointer<bool>::operator[](const size_t index)
{
    _upd();

    index_=index;
    int i = index / 8;
    int j = index % 8;
    char c = data_ [i];
    ret_val_ =(c & access[j]) ? 1:0;
    return ret_val_;
}

bool& ArrayPointer<bool>::At(const size_t index)
{
    _upd();
    if (index<capacity_){
        index_=index;
        int i = index / 8;
        int j = index % 8;
        char c = data_ [i];
        ret_val_ =(c & access[j]) ? 1 : 0;
        return ret_val_;
    }
    throw std::out_of_range("bad value");
}

ArrayPointer<bool>::~ArrayPointer()
{
    delete[] data_;
    log("bool free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

#endif //ARRAY_ARRAYPOINTER_H

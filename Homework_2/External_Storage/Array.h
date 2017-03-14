//
// Created by svuatoslav on 3/2/17.
//
#ifndef HOMEWORK_2_ARRAY_H
#define HOMEWORK_2_ARRAY_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include "ArrayPointer.h"
#include "Collection.h"
#include "Iterator.h"


template <typename T>
class Array:Collection<T>
{
private:
    int current_;
    ArrayPointer<T> * pointer_;

public:
    Iterator<T> begin();
    Iterator<T> end();

    explicit Array(size_t capacity);
    Array(const Array<T>&);
    ~Array();
    T& operator[](size_t position);
    T& At(size_t position);
    const Array<T>& operator=(const Array<T>&);//inc value of pointer
    Array<T>& clone() const; //deep copy of object
    bool ok() const;
    size_t capacity() const;
    T& operator*() const;
    Array<T>& operator+(int) const;
    Array<T>& operator-(int) const;
    Array<T>& operator++();
    Array<T>& operator--();
    Array<T>& operator+=(int);
    Array<T>& operator-=(int);
};


template <typename T>
Array<T>::Array(size_t capacity):current_(0), pointer_(new ArrayPointer<T>(capacity))
{}

template <typename T>
Array<T>::Array(const Array<T>& that):current_(0), pointer_(that.pointer_)
{
    that.pointer_->link();
}

template <typename T>
Array<T>::~Array()
{
    if (pointer_->dislink()) delete pointer_;
}

template <typename T>
T& Array<T>::operator[](size_t position)
{
    return (*pointer_)[position];
}

template <typename T>
T& Array<T>::At(size_t position)//////////&&&&&&&
{
    return pointer_->At(position);
}

template <typename T>
const Array<T>& Array<T>::operator=(const Array& that)
{
    Array swapper(that);
    std::swap(*this, swapper);
    return *this;
}

template <typename T>
Array<T>& Array<T>::clone() const
{
    Array<T> * ret = new Array<T>(0);
    ret->pointer_ = new ArrayPointer<T>(*this->pointer_);
    return *ret;
}

template <typename T>
bool Array<T>::ok() const
{
    return pointer_->ok();
}

template <typename T>
size_t Array<T>::capacity() const
{
    return pointer_->capacity();
}

template <typename T>
T& Array<T>::operator*() const
{
    if (current_ < 0) throw std::out_of_range("minus is not allow");
    return (*pointer_)[current_];
}

template <typename T>
Array<T>& Array<T>::operator+(int value) const
{
    Array<T> * ret = new Array<T>(*this);
    ret->current_ += value;
    return *ret;
}

template <typename T>
Array<T>& Array<T>::operator-(int value) const
{
    Array<T> * ret = new Array<T>(*this);
    ret->current_ -= value;
    return *ret;
}

template <typename T>
Array<T>& Array<T>::operator++()
{
    current_++;
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator--()
{
    current_--;
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator+=(int value)
{
    current_+=value;
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator-=(int value)
{
    current_-=value;
    return *this;
}

template <typename T>
Iterator<T> Array<T>::begin()
{
    return Iterator<T>(this,0);
}

template <typename T>
Iterator<T> Array<T>::end()
{
    return Iterator<T>(this,capacity());
}
//
//
//
//
//
//
//
//template <typename T>
//class Iterator {
//public:
//
//private:
//
//
//
//};

#endif //HOMEWORK_2_ARRAY_H
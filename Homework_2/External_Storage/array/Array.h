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

    static void swap(Array<T> *one, Array<T> *another); //std:swap don't want to work with me, it want to use operator=(((
public:
    Iterator<T>& begin();
    Iterator<T>& end();

    explicit Array(size_t capacity); //testirovano
    Array(const Array<T>&);//toje
    ~Array();//nado destructor
    T& operator[](size_t position);//prisv zn elem mas nebezopasno
    T& At(size_t position);//bezopasn
    const Array<T>& operator=(const Array<T>&);//inc value of pointer (copy mas j ssilka
    Array<T>& clone() const; //deep copy of object (copy mas j nezavisimie
    bool ok() const; //E
    size_t capacity() const;//size mas in constr
    T& operator*() const; //
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
Array<T>::Array(const Array<T>& that):current_(that.current_), pointer_(that.pointer_)
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

    swap(&swapper, this);

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
    return pointer_->At(current_);
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
    current_ += value;
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator-=(int value)
{
    current_ -= value;
    return *this;
}

template <typename T>
void Array<T>::swap(Array<T> *one, Array<T> *another)
{

    ArrayPointer<T> *pointer = one->pointer_;
    int current = one->current_;

    one->current_ = another->current_;
    one->pointer_ = another->pointer_;

    another->current_ = current;
    another->pointer_ = pointer;
}

template <typename T>
Iterator<T>& Array<T>::begin()
{
    Iterator<T> i(this);
    return i.GetBegin();
}

template <typename T>
Iterator<T>& Array<T>::end()
{
    Iterator<T> i(this);
    return i.GetEnd();
}



#endif //HOMEWORK_2_ARRAY_H
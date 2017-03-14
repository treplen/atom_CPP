//---------------------------------------
//! @file Array.h
//! Implementation of the array class
//---------------------------------------

#ifndef HOMEWORK_2_ARRAY_H
#define HOMEWORK_2_ARRAY_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include "ArrayPointer.h"
#include "ArrayPointerBool.h"
#include "Collection.h"
#include "Iterator.h"
#include "Utils.h"


template <typename T>
class Array:Collection<T>
{
private:
    int current_;
    ArrayPointer<T> * pointer_;

public:

//---------------------------------------
//! @brief Returns an iterator to the beginning of the array
//! @return An iterator to the beginning of the array
//---------------------------------------

    Iterator<T> begin();

//---------------------------------------
//! @brief Returns an iterator to the end of the array
//! @return An iterator to the end of the array
//---------------------------------------

    Iterator<T> end();

//---------------------------------------
//! @brief Constructor
//! @param capacity Maximum amount of elements in the array
//---------------------------------------

    explicit Array(size_t capacity);

//---------------------------------------
//! @brief Copy constructor
//! @param that Object to copy
//---------------------------------------

    Array(const Array<T>& that);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    ~Array();

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use At() instead
//---------------------------------------

    T& operator[](size_t position) const;

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    T& At(size_t position) const;

//---------------------------------------
//! @brief Assigns a value of a variable to the object
//! @param that Object with the required value
//! @return The assigned object
//---------------------------------------

    const Array<T>& operator=(const Array<T>& that);

//---------------------------------------
//! @brief Clones an object via deep copy
//! @return Clone of the object
//---------------------------------------

    Array<T>& clone() const;

//---------------------------------------
//! @brief Silent verifier
//! @return True if object is OK
//---------------------------------------

    bool ok() const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the info into
//! @param displacement A length of the padding
//---------------------------------------

    void dump(std::ostream& out,size_t displacement = 0) const;

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    size_t capacity() const;

//---------------------------------------
//! @brief Returns a value pointed by the internal pointer
//! @return A value pointed by the internal pointer
//---------------------------------------

    T& operator*() const;

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return An object with increased internal pointer
//---------------------------------------

    Array<T> operator+(int value) const;

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return An object with decreased internal pointer
//---------------------------------------

    Array<T> operator-(int value) const;

//---------------------------------------
//! @brief Increments the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Array<T>& operator++();

//---------------------------------------
//! @brief Decrements the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Array<T>& operator--();

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return A reference to the object
//---------------------------------------

    Array<T>& operator+=(int value);

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return An reference to the object
//---------------------------------------

    Array<T>& operator-=(int value);
};


template <typename T>
Array<T>::Array(size_t capacity):current_(0), pointer_(new ArrayPointer<T>(capacity))
{
    INFO(*this);
}

template <typename T>
Array<T>::Array(const Array<T>& that):current_(0), pointer_(that.pointer_)
{
    that.pointer_->link();
    INFO(*this);
}

template <typename T>
Array<T>::~Array()
{
    INFO(*this);
    if (pointer_->dislink()) delete pointer_;
}

template <typename T>
T& Array<T>::operator[](size_t position) const
{
    INFO(*this);
    return (*pointer_)[position];
}

template <typename T>
T& Array<T>::At(size_t position) const
{
    INFO(*this);
    return pointer_->At(position);
}

template <typename T>
const Array<T>& Array<T>::operator=(const Array& that)
{
    INFO(*this);
    Array swapper(that);
    std::swap(*this, swapper);
    INFO(*this);
    return *this;
}

template <typename T>
Array<T>& Array<T>::clone() const
{
    INFO(*this);
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
void Array<T>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"Array("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcurrent: "<<current_<<'\n';
    out<<tabs<<"\tpointer:\n";
    pointer_->dump(out,displacement+2);
    out<<tabs<<"}\n";

    delete [] tabs;
}

template <typename T>
size_t Array<T>::capacity() const
{
    INFO(*this);
    return pointer_->capacity();
}

template <typename T>
T& Array<T>::operator*() const
{
    INFO(*this);
    if (current_ < 0) throw std::out_of_range("minus is not allow");
    return (*pointer_)[current_];
}

template <typename T>
Array<T> Array<T>::operator+(int value) const
{
    INFO(*this);
    Array<T> ret(*this);
    ret.current_ += value;
    return ret;
}

template <typename T>
Array<T> Array<T>::operator-(int value) const
{
    INFO(*this);
    Array<T> ret(*this);
    ret.current_ -= value;
    return ret;
}

template <typename T>
Array<T>& Array<T>::operator++()
{
    INFO(*this);
    INFO(*this);
    current_++;
    INFO(*this);
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator--()
{
    INFO(*this);
    current_--;
    INFO(*this);
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator+=(int value)
{
    INFO(*this);
    current_+=value;
    INFO(*this);
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator-=(int value)
{
    INFO(*this);
    current_-=value;
    INFO(*this);
    return *this;
}

template <typename T>
Iterator<T> Array<T>::begin()
{
    INFO(*this);
    return Iterator<T>(this,0);
}

template <typename T>
Iterator<T> Array<T>::end()
{
    INFO(*this);
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
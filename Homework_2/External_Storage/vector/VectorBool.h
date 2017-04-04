//---------------------------------------
//! @file VectorBool.h
//! Specification of the vector class for bool type
//---------------------------------------

#ifndef HOMEWORK_2_VECTORBOOL_H
#define HOMEWORK_2_VECTORBOOL_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include "VectorPointer.h"
#include "VectorPointerBool.h"
#include "Collection.h"
#include "Iterator.h"
#include "Utils.h"

template <>
class Vector<bool>:Collection<bool>
{
private:
    int current_;
    VectorPointer<bool> * pointer_;
    static void swap(Vector<bool> *one, Vector<bool> *another);
public:

//---------------------------------------
//! @brief Returns an iterator to the beginning of the vector
//! @return An iterator to the beginning of the vector
//---------------------------------------

    Iterator<bool> begin();

//---------------------------------------
//! @brief Returns an iterator to the end of the vector
//! @return An iterator to the end of the vector
//---------------------------------------

    Iterator<bool> end();

//---------------------------------------
//! @brief Constructor
//! @param capacity Maximum amount of elements in the vector
//---------------------------------------

    explicit Vector(size_t capacity=0);

//---------------------------------------
//! @brief Copy constructor
//! @param that Object to copy
//---------------------------------------

    Vector(const Vector<bool>& that);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    ~Vector();

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use at() instead
//---------------------------------------

    bit_pointer operator[](size_t position) const;

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    bit_pointer at(size_t position) const;

//---------------------------------------
//! @brief Assigns a value of a variable to the object
//! @param that Object with the required value
//! @return The assigned object
//---------------------------------------

    const Vector<bool>& operator=(const Vector<bool>& that);

//---------------------------------------
//! @brief Clones an object via deep copy
//! @return Clone of the object
//---------------------------------------

    Vector<bool>& clone() const;

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
//! @brief Returns the size of the object
//! @return The size of the object
//---------------------------------------

    size_t size() const;

//---------------------------------------
//! @brief Returns a value pointed by the internal pointer
//! @return A value pointed by the internal pointer
//---------------------------------------

    bit_pointer operator*() const;

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return An object with increased internal pointer
//---------------------------------------

    Vector<bool> operator+(int value) const;

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return An object with decreased internal pointer
//---------------------------------------

    Vector<bool> operator-(int value) const;

//---------------------------------------
//! @brief Increments the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Vector<bool>& operator++();

//---------------------------------------
//! @brief Decrements the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Vector<bool>& operator--();

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return A reference to the object
//---------------------------------------

    Vector<bool>& operator+=(int value);

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return A reference to the object
//---------------------------------------

    Vector<bool>& operator-=(int value);

//---------------------------------------
//! @brief Change capacity and size of obj
//! @throws std::bad_alloc
//! @param n new size of vector
//---------------------------------------

    void resize(size_t );

//---------------------------------------
//! @brief Change capacity of obj
//! @throws std::bad_alloc
//! @param n new capacity of vector
//---------------------------------------

    void reserve(size_t );

//---------------------------------------
//! @brief Change capacity to size of vector
//---------------------------------------

    void shrink_to_fit();

//---------------------------------------
//! @brief Push the value to vector tail
//! @throws std::bad_alloc
//! @param elem element pushing to vector
//---------------------------------------

    void push_back(bool & );
    void push_back(bool && );
//---------------------------------------
//! @brief Pop the value from vector tail
//! @throws std::out_of_range
//---------------------------------------

    void pop_back();


};

Vector<bool>::Vector(size_t capacity):current_(0), pointer_(new VectorPointer<bool>(capacity))
{
    INFO(*this);
}

Vector<bool>::Vector(const Vector<bool>& that):current_(that.current_), pointer_(that.pointer_)
{
    that.pointer_->link();
    INFO(*this);
}

Vector<bool>::~Vector()
{
    INFO(*this);
    if (pointer_->dislink()) delete pointer_;
}

bit_pointer Vector<bool>::operator[](size_t position) const
{
    INFO(*this);
    return (*pointer_)[position];
}

bit_pointer Vector<bool>::at(size_t position) const
{
    INFO(*this);
    return pointer_->at(position);
}

const Vector<bool>& Vector<bool>::operator=(const Vector& that)
{
    INFO(*this);
    Vector swapper(that);
    swap(&swapper, this);
    INFO(*this);
    return *this;
}

Vector<bool>& Vector<bool>::clone() const
{
    INFO(*this);
    Vector<bool> * ret = new Vector<bool>(0);
    ret->pointer_ = new VectorPointer<bool>(*this->pointer_);
    return *ret;
}

bool Vector<bool>::ok() const
{
    return pointer_->ok();
}

void Vector<bool>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"Vector("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcurrent: "<<current_<<'\n';
    out<<tabs<<"\tpointer:\n";
    pointer_->dump(out,displacement+2);
    out<<tabs<<"}\n";

    delete [] tabs;
}

size_t Vector<bool>::capacity() const
{
    INFO(*this);
    return pointer_->capacity();
}

bit_pointer Vector<bool>::operator*() const
{
    INFO(*this);
    if (current_ < 0) throw std::out_of_range("minus is not allow");
    return pointer_->at(current_);
}

Vector<bool> Vector<bool>::operator+(int value) const
{
    INFO(*this);
    Vector<bool> ret(*this);
    ret.current_ += value;
    return ret;
}

Vector<bool> Vector<bool>::operator-(int value) const
{
    INFO(*this);
    Vector<bool> ret(*this);
    ret.current_ -= value;
    return ret;
}

Vector<bool>& Vector<bool>::operator++()
{
    INFO(*this);
    INFO(*this);
    current_++;
    INFO(*this);
    return *this;
}

Vector<bool>& Vector<bool>::operator--()
{
    INFO(*this);
    current_--;
    INFO(*this);
    return *this;
}

Vector<bool>& Vector<bool>::operator+=(int value)
{
    INFO(*this);
    current_+=value;
    INFO(*this);
    return *this;
}

Vector<bool>& Vector<bool>::operator-=(int value)
{
    INFO(*this);
    current_-=value;
    INFO(*this);
    return *this;
}

void Vector<bool>::swap(Vector<bool> *one, Vector<bool> *another)
{

    VectorPointer<bool> *pointer = one->pointer_;
    int current = one->current_;

    one->current_ = another->current_;
    one->pointer_ = another->pointer_;

    another->current_ = current;
    another->pointer_ = pointer;
}

Iterator<bool> Vector<bool>::begin()
{
    INFO(*this);
    return Iterator<bool>(this,0);
}

Iterator<bool> Vector<bool>::end()
{
    INFO(*this);
    return Iterator<bool>(this,capacity());
}

void Vector<bool>::resize(size_t e)
{
    pointer_->resize(e);
}

void Vector<bool>::pop_back()
{
    pointer_->pop_back();
}

void Vector<bool>::shrink_to_fit()
{
    pointer_->shrink_to_fit();
}

void Vector<bool>::push_back(bool & elem)
{
    pointer_->push_back(elem);
}

void Vector<bool>::push_back(bool && elem)
{
    bool &val = elem;
    pointer_->push_back(val);
}

size_t Vector<bool>::size() const {
    return pointer_->size();
}

void Vector<bool>::reserve(size_t n) {
    pointer_->reserve(n);
}


#endif //HOMEWORK_2_VECTORBOOL_H

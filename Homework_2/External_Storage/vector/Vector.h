//---------------------------------------
//! @file Vector.h
//! Implementation of the vector class
//---------------------------------------

#ifndef HOMEWORK_2_VECTOR_H
#define HOMEWORK_2_VECTOR_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include "VectorPointer.h"
#include "VectorPointerBool.h"
#include "Collection.h"
#include "Iterator.h"
#include "Utils.h"

template <typename T>
class Vector:Collection<T>
{
private:
    int current_;
    VectorPointer<T> * pointer_;
    static void swap(Vector<T> *one, Vector<T> *another);
public:

//---------------------------------------
//! @brief Returns an iterator to the beginning of the vector
//! @return An iterator to the beginning of the vector
//---------------------------------------

    Iterator<T> begin();

//---------------------------------------
//! @brief Returns an iterator to the end of the vector
//! @return An iterator to the end of the vector
//---------------------------------------

    Iterator<T> end();

//---------------------------------------
//! @brief Constructor
//! @param capacity Maximum amount of elements in the vector
//---------------------------------------

    explicit Vector(size_t capacity=0);

//---------------------------------------
//! @brief Copy constructor
//! @param that Object to copy
//---------------------------------------

    Vector(const Vector<T>& that);

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

    T& operator[](size_t position) const;

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    T& at(size_t position) const;

//---------------------------------------
//! @brief Assigns a value of a variable to the object
//! @param that Object with the required value
//! @return The assigned object
//---------------------------------------

    const Vector<T>& operator=(const Vector<T>& that);

//---------------------------------------
//! @brief Clones an object via deep copy
//! @return Clone of the object
//---------------------------------------

    Vector<T>& clone() const;

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

    T& operator*() const;

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return An object with increased internal pointer
//---------------------------------------

    Vector<T> operator+(int value) const;

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return An object with decreased internal pointer
//---------------------------------------

    Vector<T> operator-(int value) const;

//---------------------------------------
//! @brief Increments the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Vector<T>& operator++();

//---------------------------------------
//! @brief Decrements the internal pointer by one
//! @return A reference to the object
//---------------------------------------

    Vector<T>& operator--();

//---------------------------------------
//! @brief Increments the internal pointer by the specified value
//! @param value A value to increment the pointer with
//! @return A reference to the object
//---------------------------------------

    Vector<T>& operator+=(int value);

//---------------------------------------
//! @brief Decrements the internal pointer by the specified value
//! @param value A value to decrement the pointer with
//! @return A reference to the object
//---------------------------------------

    Vector<T>& operator-=(int value);

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

    void push_back(T & );
    void push_back(T && );
//---------------------------------------
//! @brief Pop the value from vector tail
//! @throws std::out_of_range
//---------------------------------------

    void pop_back();


};

template <typename T>
Vector<T>::Vector(size_t capacity):current_(0), pointer_(new VectorPointer<T>(capacity))
{
    INFO(*this);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& that):current_(that.current_), pointer_(that.pointer_)
{
    that.pointer_->link();
    INFO(*this);
}

template <typename T>
Vector<T>::~Vector()
{
    INFO(*this);
    if (pointer_->dislink()) delete pointer_;
}

template <typename T>
T& Vector<T>::operator[](size_t position) const
{
    INFO(*this);
    return (*pointer_)[position];
}

template <typename T>
T& Vector<T>::at(size_t position) const
{
    INFO(*this);
    return pointer_->at(position);
}

template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector& that)
{
    INFO(*this);
    Vector swapper(that);
    swap(&swapper, this);
    INFO(*this);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::clone() const
{
    INFO(*this);
    Vector<T> * ret = new Vector<T>(0);
    ret->pointer_ = new VectorPointer<T>(*this->pointer_);
    return *ret;
}

template <typename T>
bool Vector<T>::ok() const
{
    return pointer_->ok();
}

template <typename T>
void Vector<T>::dump(std::ostream& out,size_t displacement) const
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

template <typename T>
size_t Vector<T>::capacity() const
{
    INFO(*this);
    return pointer_->capacity();
}

template <typename T>
T& Vector<T>::operator*() const
{
    INFO(*this);
    if (current_ < 0) throw std::out_of_range("minus is not allow");
    return pointer_->at(current_);
}

template <typename T>
Vector<T> Vector<T>::operator+(int value) const
{
    INFO(*this);
    Vector<T> ret(*this);
    ret.current_ += value;
    return ret;
}

template <typename T>
Vector<T> Vector<T>::operator-(int value) const
{
    INFO(*this);
    Vector<T> ret(*this);
    ret.current_ -= value;
    return ret;
}

template <typename T>
Vector<T>& Vector<T>::operator++()
{
    INFO(*this);
    INFO(*this);
    current_++;
    INFO(*this);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator--()
{
    INFO(*this);
    current_--;
    INFO(*this);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(int value)
{
    INFO(*this);
    current_+=value;
    INFO(*this);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(int value)
{
    INFO(*this);
    current_-=value;
    INFO(*this);
    return *this;
}

template <typename T>
void Vector<T>::swap(Vector<T> *one, Vector<T> *another)
{

    VectorPointer<T> *pointer = one->pointer_;
    int current = one->current_;

    one->current_ = another->current_;
    one->pointer_ = another->pointer_;

    another->current_ = current;
    another->pointer_ = pointer;
}

template <typename T>
Iterator<T> Vector<T>::begin()
{
    INFO(*this);
    return Iterator<T>(this,0);
}

template <typename T>
Iterator<T> Vector<T>::end()
{
    INFO(*this);
    return Iterator<T>(this,capacity());
}

template <typename T>
void Vector<T>::resize(size_t e)
{
    pointer_->resize(e);
}

template <typename T>
void Vector<T>::pop_back()
{
    pointer_->pop_back();
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    pointer_->shrink_to_fit();
}

template <typename T>
void Vector<T>::push_back(T & elem)
{
    pointer_->push_back(elem);
}

template <typename T>
void Vector<T>::push_back(T && elem)
{
    T &val = elem;
    pointer_->push_back(val);
}

template <typename T>
size_t Vector<T>::size() const {
    return pointer_->size();
}

template <typename T>
void Vector<T>::reserve(size_t n) {
    pointer_->reserve(n);
}

#include "VectorBool.h"

#endif //HOMEWORK_2_VECTOR_H

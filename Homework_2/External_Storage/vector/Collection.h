//---------------------------------------
//! @file Collection.h
//! Declaration of an abstract collection class
//---------------------------------------

#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H

#include <cstring>
#include "bit_pointer.h"

template <typename T>
class Collection
{
public:

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    virtual ~Collection(){} ;

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use At() instead
//---------------------------------------

    virtual T& operator[](size_t) const = 0;

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    virtual T& at(size_t position) const = 0;

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    virtual size_t capacity() const = 0;

//---------------------------------------
//! @brief Returns the size of the object
//! @return The size of the object
//---------------------------------------

    virtual size_t size() const = 0;

//---------------------------------------
//! @brief Returns a value pointed by the internal pointer
//! @return A value pointed by the internal pointer
//---------------------------------------

    virtual T& operator*() const = 0;
};

template <>
class Collection<bool>
{
public:

    virtual ~Collection(){} ;
    virtual bit_pointer operator[](size_t) const = 0;
    virtual bit_pointer at(size_t position) const = 0;
    virtual size_t capacity() const = 0;
    virtual size_t size() const = 0;
    virtual bit_pointer operator*() const = 0;
};

#endif //VECTOR_COLLECTION_H

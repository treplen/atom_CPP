//---------------------------------------
//! @file Collection.h
//! Declaration of an abstract collection class
//---------------------------------------

#ifndef ARRAY_COLLECTION_H
#define ARRAY_COLLECTION_H

#include <cstring>

template <typename T>
class Collection
{
public:

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    virtual ~Collection(){} ;

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use At() instead
//---------------------------------------

    virtual T& operator[](size_t) const = 0;

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    virtual T& At(size_t position) const = 0;

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    virtual size_t capacity() const = 0;

//---------------------------------------
//! @brief Returns a value pointed by the internal pointer
//! @return A value pointed by the internal pointer
//---------------------------------------

    virtual T& operator*() const = 0;
};

#endif //ARRAY_COLLECTION_H

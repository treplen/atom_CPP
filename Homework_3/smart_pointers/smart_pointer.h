//---------------------------------------
//! @file smart_pointer.h
//! Declaration of the smart_pointer abstract class
//---------------------------------------

#ifndef HOMEWORK_3_SMART_POINTER_H
#define HOMEWORK_3_SMART_POINTER_H

#include "Utils.h"

//---------------------------------------
//! @class smart_pointer
//! @brief An abstract class that is inherited by implemented smart pointers
//---------------------------------------

template<typename T>
class smart_pointer
{
public:

//---------------------------------------
//! @brief Returns the stored pointer
//! @returns The stored pointer
//---------------------------------------

    virtual T *get () const = 0;

//---------------------------------------
//! @brief Returns the pointed object
//! @returns The pointed object
//---------------------------------------

    virtual T &operator* () const = 0;

//---------------------------------------
//! @brief Returns the stored pointer that makes it possible to use the -> operator of the stored class
//! @returns The stored pointer
//---------------------------------------

    virtual T *operator-> () const = 0;

//---------------------------------------
//! @brief Assignment operator
//! @param ptr Pointer to store
//! @returns Copied stored pointer
//---------------------------------------

    virtual T *operator= (T *ptr) = 0;

//---------------------------------------
//! @brief Type cast to boolean
//! @returns True if the pointer is assigned
//---------------------------------------

    virtual operator bool () const = 0;

//---------------------------------------
//! @brief Removes the object's ownership over the stored pointer
//! @returns Previously stored pointer
//---------------------------------------

    virtual T *release () = 0;

//---------------------------------------
//! @brief Deletes the stored object and sets the stored pointer to a new value
//! @param ptr A value to replace the stored pointer with
//! @returns Copied stored pointer
//---------------------------------------

    virtual void reset (T *ptr) = 0;

//---------------------------------------
//! @brief Silent verifier
//! @returns True if no errors has occurred
//---------------------------------------

    virtual bool ok () const = 0;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &out) const =0;

//---------------------------------------
//! @brief Dumper for rvalues
//! @param out A rvalue stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &&out) const =0;
};

#endif //HOMEWORK_3_SMART_POINTER_H

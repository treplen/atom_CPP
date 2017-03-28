//---------------------------------------
//! @file unique_ptr.h
//! Definition of the unique pointer class
//---------------------------------------

#ifndef HOMEWORK_3_UNIQUE_PTR_H
#define HOMEWORK_3_UNIQUE_PTR_H

#include "smart_pointer.h"

//---------------------------------------
//! @class unique_ptr is an implementation of the unique smart pointer
//---------------------------------------

template<typename T>
class unique_ptr : public smart_pointer<T>
{
    T *pointer_;
public:

//---------------------------------------
//! @brief Constructor
//! @param pointer A pointer to be stored
//---------------------------------------

    unique_ptr (T *pointer = nullptr);

//---------------------------------------
//! @brief Copy constructor
//! @note You cant copy unique pointers
//---------------------------------------

    unique_ptr (const unique_ptr &that) = delete;

//---------------------------------------
//! @brief Move constructor for rvalues
//! @param that An rvalue to be moved to the object
//---------------------------------------

    unique_ptr (const unique_ptr &&that);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    virtual ~unique_ptr ();

//---------------------------------------
//! @brief Returns the stored pointer
//! @returns The stored pointer
//---------------------------------------

    T *get () const;

//---------------------------------------
//! @brief Returns the pointed object
//! @returns The pointed object
//---------------------------------------

    T &operator* () const;

//---------------------------------------
//! @brief Returns the stored pointer that makes it possible to use the -> operator of the stored class
//! @returns The stored pointer
//---------------------------------------

    T *operator-> () const;

//---------------------------------------
//! @brief Assignment operator
//! @param ptr Pointer to store
//! @returns Copied stored pointer
//---------------------------------------

    virtual T *operator= (T *t);

//---------------------------------------
//! @brief Assignation operator
//! @note You cant assign unique pointers with each other
//---------------------------------------

    const unique_ptr &operator= (const unique_ptr &)= delete;

//---------------------------------------
//! @brief Assignation operator for rvalue
//! @param that An rvalue to be assigned to the object
//---------------------------------------

    const unique_ptr &operator= (unique_ptr &&);

//---------------------------------------
//! @brief Type cast to boolean
//! @returns True if the pointer is assigned
//---------------------------------------

    operator bool () const;

//---------------------------------------
//! @brief Removes the object's ownership over the stored pointer
//! @returns Previously stored pointer
//---------------------------------------

    virtual T *release ();

//---------------------------------------
//! @brief Deletes the stored object and sets the stored pointer to a new value
//! @param ptr A value to replace the stored pointer with
//! @returns Copied stored pointer
//---------------------------------------


    virtual void reset (T *t = nullptr);

//---------------------------------------
//! @brief Silent verifier
//! @returns True if no errors has occurred
//---------------------------------------

    virtual bool ok () const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &ostream) const;

//---------------------------------------
//! @brief Dumper for rvalues
//! @param out A rvalue stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &&ostream) const;

//---------------------------------------
//! @brief Swaps the containment of two objects
//! @param that A value to swap this object with
//---------------------------------------

    virtual void swap (unique_ptr &that);
};

template<typename T>
T *unique_ptr<T>::get () const
{
    INFO(*this);
    return pointer_;
}

template<typename T>
T &unique_ptr<T>::operator* () const
{
    INFO(*this);
    if (pointer_ != nullptr)
        return *pointer_;
    throw "Pointer is empty";
}

template<typename T>
T *unique_ptr<T>::operator-> () const
{
    INFO(*this);
    return pointer_;
}

template<typename T>
T *unique_ptr<T>::operator= (T *t)
{
    INFO(*this);
    delete pointer_;
    pointer_ = t;
    INFO(*this);
    return pointer_;
}

template<typename T>
unique_ptr<T>::operator bool () const
{
    INFO(*this);
    return pointer_ != nullptr;
}

template<typename T>
T *unique_ptr<T>::release ()
{
    INFO(*this);
    T *ret = pointer_;
    pointer_ = nullptr;
    INFO(*this);
    return ret;
}

template<typename T>
void unique_ptr<T>::reset (T *t)
{
    INFO(*this);
    delete pointer_;
    pointer_ = t;
    INFO(*this);
}

template<typename T>
bool unique_ptr<T>::ok () const
{
    return pointer_ != (T *) utils::POISON_PTR;
}

template<typename T>
void unique_ptr<T>::dump (utils::ostream &ostream) const
{
    ostream.println ("unique_ptr (", ok () ? "OK" : "ERROR", ") @ ", this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("pointer_ = ", (void *) pointer_, pointer_ == (void *) utils::POISON_PTR ? " (POISON_PTR)" : "");
    --ostream;
    ostream.println ('}');
}

template<typename T>
void unique_ptr<T>::dump (utils::ostream &&ostream) const
{
    dump (ostream);
}

template<typename T>
unique_ptr<T>::unique_ptr (T *pointer):pointer_ (pointer)
{
    INFO(*this);
}

template<typename T>
unique_ptr<T>::~unique_ptr ()
{
    INFO(*this);
    delete pointer_;
    pointer_ = (T *) utils::POISON_PTR;
}

template<typename T>
unique_ptr<T>::unique_ptr (const unique_ptr<T> &&that):pointer_ (that.pointer_)
{
    INFO(*this);
}

template<typename T>
const unique_ptr<T> &unique_ptr<T>::operator= (unique_ptr<T> &&that)
{
    INFO(*this);
    swap (that);
    INFO(*this);
    return *this;
}

template<typename T>
void unique_ptr<T>::swap (unique_ptr<T> &that)
{
    INFO(*this);
    T *buf;
    buf = pointer_;
    pointer_ = that.pointer_;
    that.pointer_ = buf;
    INFO(*this);
}

#endif //HOMEWORK_3_UNIQUE_PTR_H

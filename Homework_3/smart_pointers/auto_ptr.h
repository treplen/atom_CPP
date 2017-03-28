//---------------------------------------
//! @file auto_ptr.h
//! Definition of the auto_ptr class
//---------------------------------------

#ifndef HOMEWORK_3_AUTO_PTR_H
#define HOMEWORK_3_AUTO_PTR_H

#include "unique_ptr.h"

//---------------------------------------
//! @class auto_ptr is an implementation of the auto smart pointer
//---------------------------------------

template<typename T>
class auto_ptr : public unique_ptr<T>
{
public:

//---------------------------------------
//! @brief Constructor
//! @param pointer A pointer to be stored
//---------------------------------------

    auto_ptr (T *ptr = nullptr);

//---------------------------------------
//! @brief Copy constructor
//! @param that A value to be copied to the object
//! @note This copy constructor moves containment instead of copying
//---------------------------------------

    auto_ptr (auto_ptr &that);

//---------------------------------------
//! @brief Move constructor for rvalues
//! @param that An rvalue to be moved to the object
//---------------------------------------

    auto_ptr (auto_ptr &&that);

//---------------------------------------
//! @brief Assignation operator
//! @param that A value to be assigned to the object
//! @note This operator moves containment instead of copying
//---------------------------------------

    auto_ptr &operator= (auto_ptr &that);

//---------------------------------------
//! @brief Assignation operator for rvalue
//! @param that An rvalue to be assigned to the object
//---------------------------------------

    auto_ptr &operator= (auto_ptr &&that);

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &out) const;

//---------------------------------------
//! @brief Dumper for rvalues
//! @param out A rvalue stream to output the result into
//---------------------------------------

    virtual void dump (utils::ostream &&out) const;
};

template<typename T>
auto_ptr<T>::auto_ptr (T *ptr) : unique_ptr<T> (ptr)
{
    INFO(*this);
}

template<typename T>
auto_ptr<T>::auto_ptr (auto_ptr &that): unique_ptr<T> (that.release ())
{
    INFO(*this);
}

template<typename T>
auto_ptr<T>::auto_ptr (auto_ptr &&that): unique_ptr<T> (that.release ())
{
    INFO(*this);
}

template<typename T>
auto_ptr<T> &auto_ptr<T>::operator= (auto_ptr &that)
{
    INFO(*this);
    this->swap (that);
    INFO(*this);
    return *this;
}

template<typename T>
auto_ptr<T> &auto_ptr<T>::operator= (auto_ptr &&that)
{
    INFO(*this);
    this->swap (that);
    INFO(*this);
    return *this;
}

template<typename T>
void auto_ptr<T>::dump (utils::ostream &out) const
{
    out.println ("auto_ptr (", this->ok () ? "OK" : "ERROR", ") @ ", this);
    out.println ('{');
    ++out;
    unique_ptr<T>::dump (out);
    --out;
    out.println ('}');
}

template<typename T>
void auto_ptr<T>::dump (utils::ostream &&out) const
{
    dump (out);
}

#endif //HOMEWORK_3_AUTO_PTR_H

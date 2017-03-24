//
// Created by svuatoslav on 3/24/17.
//

#ifndef HOMEWORK_3_AUTO_PTR_H
#define HOMEWORK_3_AUTO_PTR_H

#include "unique_ptr.h"

template <typename T>
class auto_ptr: public unique_ptr<T>
{
public:
    auto_ptr(T* ptr=nullptr);
    auto_ptr(auto_ptr& that);
    auto_ptr(auto_ptr&& that);
    auto_ptr&operator=(auto_ptr& that);
    virtual void dump(utils::ostream& out) const;
    virtual void dump(utils::ostream&& out) const;
};

template <typename T>
auto_ptr<T>::auto_ptr (T *ptr) : unique_ptr<T> (ptr)
{
    INFO(*this);
}

template <typename T>
auto_ptr<T>::auto_ptr (auto_ptr &that): unique_ptr<T> (that.release ())
{
    INFO(*this);
}

template <typename T>
auto_ptr<T>::auto_ptr (auto_ptr &&that): unique_ptr<T> (that.release ())
{
    INFO(*this);
}

template <typename T>
auto_ptr<T> &auto_ptr<T>::operator= (auto_ptr &that)
{
    INFO(*this);
    this->reset (that.release ());
    INFO(*this);
    return *this;
}

template <typename T>
void auto_ptr<T>::dump (utils::ostream &out) const
{
    out.println ("auto_ptr (",this->ok()?"OK":"ERROR",") @ ",this);
    out.println ('{');
    ++out;
    unique_ptr<T>::dump (out);
    --out;
    out.println ('}');
}

template <typename T>
void auto_ptr<T>::dump (utils::ostream &&out) const
{
    dump (out);
}

#endif //HOMEWORK_3_AUTO_PTR_H

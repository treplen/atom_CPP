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
    virtual void dump(utils::ostream& out);
};

template <typename T>
auto_ptr<T>::auto_ptr (T *ptr) : unique_ptr<T> (ptr)
{
}

template <typename T>
auto_ptr<T>::auto_ptr (auto_ptr &that): unique_ptr<T> (that.release ())
{
}

template <typename T>
auto_ptr<T>::auto_ptr (auto_ptr &&that): unique_ptr<T> (that.release ())
{
}

template <typename T>
auto_ptr<T> &auto_ptr<T>::operator= (auto_ptr &that)
{
    this->reset (that.release ());
    return *this;
}

template <typename T>
void auto_ptr<T>::dump (utils::ostream &out)
{
    out.println ("auto_ptr (",this->ok()?"OK":"ERROR",") @ ",this);
    out.println ('{');
    ++out;
    unique_ptr<T>::dump (out);
    --out;
    out.println ('}');
}

#endif //HOMEWORK_3_AUTO_PTR_H

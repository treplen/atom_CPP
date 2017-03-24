//
// Created by svuatoslav on 3/24/17.
//

#ifndef HOMEWORK_3_SMART_POINTER_H
#define HOMEWORK_3_SMART_POINTER_H

#include "Utils.h"

template <typename T>
class smart_pointer
{
public:
    virtual T* get() const = 0;
    virtual T& operator*() const = 0;
    virtual T*operator->() const = 0;
    virtual T*operator=(T*) = 0;
    virtual operator bool() const = 0;
    virtual T* release() = 0;
    virtual void reset(T*) = 0;
    virtual bool ok() = 0;
    virtual void dump(utils::ostream&)=0;
};

#endif //HOMEWORK_3_SMART_POINTER_H

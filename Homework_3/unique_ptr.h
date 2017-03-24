//
// Created by svuatoslav on 3/24/17.
//

#ifndef HOMEWORK_3_UNIQUE_PTR_H
#define HOMEWORK_3_UNIQUE_PTR_H

#include "smart_pointer.h"

template <typename T>
class unique_ptr: public smart_pointer<T>
{
    T* pointer_;
public:

    unique_ptr(T* pointer=nullptr);

    unique_ptr(const unique_ptr&)= delete;

    virtual ~unique_ptr ();

    T *get () const;

    T &operator* () const;

    T *operator-> () const;

    virtual T *operator= (T *t);

    const unique_ptr&operator=(const unique_ptr&)= delete;

    operator bool () const;

    virtual T *release ();

    virtual void reset (T *t);

    virtual bool ok ();

    virtual void dump (utils::ostream &ostream);
};

template <typename T>
T *unique_ptr<T>::get () const
{
    return pointer_;
}

template <typename T>
T &unique_ptr<T>::operator* () const
{
    if(pointer_!= nullptr)
        return *pointer_;
    throw "Pointer is empty";
}

template <typename T>
T *unique_ptr<T>::operator-> () const
{
    return pointer_;
}

template <typename T>
T *unique_ptr<T>::operator= (T *t)
{
    delete pointer_;
    pointer_=t;
    return pointer_;
}

template <typename T>
unique_ptr<T>::operator bool () const
{
    return pointer_!= nullptr;
}

template <typename T>
T *unique_ptr<T>::release ()
{
    T* ret = pointer_;
    pointer_= nullptr;
    return ret;
}

template <typename T>
void unique_ptr<T>::reset (T *t)
{
    delete pointer_;
    pointer_ = t;
}

template <typename T>
bool unique_ptr<T>::ok ()
{
    return pointer_!=(void*)utils::POISON_PTR;
}

template <typename T>
void unique_ptr<T>::dump (utils::ostream &ostream)
{
    ostream.println ("unique_ptr (",ok()?"OK":"ERROR",") @ ",this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("pointer_ = ",(void*)pointer_,pointer_==(void*)utils::POISON_PTR?" (POISON_PTR)":"");
    --ostream;
    ostream.println ('}');
}

template <typename T>
unique_ptr<T>::unique_ptr (T *pointer):pointer_(pointer)
{
}

template <typename T>
unique_ptr<T>::~unique_ptr ()
{
    delete pointer_;
    pointer_=(int*)utils::POISON_PTR;
}

#endif //HOMEWORK_3_UNIQUE_PTR_H

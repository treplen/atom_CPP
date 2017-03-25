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

    unique_ptr(const unique_ptr&&);

    virtual ~unique_ptr ();

    T *get () const;

    T &operator* () const;

    T *operator-> () const;

    virtual T *operator= (T *t);

    const unique_ptr&operator=(const unique_ptr&)= delete;

    const unique_ptr&operator=(unique_ptr&&);

    operator bool () const;

    virtual T *release ();

    virtual void reset (T *t);

    virtual bool ok () const;

    virtual void dump (utils::ostream &ostream) const ;

    virtual void dump (utils::ostream &&ostream) const ;

    virtual void swap (unique_ptr &);
};

template <typename T>
T *unique_ptr<T>::get () const
{
    INFO(*this);
    return pointer_;
}

template <typename T>
T &unique_ptr<T>::operator* () const
{
    INFO(*this);
    if(pointer_!= nullptr)
        return *pointer_;
    throw "Pointer is empty";
}

template <typename T>
T *unique_ptr<T>::operator-> () const
{
    INFO(*this);
    return pointer_;
}

template <typename T>
T *unique_ptr<T>::operator= (T *t)
{
    INFO(*this);
    delete pointer_;
    pointer_=t;
    INFO(*this);
    return pointer_;
}

template <typename T>
unique_ptr<T>::operator bool () const
{
    INFO(*this);
    return pointer_!= nullptr;
}

template <typename T>
T *unique_ptr<T>::release ()
{
    INFO(*this);
    T* ret = pointer_;
    pointer_= nullptr;
    INFO(*this);
    return ret;
}

template <typename T>
void unique_ptr<T>::reset (T *t)
{
    INFO(*this);
    delete pointer_;
    pointer_ = t;
    INFO(*this);
}

template <typename T>
bool unique_ptr<T>::ok () const
{
    return pointer_!=(void*)utils::POISON_PTR;
}

template <typename T>
void unique_ptr<T>::dump (utils::ostream &ostream) const
{
    ostream.println ("unique_ptr (",ok()?"OK":"ERROR",") @ ",this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("pointer_ = ",(void*)pointer_,pointer_==(void*)utils::POISON_PTR?" (POISON_PTR)":"");
    --ostream;
    ostream.println ('}');
}

template <typename T>
void unique_ptr<T>::dump (utils::ostream &&ostream) const
{
    dump (ostream);
}

template <typename T>
unique_ptr<T>::unique_ptr (T *pointer):pointer_(pointer)
{
    INFO(*this);
}

template <typename T>
unique_ptr<T>::~unique_ptr ()
{
    INFO(*this);
    delete pointer_;
    pointer_=(int*)utils::POISON_PTR;
}

template <typename T>
unique_ptr<T>::unique_ptr (const unique_ptr<T> && that):pointer_(that.pointer_)
{
    INFO(*this);
}

template <typename T>
const unique_ptr<T> &unique_ptr<T>::operator= (unique_ptr<T> && that)
{
    INFO(*this);
    swap (that);
    INFO(*this);
    return *this;
}

template <typename T>
void unique_ptr<T>::swap (unique_ptr<T> & that)
{
    INFO(*this);
    T* buf;
    buf=pointer_;
    pointer_=that.pointer_;
    that.pointer_=buf;
    INFO(*this);
}

#endif //HOMEWORK_3_UNIQUE_PTR_H

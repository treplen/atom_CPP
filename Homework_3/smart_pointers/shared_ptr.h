//
// Created by svuatoslav on 3/24/17.
//

#ifndef HOMEWORK_3_SHARED_PTR_H
#define HOMEWORK_3_SHARED_PTR_H

#include "unique_ptr.h"

template <typename T>
class shared_ptr: public smart_pointer<T>
{
    class proxy_ptr: public unique_ptr<T>
    {
        int links;
    public:
        void link();
        bool dislink();
        bool linked();
        virtual bool ok() const;
        virtual void dump(utils::ostream&) const;
        virtual void dump(utils::ostream&&) const;
        proxy_ptr(T* ptr = nullptr);
        virtual ~proxy_ptr ();
    };

    proxy_ptr* pointer_;

public:
    shared_ptr(T* t= nullptr);

    shared_ptr(const shared_ptr&);

    virtual ~shared_ptr ();

    virtual T *get () const;

    virtual T &operator* () const;

    virtual T *operator-> () const;

    virtual T *operator= (T *t);

    const shared_ptr&operator=(const shared_ptr& that);

    virtual operator bool () const;

    virtual T *release ();

    virtual void reset (T *t);

    virtual bool ok () const;

    virtual void dump (utils::ostream &ostream) const;

    virtual void dump (utils::ostream &&ostream) const;

};

template <typename T>
void shared_ptr<T>::proxy_ptr::link ()
{
    INFO(*this);
    links++;
    INFO(*this);
}

template <typename T>
bool shared_ptr<T>::proxy_ptr::dislink ()
{
    INFO(*this);
    --links;
    INFO(*this);
    return links==0;
}

template <typename T>
bool shared_ptr<T>::proxy_ptr::linked ()
{
    INFO(*this);
    return links>0;
}

template <typename T>
bool shared_ptr<T>::proxy_ptr::ok () const
{
    return unique_ptr<T>::ok () && links!=utils::POISON_INT;
}

template <typename T>
void shared_ptr<T>::proxy_ptr::dump (utils::ostream & ostream) const
{
    ostream.println ("proxy_ptr (",ok()?"OK":"ERROR",") @ ",this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("links = ",links,links==utils::POISON_INT?" (POISON)":"");
    unique_ptr<T>::dump ( ostream);
    --ostream;
    ostream.println ('}');
}

template <typename T>
void shared_ptr<T>::proxy_ptr::dump (utils::ostream && ostream) const
{
    dump (ostream);
}

template <typename T>
shared_ptr<T>::proxy_ptr::proxy_ptr (T *ptr) : unique_ptr<T> (ptr),links(1)
{
    INFO(*this);
}

template <typename T>
shared_ptr<T>::proxy_ptr::~proxy_ptr ()
{
    links=utils::POISON_INT;
}

template <typename T>
T *shared_ptr<T>::get () const
{
    INFO(*this);
    if(pointer_!= nullptr)
        return pointer_->get ();
    return nullptr;
}

template <typename T>
T &shared_ptr<T>::operator* () const
{
    INFO(*this);
    if(pointer_!= nullptr)
        return pointer_->operator* ();
    throw "Pointer is empty";
}

template <typename T>
T *shared_ptr<T>::operator-> () const
{
    INFO(*this);
    if(pointer_!= nullptr)
        return pointer_->operator-> ();
    return nullptr;
}

template <typename T>
T *shared_ptr<T>::operator= (T *t)
{
    INFO(*this);
    if(pointer_== nullptr)
        pointer_=new proxy_ptr();
    pointer_->reset (t);
    INFO(*this);
    return t;
}

template <typename T>
shared_ptr<T>::operator bool () const
{
    INFO(*this);
    if(pointer_!= nullptr)
        return (bool)pointer_;
    return false;
}

template <typename T>
T *shared_ptr<T>::release ()
{
    INFO(*this);
    if(pointer_== nullptr)
        return nullptr;
    T* ret = pointer_->get ();
    if(pointer_->dislink ()) delete pointer_;
    pointer_=nullptr;
    INFO(*this);
    return ret;
}

template <typename T>
void shared_ptr<T>::reset (T *t)
{
    INFO(*this);
    if(pointer_!= nullptr && pointer_->dislink ()) delete pointer_;
    pointer_=new proxy_ptr(t);
    INFO(*this);
}

template <typename T>
bool shared_ptr<T>::ok () const
{
    if(pointer_==utils::POISON_PTR)
        return false;
    return pointer_== nullptr || pointer_->ok();
}

template <typename T>
void shared_ptr<T>::dump (utils::ostream &ostream) const
{
    ostream.println ("shared_ptr (",ok()?"OK":"ERROR",") @ ",this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("pointer_ = ",pointer_,pointer_==utils::POISON_PTR?" (POISON)":"",pointer_!= nullptr&&pointer_!=utils::POISON_PTR?" :":"");
    if(pointer_!= nullptr&&pointer_!=utils::POISON_PTR)
        pointer_->dump (ostream);
    --ostream;
    ostream.println ('}');
}

template <typename T>
void shared_ptr<T>::dump (utils::ostream &&ostream) const
{
    dump (ostream);
}

template <typename T>
shared_ptr<T>::shared_ptr (T *t):pointer_(nullptr)
{
    try
    {
        pointer_=new proxy_ptr(t);
    }
    catch (std::bad_alloc)
    {
        pointer_= nullptr;
    }
    INFO(*this);
}

template <typename T>
shared_ptr<T>::shared_ptr (const shared_ptr &that)
{
    pointer_=that.pointer_;
    if(pointer_!= nullptr)
        pointer_->link ();
    INFO(*this);
}

template <typename T>
const shared_ptr<T> &shared_ptr<T>::operator= (const shared_ptr &that)
{
    INFO(*this);
    release ();
    pointer_=that.pointer_;
    if(pointer_!= nullptr)
        pointer_->link ();
    INFO(*this);
    return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr ()
{
    release ();
    pointer_=(proxy_ptr*)utils::POISON_PTR;
}

#endif //HOMEWORK_3_SHARED_PTR_H

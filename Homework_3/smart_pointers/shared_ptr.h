//---------------------------------------
//! @file shared_ptr.h
//! Definition of the shared_ptr class
//---------------------------------------

#ifndef HOMEWORK_3_SHARED_PTR_H
#define HOMEWORK_3_SHARED_PTR_H

#include "unique_ptr.h"

//---------------------------------------
//! @class shared_ptr is an implementation of the shared smart pointer
//---------------------------------------

template<typename T>
class shared_ptr : public smart_pointer<T>
{

//---------------------------------------
//! @class proxy_ptr is an implementation of the proxy used in the shared pointer
//---------------------------------------

    class proxy_ptr : public unique_ptr<T>
    {
        int links;
    public:

//---------------------------------------
//! @brief Increments the anount of links by one
//---------------------------------------

        void link ();

//---------------------------------------
//! @brief Decrements the anount of links by one
//! @returns true if there are no more links
//---------------------------------------

        bool dislink ();

//---------------------------------------
//! @brief Checks if there are any links to the object
//! @returns true if there is at least one object that references this object
//---------------------------------------

        bool linked ();

//---------------------------------------
//! @brief Silent verifier
//! @returns True if no errors has occurred
//---------------------------------------

        virtual bool ok () const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the result into
//---------------------------------------

        virtual void dump (utils::ostream &) const;

//---------------------------------------
//! @brief Dumper for rvalues
//! @param out A rvalue stream to output the result into
//---------------------------------------

        virtual void dump (utils::ostream &&) const;

//---------------------------------------
//! @brief Constructor
//! @param ptr A pointer to be stored
//---------------------------------------

        proxy_ptr (T *ptr = nullptr);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

        virtual ~proxy_ptr ();
    };

    proxy_ptr *pointer_;

public:

//---------------------------------------
//! @brief Constructor
//! @param t A pointer to be stored
//---------------------------------------

    shared_ptr (T *t = nullptr);

//---------------------------------------
//! @brief Copy constructor
//! @param that A value to be copied to the object
//---------------------------------------

    shared_ptr (const shared_ptr &that);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    virtual ~shared_ptr ();

//---------------------------------------
//! @brief Returns the stored pointer
//! @returns The stored pointer
//---------------------------------------

    virtual T *get () const;

//---------------------------------------
//! @brief Returns the pointed object
//! @returns The pointed object
//---------------------------------------

    virtual T &operator* () const;

//---------------------------------------
//! @brief Returns the stored pointer that makes it possible to use the -> operator of the stored class
//! @returns The stored pointer
//---------------------------------------

    virtual T *operator-> () const;

//---------------------------------------
//! @brief Assignment operator
//! @param ptr Pointer to store
//! @returns Copied stored pointer
//---------------------------------------

    virtual T *operator= (T *t);

//---------------------------------------
//! @brief Assignation operator
//! @param that A value to be assigned to the object
//! @note This operator copies he pointer to the proxy and links the proxy to a new object
//---------------------------------------

    const shared_ptr &operator= (const shared_ptr &that);

//---------------------------------------
//! @brief Assignation operator for rvalue
//! @param that An rvalue to be assigned to the object
//---------------------------------------

    const shared_ptr &operator= (shared_ptr &&that);

//---------------------------------------
//! @brief Type cast to boolean
//! @returns True if the pointer is assigned
//---------------------------------------

    virtual operator bool () const;

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

    virtual void reset (T *t);

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

    virtual void swap (shared_ptr &that);
};

template<typename T>
void shared_ptr<T>::proxy_ptr::link ()
{
    INFO(*this);
    links++;
    INFO(*this);
}

template<typename T>
bool shared_ptr<T>::proxy_ptr::dislink ()
{
    INFO(*this);
    --links;
    INFO(*this);
    return links == 0;
}

template<typename T>
bool shared_ptr<T>::proxy_ptr::linked ()
{
    INFO(*this);
    return links > 0;
}

template<typename T>
bool shared_ptr<T>::proxy_ptr::ok () const
{
    return unique_ptr<T>::ok () && links != utils::POISON_INT;
}

template<typename T>
void shared_ptr<T>::proxy_ptr::dump (utils::ostream &ostream) const
{
    ostream.println ("proxy_ptr (", ok () ? "OK" : "ERROR", ") @ ", this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("links = ", links, links == utils::POISON_INT ? " (POISON)" : "");
    unique_ptr<T>::dump (ostream);
    --ostream;
    ostream.println ('}');
}

template<typename T>
void shared_ptr<T>::proxy_ptr::dump (utils::ostream &&ostream) const
{
    dump (ostream);
}

template<typename T>
shared_ptr<T>::proxy_ptr::proxy_ptr (T *ptr) : unique_ptr<T> (ptr), links (1)
{
    INFO(*this);
}

template<typename T>
shared_ptr<T>::proxy_ptr::~proxy_ptr ()
{
    INFO(*this);
    links = utils::POISON_INT;
}

template<typename T>
T *shared_ptr<T>::get () const
{
    INFO(*this);
    if (pointer_ != nullptr)
        return pointer_->get ();
    return nullptr;
}

template<typename T>
T &shared_ptr<T>::operator* () const
{
    INFO(*this);
    if (pointer_ != nullptr)
        return pointer_->operator* ();
    throw "Pointer is empty";
}

template<typename T>
T *shared_ptr<T>::operator-> () const
{
    INFO(*this);
    if (pointer_ != nullptr)
        return pointer_->operator-> ();
    return nullptr;
}

template<typename T>
T *shared_ptr<T>::operator= (T *t)
{
    INFO(*this);
    if (pointer_ == nullptr)
        pointer_ = new proxy_ptr ();
    pointer_->reset (t);
    INFO(*this);
    return t;
}

template<typename T>
shared_ptr<T>::operator bool () const
{
    INFO(*this);
    if (pointer_ != nullptr)
        return (bool) pointer_;
    return false;
}

template<typename T>
T *shared_ptr<T>::release ()
{
    INFO(*this);
    if (pointer_ == nullptr)
        return nullptr;
    T *ret = pointer_->get ();
    if (pointer_->dislink ()) delete pointer_;
    pointer_ = nullptr;
    INFO(*this);
    return ret;
}

template<typename T>
void shared_ptr<T>::reset (T *t)
{
    INFO(*this);
    if (pointer_ != nullptr && pointer_->dislink ()) delete pointer_;
    pointer_ = new proxy_ptr (t);
    INFO(*this);
}

template<typename T>
bool shared_ptr<T>::ok () const
{
    if (pointer_ == utils::POISON_PTR)
        return false;
    return pointer_ == nullptr || pointer_->ok ();
}

template<typename T>
void shared_ptr<T>::dump (utils::ostream &ostream) const
{
    ostream.println ("shared_ptr (", ok () ? "OK" : "ERROR", ") @ ", this);
    ostream.println ('{');
    ++ostream;
    ostream.println ("pointer_ = ", pointer_, pointer_ == utils::POISON_PTR ? " (POISON)" : "",
                     pointer_ != nullptr && pointer_ != utils::POISON_PTR ? " :" : "");
    if (pointer_ != nullptr && pointer_ != utils::POISON_PTR)
        pointer_->dump (ostream);
    --ostream;
    ostream.println ('}');
}

template<typename T>
void shared_ptr<T>::dump (utils::ostream &&ostream) const
{
    dump (ostream);
}

template<typename T>
shared_ptr<T>::shared_ptr (T *t):pointer_ (nullptr)
{
    if (t == nullptr)
        pointer_ = nullptr;
    else
        try {
            pointer_ = new proxy_ptr (t);
        }
        catch (std::bad_alloc) {
            pointer_ = nullptr;
        }
    INFO(*this);
}

template<typename T>
shared_ptr<T>::shared_ptr (const shared_ptr &that)
{
    pointer_ = that.pointer_;
    if (pointer_ != nullptr)
        pointer_->link ();
    INFO(*this);
}

template<typename T>
const shared_ptr<T> &shared_ptr<T>::operator= (const shared_ptr &that)
{
    INFO(*this);
    shared_ptr<T> buf (that);
    swap (buf);
    INFO(*this);
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr ()
{
    INFO(*this);
    release ();
    INFO(*this);
    pointer_ = (proxy_ptr *) utils::POISON_PTR;
}

template<typename T>
const shared_ptr<T> &shared_ptr<T>::operator= (shared_ptr<T> &&that)
{
    INFO (*this);
    swap (that);
    INFO (*this);
    return *this;
}

template<typename T>
void shared_ptr<T>::swap (shared_ptr<T> &that)
{
    INFO(*this);
    proxy_ptr *buf = pointer_;
    pointer_ = that.pointer_;
    that.pointer_ = buf;
    INFO(*this);
}

#endif //HOMEWORK_3_SHARED_PTR_H

//---------------------------------------
//! @file ArrayPointerBool.h
//! Partial bool specification for the smart pointer
//---------------------------------------

#ifndef VECTOR_VECTORPOINTERBOOL_H
#define VECTOR_VECTORPOINTERBOOL_H

#include <cstring>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "bit_pointer.h"

template<>
class VectorPointer<bool>
{
private:
    char *data_;
    size_t capacity_;
    size_t size_;
    size_t links_;

    static size_t bits_to_bytes (size_t n_bits);

public:

//---------------------------------------
//! @brief Decrements the links counter by one
//! @return True if there are no more links
//---------------------------------------

    bool dislink ();

//---------------------------------------
//! @brief Increments the links counter by one
//---------------------------------------

    void link ();

//---------------------------------------
//! @brief Silent verifier
//! @return True if object is OK
//---------------------------------------

    bool ok () const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the info into
//! @param displacement A length of the padding
//---------------------------------------

    void dump (std::ostream &out, size_t displacement = 0) const;

//---------------------------------------
//! @brief A value that is used to determine destructed objects
//---------------------------------------

    const uint32_t POISON = UINT32_MAX;

    //---------------------------------------
//! @brief Constructor
//! @param capacity Maximum amount of elements in the storage
//---------------------------------------

    explicit VectorPointer (size_t capacity);

//---------------------------------------
//! @brief Copy constructor
//! @param that An object to copy
//---------------------------------------

    VectorPointer (VectorPointer<bool> &);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    ~VectorPointer ();

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use At() instead
//---------------------------------------

    bit_pointer operator[] (const size_t);

//---------------------------------------
//! @brief Gives access to the requested element from the vector
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    bit_pointer at (const size_t);

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    size_t capacity () const;

//---------------------------------------
//! @brief Returns the size of the object
//! @return The size of the object
//---------------------------------------

    size_t size () const;

//---------------------------------------
//! @brief Change capacity and size of obj
//! @throws std::bad_alloc
//! @param n new size of vector
//---------------------------------------

    void resize (size_t);

//---------------------------------------
//! @brief Change capacity of obj
//! @throws std::bad_alloc
//! @param n new capacity of vector
//---------------------------------------

    void reserve (size_t);

//---------------------------------------
//! @brief Change capacity to size of vector
//---------------------------------------

    void shrink_to_fit ();

//---------------------------------------
//! @brief Push the value to vector tail
//! @throws std::bad_alloc
//! @param elem element pushing to vector
//---------------------------------------

    void push_back (bool);

//---------------------------------------
//! @brief Pop the value from vector tail
//! @throws std::out_of_range
//! @param elem element pushing to vector
//! @return None
//---------------------------------------
    void pop_back ();
};

void VectorPointer<bool>::link ()
{
    INFO(*this);
    links_++;
    LOG("bool add link" + std::to_string (links_));
    INFO(*this);
}

bool VectorPointer<bool>::dislink ()
{
    INFO(*this);
    LOG("bool rem link" + std::to_string (links_ - 1));
    INFO(*this);
    return !(--links_);
}

size_t VectorPointer<bool>::capacity () const
{
    INFO(*this);
    return capacity_ * 8;
}

VectorPointer<bool>::VectorPointer (size_t capacity) : data_ (nullptr), capacity_ (bits_to_bytes (capacity)), size_ (0),
                                                       links_ (1)
{
    if (capacity == 0) return;
    try {
        data_ = new char[capacity_];
    }
    catch (std::bad_alloc e) {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

VectorPointer<bool>::VectorPointer (VectorPointer<bool> &vector_pointer) : capacity_ (vector_pointer.capacity_),
                                                                           size_ (vector_pointer.size_), links_ (1)
{
    if (capacity_ == 0) return;
    try {
        data_ = new char[capacity_];
        for (size_t i = 0; i < bits_to_bytes (size_); i++)
            data_[i] = vector_pointer.data_[i];
    }
    catch (std::bad_alloc e) {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

bit_pointer VectorPointer<bool>::operator[] (const size_t index)
{
    INFO(*this);
    return bit_pointer (data_ + index / 8, index % 8);
}

bit_pointer VectorPointer<bool>::at (const size_t index)
{
    INFO(*this);
    if (index < size_) {
        return operator[] (index);
    }
    INFO(*this);
    throw std::out_of_range ("bad value");
}

VectorPointer<bool>::~VectorPointer ()
{
    INFO(*this);
    delete[] data_;
    LOG("bool free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

bool VectorPointer<bool>::ok () const
{
    return (links_ != POISON) && (capacity_ != POISON);
}

void VectorPointer<bool>::dump (std::ostream &out, size_t displacement) const
{
    char *tabs = utils::getPadding ('\t', displacement);

    out << tabs << "VectorPointer(" << (ok () ? "OK" : "ERROR") << ") @ " << (void *) this << '\n';
    out << tabs << "{\n";
    out << tabs << "\tcapacity: " << capacity_ << (capacity_ == POISON ? " (POISON)" : "") << '\n';
    out << tabs << "\tlinks: " << links_ << (links_ == POISON ? " (POISON)" : "") << '\n';
    out << tabs << "\tdata @ " << (void *) data_ << " :\n";
    out << tabs << "\t{\n";

    for (int index = 0; index < capacity_ * 8; index++) {
        bool b = (data_[index / 8] & utils::access[index % 8]);
        out << tabs << "\t\tdata_[" << index << "] = ";
        out << b << '\n';
    }

    out << tabs << "\t}\n";
    out << tabs << "}\n";

    delete[] tabs;
}

size_t VectorPointer<bool>::size () const
{
    INFO(*this);
    return size_;
}

void VectorPointer<bool>::resize (size_t n)
{
    INFO(*this);
    reserve (n);
    size_ = n;
    INFO(*this);
}

void VectorPointer<bool>::reserve (size_t n)
{
    INFO(*this);
    if (n > capacity_ * 8) {
        char *dat = new char[bits_to_bytes (n)];
        for (size_t i = 0; i < bits_to_bytes (size_); i++)
            dat[i] = data_[i];
        delete[] data_;
        data_ = dat;
        capacity_ = bits_to_bytes (n);
    }
    INFO(*this);
}

void VectorPointer<bool>::shrink_to_fit ()
{
    if (bits_to_bytes (size_) < capacity_) {
        char *dat = new char[bits_to_bytes (size_)];
        for (size_t i = 0; i < bits_to_bytes (size_); i++)
            dat[i] = data_[i];
        delete[] data_;
        data_ = dat;
        capacity_ = bits_to_bytes (size_);
    }
}

void VectorPointer<bool>::push_back (bool elem)
{
    if (size_ == capacity_ * 8)
        reserve (capacity_ + 4);
    (*this)[size_++] = elem;
}


void VectorPointer<bool>::pop_back ()
{
    --size_;
}

size_t VectorPointer<bool>::bits_to_bytes (size_t n_bits)
{
    size_t n_bytes = n_bits / 8;
    if (n_bits % 8 > 0)
        ++n_bytes;
    return n_bytes;
}

#endif //VECTOR_VECTORPOINTERBOOL_H

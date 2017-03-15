//---------------------------------------
//! @file ArrayPointer.h
//! Implementation of a smart pointer
//---------------------------------------

#ifndef ARRAY_ARRAYPOINTER_H
#define ARRAY_ARRAYPOINTER_H

#include <cstring>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include "Utils.h"

template <typename T>
class ArrayPointer
{
private:
    T * data_;
    size_t capacity_;
    size_t links_;
public:

//---------------------------------------
//! @brief Decrements the links counter by one
//! @return True if there are no more links
//---------------------------------------

    bool dislink();

//---------------------------------------
//! @brief Increments the links counter by one
//---------------------------------------

    void link();

//---------------------------------------
//! @brief Silent verifier
//! @return True if object is OK
//---------------------------------------

    bool ok() const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the info into
//! @param displacement A length of the padding
//---------------------------------------

    void dump(std::ostream& out,size_t displacement = 0) const;

//---------------------------------------
//! @brief A value that is used to determine destructed objects
//---------------------------------------

    const uint32_t POISON = UINT32_MAX;

//---------------------------------------
//! @brief Constructor
//! @param capacity Maximum amount of elements in the storage
//---------------------------------------

    explicit ArrayPointer(size_t capacity);

//---------------------------------------
//! @brief Copy constructor
//! @param that An object to copy
//---------------------------------------

    ArrayPointer(const ArrayPointer<T>& that);

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    ~ArrayPointer();

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//! @note This method is unsafe, it's highly suggested to use At() instead
//---------------------------------------

    T& operator[](const size_t);

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    T& At(const size_t);

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    size_t capacity() const;
};



template <typename T>
ArrayPointer<T>::ArrayPointer(size_t capacity):data_(nullptr), capacity_(capacity), links_(1)
{
    if (capacity_ == 0) return;
    try
    {
        data_ = new T[capacity];
    }
    catch(std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

template <typename T>
ArrayPointer<T>::ArrayPointer(const ArrayPointer<T> & array_pointer):capacity_(array_pointer.capacity_), links_(1)
{
    try
    {
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

template <typename T>
ArrayPointer<T>::~ArrayPointer()
{
    INFO(*this);
    delete[] data_;
    LOG("free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

template <typename T>
T& ArrayPointer<T>::operator[](const size_t index)
{
    INFO(*this);
    return data_[index];
}

template <typename T>
T& ArrayPointer<T>::At(const size_t index)
{
    INFO(*this);
    if (index<capacity_) return data_[index];
    throw std::out_of_range("bad value");
}

template <typename T>
bool ArrayPointer<T>::ok() const
{
    return (links_ != POISON) && (capacity_ != POISON);
}

template <typename T>
void ArrayPointer<T>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"ArrayPointer("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcapacity: "<<capacity_<<(capacity_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tlinks: "<<links_<<(links_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tdata @ "<<(void*)data_<<" :\n";
    out<<tabs<<"\t{\n";

    for(int i = 0;i<capacity_;i++){
        const int*casted = reinterpret_cast<const int*>(&data_[i]);
        out<<tabs<<"\t\tdata_["<<i<<"] = 0x";
        for(int j = 0;j<((double)sizeof(T))/4;j++)
            out<<std::setw(sizeof(T)*2<8?sizeof(T)*2:8)<<std::setfill('0')<<std::hex<<(casted[j]%(int)pow(2,8*sizeof(T)))<<std::dec;
        out<<'\n';
    }

    out<<tabs<<"\t}\n";
    out<<tabs<<"}\n";

    delete [] tabs;
}

template <typename T>
void ArrayPointer<T>::link()
{
    INFO(*this);
    links_++;
    LOG("add link"+std::to_string(links_));
    INFO(*this);
}

template <typename T>
bool ArrayPointer<T>::dislink()
{
    INFO(*this);
    LOG("rem link"+std::to_string(links_-1));
    INFO(*this);
    return !(--links_);
}

template <typename T>
size_t ArrayPointer<T>::capacity() const
{
    INFO(*this);
    return capacity_;
}

#endif //ARRAY_ARRAYPOINTER_H

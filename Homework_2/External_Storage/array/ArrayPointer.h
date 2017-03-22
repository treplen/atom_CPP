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
    size_t size_;
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

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    size_t size() const;

//---------------------------------------
//! @brief Change capacity and size of obj
//! @throws std::bad_alloc
//! @param n new size of array
//---------------------------------------

    void resize(size_t );

//---------------------------------------
//! @brief Change capacity of obj
//! @throws std::bad_alloc
//! @param n new capacity of array
//---------------------------------------

    void reserve(size_t );

//---------------------------------------
//! @brief Change capacity to size of array
//---------------------------------------

    void shrink_to_fit();

//---------------------------------------
//! @brief Push the value to array tail
//! @throws std::bad_alloc
//! @param elem element pushing to array
//---------------------------------------

    void push_back(T & );

//---------------------------------------
//! @brief Pop the value from array tail
//! @throws std::out_of_range
//---------------------------------------

    void pop_back();

};



template <typename T>
ArrayPointer<T>::ArrayPointer(size_t capacity):data_(nullptr), capacity_(capacity), size_(capacity), links_(1)
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
        size_ = 0;
    }
    INFO(*this);
}

template <typename T>
ArrayPointer<T>::ArrayPointer(const ArrayPointer<T> & array_pointer):capacity_(array_pointer.size_), size_(array_pointer.size_), links_(1)
{
    try
    {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
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
    size_ = POISON;
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
    if (index < capacity_ && index < size_)
    {
        return data_[index];
    }
    throw std::out_of_range("bad value");
}

template <typename T>
bool ArrayPointer<T>::ok() const
{
    return (links_ != POISON) && (capacity_ != POISON) && (size_<=capacity_);
}

template <typename T>
void ArrayPointer<T>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"ArrayPointer("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcapacity: "<<capacity_<<(capacity_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tsize: "<<size_<<(size_==POISON?" (POISON)":"")<<'\n';
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

template <typename T>
size_t ArrayPointer<T>::size() const
{
    INFO(*this);
    return size_;
}

template <typename T>
void ArrayPointer<T>::resize(size_t n) {
    INFO(*this);
    if(n>capacity_)
    {
        T *dat = new T[n];
        for (size_t i = 0; i < size_; i++)
            dat[i] = data_[i];
        delete[] data_;
        data_ = dat;
        capacity_ = n;
    }
    size_ = n;
    INFO(*this);
}

template <typename T>
void ArrayPointer<T>::push_back(T & elem)
{
    if (size_ == capacity_)
        resize(capacity_ == 0 ? 1 : capacity_ * 2);
    data_[size_++] = elem;
}

template <typename T>
void ArrayPointer<T>::pop_back()
{
    if(size_>0)
        --size_;
    else
        throw std::out_of_range("Size is zero");
}

template <typename T>
void ArrayPointer<T>::reserve(size_t n)
{
    if(n>capacity_)
    {
        T *dat = new T[n];
        for (size_t i = 0; i < size_; i++)
            dat[i] = data_[i];
        delete[] data_;
        data_ = dat;
        capacity_ = n;
    }
}

template <typename T>
void ArrayPointer<T>::shrink_to_fit()
{
    T *dat = new T[size_];
    for (size_t i = 0; i < size_; i++)
        dat[i] = data_[i];
    delete[] data_;
    data_ = dat;
    capacity_ = size_;
}


#endif //ARRAY_ARRAYPOINTER_H

//---------------------------------------
//! @file ArrayPointerBool.h
//! Partial bool specification for the smart pointer
//---------------------------------------

#ifndef ARRAY_ARRAYPOINTERBOOL_H
#define ARRAY_ARRAYPOINTERBOOL_H

#include <cstring>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include "Utils.h"

template <>
class ArrayPointer<bool>
{
private:
    int access[8] = {0b00000001, 0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
    char * data_;
    size_t capacity_;
    size_t size_;
    size_t links_;
    bool helper_; //i'm useless here...
    bool & ret_val_;
    int index_;
    void _upd();
    inline size_t _capacity();
    inline size_t _size();
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

    ArrayPointer(ArrayPointer<bool>&);

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

    bool& operator[](const size_t);

//---------------------------------------
//! @brief Gives access to the requested element from the array
//! @param position Position of the element
//! @return The requested element
//---------------------------------------

    bool& At(const size_t);

//---------------------------------------
//! @brief Returns the capacity of the object
//! @return The capacity of the object
//---------------------------------------

    size_t capacity() const;

//---------------------------------------
//! @brief Returns the size of the object
//! @return The size of the object
//---------------------------------------

    size_t size() const;

//---------------------------------------
//! @brief Change capacity and size of obj
//! @throws std::bad_alloc
//! @param n new capacity of array
//! @return None
//---------------------------------------

    void resize(size_t );

//---------------------------------------
//! @brief Push the value to array tail
//! @throws std::bad_alloc
//! @param elem element pushing to array
//! @return None
//---------------------------------------

    void push_back(bool );

//---------------------------------------
//! @brief Pop the value from array tail
//! @throws std::out_of_range
//! @param elem element pushing to array
//! @return None
//---------------------------------------
    const bool pop_back();
};


void ArrayPointer<bool>::link()
{
    INFO(*this);
    links_++;
    LOG("bool add link"+std::to_string(links_));
    INFO(*this);
}

bool ArrayPointer<bool>::dislink()
{
    INFO(*this);
    LOG("bool rem link"+std::to_string(links_-1));
    INFO(*this);
    return !(--links_);
}

size_t ArrayPointer<bool>::capacity() const
{
    INFO(*this);
    return capacity_;
}
size_t ArrayPointer<bool>::_capacity() {
    return (int)ceil(1. * capacity_ / 8);
}

ArrayPointer<bool>::ArrayPointer(size_t capacity): data_(nullptr), capacity_(capacity),size_(capacity), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    if (capacity == 0) return;
    try
    {
        data_ = new char[_capacity()];
    }
    catch(std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

ArrayPointer<bool>::ArrayPointer(ArrayPointer<bool> & array_pointer):capacity_(array_pointer.size_), size_(array_pointer.size_), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    array_pointer._upd();
    try
    {
        int cap = _capacity();
        data_ = new char[cap];
        for (size_t i = 0; i < cap; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

void ArrayPointer<bool>::_upd()
{
    INFO(*this);
    int i = index_ / 8;
    int j = index_ % 8;
    data_ [i] &= ~access[j];
    if (ret_val_) data_ [i] |=access[j];
    INFO(*this);
}

bool& ArrayPointer<bool>::operator[](const size_t index)
{
    INFO(*this);
    _upd();

    index_=index;
    int i = index / 8;
    int j = index % 8;
    char c = data_ [i];
    ret_val_ =(c & access[j]) ? 1:0;
    INFO(*this);
    return ret_val_;
}

bool& ArrayPointer<bool>::At(const size_t index)
{
    INFO(*this);
    _upd();
    if (index<capacity_){
        index_=index;
        int i = index / 8;
        int j = index % 8;
        char c = data_ [i];
        ret_val_ =(c & access[j]) ? 1 : 0;
        INFO(*this);
        return ret_val_;
    }
    INFO(*this);
    throw std::out_of_range("bad value");
}

ArrayPointer<bool>::~ArrayPointer()
{
    INFO(*this);
    delete[] data_;
    LOG("bool free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

bool ArrayPointer<bool>::ok() const
{
    return (links_ != POISON) && (capacity_ != POISON);
}

void ArrayPointer<bool>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"ArrayPointer("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcapacity: "<<capacity_<<(capacity_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tlinks: "<<links_<<(links_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tdata @ "<<(void*)data_<<" :\n";
    out<<tabs<<"\t{\n";

    for(int index = 0;index<capacity_;index++){
        int i = index / 8;
        int j = index % 8;
        char c = data_ [i];
        bool b = (c & access[j]) ? 1:0;
        out<<tabs<<"\t\tdata_["<<index<<"] = ";
        out<< b <<'\n';
    }

    out<<tabs<<"\t}\n";
    out<<tabs<<"}\n";

    delete [] tabs;
}

size_t ArrayPointer<bool>::size() const
{
    INFO(*this);
    return size_;
}

void ArrayPointer<bool>::resize(size_t n) {
    INFO(*this);
    capacity_ = n;
    size_ = std::min(capacity_, size_);
    char* dat = new char[_capacity()];
    for (size_t i = 0; i < _size(); i++)
        dat[i] = data_[i];
    delete[] data_;
    data_ = dat;
    INFO(*this);
}

void ArrayPointer<bool>::push_back(bool elem)
{
    if (size_ == capacity_)
        resize(capacity_ * 8);
    data_[size_++] = elem;
}


const bool ArrayPointer<bool>::pop_back()
{
    return  At(--size_);
}

size_t ArrayPointer<bool>::_size() {
    return (int)ceil(1. * size_ / 8);
}


#endif //ARRAY_ARRAYPOINTERBOOL_H

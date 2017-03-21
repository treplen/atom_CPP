//---------------------------------------
//! @file Iterator.h
//! Implementation of the array iterator
//---------------------------------------

#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "Collection.h"

template<typename T>
class Iterator
{
private:
    Collection<T> *c_;
    size_t index_;
public:

//---------------------------------------
//! @brief Constructor
//! @param col A pointer to the iterated collection
//---------------------------------------

    Iterator(Collection<T> *col):c_(col)
    {INFO(*this);}

//---------------------------------------
//! @brief Constructor
//! @param col A pointer to the iterated collection
//! @param index The index of the pointed element
//---------------------------------------

    Iterator(Collection<T>* col, size_t index):c_(col), index_(index)
    {INFO(*this);}

//---------------------------------------
//! @brief Moves the iterator to the beginning of the storage
//! @return A reference to the iterator
//---------------------------------------

    Iterator<T>& SetBegin()
    {
        INFO(*this);
        index_ = 0;
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Moves the iterator to the end of the storage
//! @return A reference to the iterator
//---------------------------------------

    Iterator<T>& SetEnd()
    {
        INFO(*this);
        index_ = c_->capacity();
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if iterators are equal
//---------------------------------------

    bool operator==(const Iterator<T>& it)const
    {
        INFO(*this);
        return it.index_ == index_ && c_==it.c_;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if iterators are not equal
//---------------------------------------

    bool operator!=(const Iterator<T>& it)const
    {
        INFO(*this);
        return it.index_ != index_ || c_!=it.c_;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if this object is lower
//---------------------------------------

    bool operator<(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ < it.index_ && c_==it.c_;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if this object is greater
//---------------------------------------

    bool operator>(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ > it.index_ && c_==it.c_;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if this object is lower or iterators are equal
//---------------------------------------

    bool operator<=(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ <= it.index_ && c_==it.c_;
    }

//---------------------------------------
//! @brief Compares two iterators
//! @param it An object to compare with
//! @return True if this object is greater or iterators are equal
//---------------------------------------

    bool operator>=(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ >= it.index_ && c_==it.c_;
    }

//---------------------------------------
//! @brief Imcrements the iterator by one
//! @return A reference to the incremented iterator
//---------------------------------------

    Iterator<T>& operator++()
    {
        INFO(*this);
        index_++;
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Decrements the iterator by one
//! @return A reference to the decremented iterator
//---------------------------------------

    Iterator<T>& operator--()
    {
        INFO(*this);
        index_--;
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Gives acces to the current object
//! @return A reference to an object that is currently pointed by the iterator
//---------------------------------------

    T& operator*() const
    {
        INFO(*this);
        return (*c_)[index_];
    }

//---------------------------------------
//! @brief Increments the iterator by the specified value
//! @param value A value to increment the iterator with
//! @return The incremented iterator
//---------------------------------------

    Iterator<T> operator+(int value) const
    {
        INFO(*this);
        return Iterator<T>(c_, index_+value);
    }

//---------------------------------------
//! @brief Decrements the iterator by the specified value
//! @param value A value to decrement the iterator with
//! @return The decremented iterator
//---------------------------------------

    Iterator<T> operator-(int value) const
    {
        INFO(*this);
        return Iterator<T>(c_, index_-value);
    }

//---------------------------------------
//! @brief Increments the iterator by the specified value
//! @param value A value to increment the iterator with
//! @return A reference to the iterator
//---------------------------------------

    Iterator<T>& operator+=(int value)
    {
        INFO(*this);
        index_+=value;
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Decrements the iterator by the specified value
//! @param value A value to decrement the iterator with
//! @return A reference to the iterator
//---------------------------------------

    Iterator<T>& operator-=(int value)
    {
        INFO(*this);
        index_-=value;
        INFO(*this);
        return *this;
    }

//---------------------------------------
//! @brief Silent verifier
//! @return True if object is OK
//---------------------------------------

    bool ok() const
    {
        return c_!= nullptr;
    }

//---------------------------------------
//! @brief Dumper
//! @param out A stream to output the info into
//! @param displacement A length of the padding
//---------------------------------------

    void dump(std::ostream& out,size_t displacement = 0) const
    {
        char* tabs = utils::getPadding('\t',displacement);

        out << tabs << "Iterator(" << (ok() ? "OK" : "ERROR")<<") @ "<<(void*)this<<'\n';
        out<<tabs<<"{\n";
        out<<tabs<<"\tData address: "<<(void*)c_<<'\n';
        out<<tabs<<"\tIndex: "<<index_<<'\n';
        out<<tabs<<"}\n";

        delete[] tabs;
    }

};

#endif //ARRAY_ITERATOR_H

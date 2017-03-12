//
// Created by sl on 11.03.17.
//
#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "Collection.h"

template<typename T>
class Iterator
{
public:
    Iterator(Collection<T> *col):c_(col)
    {}
    Iterator(Collection<T>* col, int index):c_(col), index_(index)
    {}

    Iterator<T>& GetBegin()
    {
        index_ = 0;
        return *this;
    }

    Iterator<T>& GetEnd()
    {
        index_ = c_->capacity();
        return *this;
    }

    bool operator==(Iterator<T>& it)const
    {
        return it.index_ == index_;
    }

    bool operator!=(Iterator<T>& it)const
    {
        return it.index_ != index_;
    }

    bool operator<(Iterator<T>& it)const
    {
        return index_ < it.index_;
    }

    bool operator>(Iterator<T>& it)const
    {
        return index_ > it.index_;
    }


    bool operator<=(Iterator<T>& it)const
    {
        return index_ <= it.index_;
    }

    bool operator>=(Iterator<T>& it)const
    {
        return index_ >= it.index_;
    }

    Iterator<T>& operator++()
    {
        index_++;
        return *this;
    }

    Iterator<T>& operator--()
    {
        index_--;
        return *this;
    }

    T& operator*() const
    {
        return (*c_)[index_];
    }

    Iterator<T>& operator+(int value) const
    {
        return Iterator<T>(c_, index_+value);
    }

    Iterator<T>& operator-(int value) const
    {
        return Iterator<T>(c_, index_-value);
    }

    Iterator<T>& operator+=(int value)
    {
        index_+=value;
        return *this;
    }

    T& operator-=(int value) const
    {
        index_+=value;
        return *this;
    }


private:
    Collection<T> *c_;
    int index_;
};


#endif //ARRAY_ITERATOR_H

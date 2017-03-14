//
// Created by sl on 11.03.17.
//
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
    Iterator(Collection<T> *col):c_(col)
    {}
    Iterator(Collection<T>* col, size_t index):c_(col), index_(index)
    {}

    Iterator<T>& SetBegin()
    {
        index_ = 0;
        return *this;
    }

    Iterator<T>& SetEnd()
    {
        index_ = c_->capacity();
        return *this;
    }

    bool operator==(const Iterator<T>& it)const
    {
        return it.index_ == index_;
    }

    bool operator!=(const Iterator<T>& it)const
    {
        return it.index_ != index_;
    }

    bool operator<(const Iterator<T>& it)const
    {
        return index_ < it.index_;
    }

    bool operator>(const Iterator<T>& it)const
    {
        return index_ > it.index_;
    }


    bool operator<=(const Iterator<T>& it)const
    {
        return index_ <= it.index_;
    }

    bool operator>=(const Iterator<T>& it)const
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

    Iterator<T> operator+(int value) const
    {
        return Iterator<T>(c_, index_+value);
    }

    Iterator<T> operator-(int value) const
    {
        return Iterator<T>(c_, index_-value);
    }

    Iterator<T>& operator+=(int value)
    {
        index_+=value;
        return *this;
    }

    Iterator<T>& operator-=(int value)
    {
        index_-=value;
        return *this;
    }
    bool ok() const
    {
        return c_!= nullptr && index_ >=0 && index_ < c_->capacity();
    }

    void dump(std::ostream& out,size_t displacement = 0) const
    {
        char* tabs;
        tabs = new char[displacement+1];
        for(int i = 0;i<displacement;i++) tabs[i]='\t';
        tabs[displacement]=0;

        out << tabs << "Iterator(" << (ok() ? "OK" : "ERROR")<<") @ "<<(void*)this<<'\n';
        out<<tabs<<'{';
        out<<tabs<<"\tData address: "<<(void*)c_<<'\n';
        out<<tabs<<"\tIndex: "<<index_<<'\n';
        out<<tabs<<"}\n";

        delete[] tabs;
    }

};


#endif //ARRAY_ITERATOR_H

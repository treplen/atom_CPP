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
    {INFO(*this);}
    Iterator(Collection<T>* col, size_t index):c_(col), index_(index)
    {INFO(*this);}

    Iterator<T>& SetBegin()
    {
        INFO(*this);
        index_ = 0;
        INFO(*this);
        return *this;
    }

    Iterator<T>& SetEnd()
    {
        INFO(*this);
        index_ = c_->capacity();
        INFO(*this);
        return *this;
    }

    bool operator==(const Iterator<T>& it)const
    {
        INFO(*this);
        return it.index_ == index_;
    }

    bool operator!=(const Iterator<T>& it)const
    {
        INFO(*this);
        return it.index_ != index_;
    }

    bool operator<(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ < it.index_;
    }

    bool operator>(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ > it.index_;
    }


    bool operator<=(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ <= it.index_;
    }

    bool operator>=(const Iterator<T>& it)const
    {
        INFO(*this);
        return index_ >= it.index_;
    }

    Iterator<T>& operator++()
    {
        INFO(*this);
        index_++;
        INFO(*this);
        return *this;
    }

    Iterator<T>& operator--()
    {
        INFO(*this);
        index_--;
        INFO(*this);
        return *this;
    }

    T& operator*() const
    {
        INFO(*this);
        return (*c_)[index_];
    }

    Iterator<T> operator+(int value) const
    {
        INFO(*this);
        return Iterator<T>(c_, index_+value);
    }

    Iterator<T> operator-(int value) const
    {
        INFO(*this);
        return Iterator<T>(c_, index_-value);
    }

    Iterator<T>& operator+=(int value)
    {
        INFO(*this);
        index_+=value;
        INFO(*this);
        return *this;
    }

    Iterator<T>& operator-=(int value)
    {
        INFO(*this);
        index_-=value;
        INFO(*this);
        return *this;
    }
    bool ok() const
    {
        return c_!= nullptr;
    }

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

//
// Created by sl on 12.03.17.
//

#ifndef ARRAY_COLLECTION_H
#define ARRAY_COLLECTION_H

#include <cstring>

template <typename T>
class Collection
{
public:
    virtual ~Collection(){} ;
    virtual T& operator[](size_t) const = 0;
    virtual T& At(size_t position) const = 0;
    virtual size_t capacity() const = 0;
    virtual T& operator*() const = 0;
};

#endif //ARRAY_COLLECTION_H

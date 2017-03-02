//
// Created by svuatoslav on 3/2/17.
//

#ifndef HOMEWORK_2_ARRAY_H
#define HOMEWORK_2_ARRAY_H

class Array
{
private:
    class ArrayPointer;
    size_t current_;
    ArrayPointer* pointer_;
public:
    explicit Array(size_t capacity);
    Array(const Array&);
    ~Array();
    ArrayPointer::value_type& operator[](size_t position);
    ArrayPointer::value_type& operator*();
    const Array& operator=(const Array&);//Возможно без '&', надо смотреть
    const Array clone();
    Array operator+(const int);
    Array operator-(const int);
    Array& operator++();      //Префиксный
    Array operator++(int);   //Постфиксный
    Array& operator--();
    Array operator--(int);
    const Array& operator+=(const int);
    const Array& operator-=(const int);
};

class ArrayPointer
{
private:
    value_type* data_;
    size_t links;
    typedef int value_type;
public:
    explicit ArrayPointer(size_t capacity);
    ArrayPointer(const ArrayPointer&)= delete;
    ~ArrayPointer();
    value_type& operator[](const size_t) const;
    ArrayPointer clone() const;
    void link();
    bool dislink();
    bool suicide();
};

#endif //HOMEWORK_2_ARRAY_H

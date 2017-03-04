//
// Created by svuatoslav on 3/2/17.
//

#ifndef HOMEWORK_2_ARRAY_H
#define HOMEWORK_2_ARRAY_H
#include <cstdint>

class Array
{
private:
	class ArrayPointer;
	size_t current_;
	ArrayPointer* pointer_;
public:
	typedef int value_type;
	explicit Array(size_t capacity);
	Array(const Array&);
	~Array();
	value_type& operator[](size_t position) const;
	value_type& At(size_t position) const; 
	value_type& operator*() const;
	const Array& operator=(const Array&);//Возможно без '&', надо смотреть
	Array clone() const;
	Array operator+(const int);
	Array operator-(const int);
	Array& operator++();      //Префиксный
	Array operator++(int);   //Постфиксный
	Array& operator--();
	Array operator--(int);
	const Array& operator+=(const int);
	const Array& operator-=(const int);
	bool ok() const;
};




class Array::ArrayPointer
{
private:
	value_type * data_;
	size_t capacity_;
	size_t links_;

	void link();
	void dislink();
	void suicide();
public:
	bool ok() const;
	const uint32_t POISON = UINT32_MAX;
	explicit ArrayPointer(size_t capacity);
	ArrayPointer(const ArrayPointer&);
	~ArrayPointer();
	value_type& operator[](const size_t) const; //unsafe
	value_type& At(const size_t) const; //safe
	ArrayPointer clone() const;
	size_t capacity() const;

};

#endif //HOMEWORK_2_ARRAY_H

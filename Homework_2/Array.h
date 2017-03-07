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
	int current_;
	ArrayPointer* pointer_;
public:
	typedef int value_type;
	explicit Array(size_t capacity);
	Array(const Array&);
	~Array();
	value_type& operator[](size_t position) const;
	value_type& At(size_t position) const; 
	const Array& operator=(const Array&);//inc value of pointer
	Array& clone() const; //deep copy of object
	bool ok() const;
	size_t capacity() const;
	value_type& operator*() const;
	Array& operator+(int) const;
	Array& operator-(int) const;
	Array& operator++();
	Array& operator--();
	Array& operator+=(int);
	Array& operator-=(int);  
};




class Array::ArrayPointer
{
private:
	value_type * data_;
	size_t capacity_;
	size_t links_;
	void suicide();
public:	
	bool dislink();
	void link();
	bool ok() const;
	const uint32_t POISON = UINT32_MAX;
	explicit ArrayPointer(size_t capacity);
	ArrayPointer(const ArrayPointer&);
	~ArrayPointer();
	value_type& operator[](const size_t) const; //unsafe
	value_type& At(const size_t) const; //safe
	size_t capacity() const;
};

#endif //HOMEWORK_2_ARRAY_H

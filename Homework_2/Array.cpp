#include "Array.h"
#include <new>
#include <stdexcept>


Array::Array(size_t capacity):current_(0), pointer_(new ArrayPointer(capacity))
{}

Array::Array(const Array& that):current_(0), pointer_(that.pointer_)
{
	that.pointer.link();
}

Array::~Array()
{
	if (pointer_.dislink()) delete pointer_;
}

Array::value_type& Array::operator[](size_t position) const
{
	return (*pointer_)[position];
}

Array::value_type& Array::At(size_t position) const
{
	return pointer_->At(position);
}

const Array& Array::operator=(const Array& that)
{
	pointer_ = that.pointer_;
	that.pointer_->link();
	return *this;
}

Array& Array::clone() const
{
	Array * ret = new Array(0);
	ret->pointer_ = new ArrayPointer(*this.pointer); 
	return *ret;
}

bool Array::ok() const
{
	return pointer_->ok();
}

size_t capacity() const
{
	return pointer_->capacity();
}

value_type& operator*()
{
	if (current_ < 0) throw std::out_of_range("minus is not allow");
	return (*pointer_)[current_];
}

Array& operator+(int value) const
{
	Array *ret = new Array(*this);
	ret->current_ += value;
	return *ret;
}

Array& operator-(int value) const
{
	Array *ret = new Array(*this);
	ret->current_ -= value;
	return *this;
}

Array& operator++()
{
	current_++;
	return *this;
}

Array& operator--()
{
	current_--;
	return *this;
}

Array& operator+=(int value)
{
	current+=value;
	return *this;
}

Array& operator-=(int value)
{
	current-=value;
	return *this;
}





Array::ArrayPointer::ArrayPointer(size_t capacity):data_(nullptr), capacity_(capacity), links_(1)
{
	if (capacity_ == 0) return;
	try
	{
		data_ = new value_type[capacity];
	}
	catch(std::bad_alloc e)
	{
		data_ = nullptr;
		capacity_ = 0;
	}
}

Array::ArrayPointer::ArrayPointer(const ArrayPointer & array_pointer):capacity_(array_pointer.capacity_), links(1)
{
	try
	{
		data_ = new value_type[capacity_];
		for (size_t i = 0; i < capacity_; i++)
			data_[i] = array_pointer.data_[i];
	}
	catch (std::bad_alloc e)
	{
		data_ = nullptr;
		capacity_ = 0;
	}
}

Array::ArrayPointer::~ArrayPointer()
{
	suicide();
}

Array::value_type& Array::ArrayPointer::operator[](const size_t index) const
{
	return data_[index];
}

Array::value_type& Array::ArrayPointer::At(const size_t index) const
{
	if (index<capacity_) return data_[index];
	throw std::out_of_range("bad value");
}

bool Array::ArrayPointer::ok() const
{
	return (links_ != POISON) && (capacity_ != POISON);
}

void Array::ArrayPointer::link()
{
	links_++;
}

bool Array::ArrayPointer::dislink()
{
	return !(--links_);
}

void Array::ArrayPointer::suicide()
{
	if (links_) return;
	delete[] data_;
	data_ = nullptr;
	capacity_ = POISON;
	links_ = POISON;
}

size_t Array::ArrayPointer::capacity() const
{
	return capacity_;
}

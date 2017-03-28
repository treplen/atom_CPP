//---------------------------------------
//! @file bit_pointer.h
//! Definition of the bit_pointer class that is used to return bool value
//---------------------------------------

#ifndef VECTOR_BIT_POINTER_H
#define VECTOR_BIT_POINTER_H

//---------------------------------------
//! @class bit_pointer is used to return bool values from operator [] and at () methods
//---------------------------------------

class bit_pointer
{
    char* byte_pointer_;
    size_t index_;
public:

//---------------------------------------
//! @brief Constructor
//! @param byte_pointer Pointer to the byte that contains the referenced bit
//! @param index Location of the referenced bit in the byte
//---------------------------------------

    bit_pointer(char* byte_pointer, size_t index);

//---------------------------------------
//! @brief Type cast to boolean
//! @return Copy of the referenced boolean value
//---------------------------------------

    operator bool() const;

//---------------------------------------
//! @brief Assignment operator
//! @param value A boolean value to be written to the referenced bit
//! @return Reference to the value parameter
//---------------------------------------

    const bool& operator = (const bool& value);

//---------------------------------------
//! @brief Assignment operator
//! @param value A bit pointer, that contains a boolean value to be written to the referenced bit
//! @return Reference to this object
//---------------------------------------

    const bit_pointer& operator = (const bit_pointer& that);
};

bit_pointer::bit_pointer (char *byte_pointer, size_t index): byte_pointer_(byte_pointer), index_(index)
{

}

const bool &bit_pointer::operator= (const bool &value)
{
    if(value)
        *byte_pointer_ |= utils::access[index_];
    else
        *byte_pointer_ &= ~utils::access[index_];
    return value;
}

const bit_pointer& bit_pointer::operator= (const bit_pointer &that)
{
    *this = that.operator bool();
    return *this;
}

bit_pointer::operator bool() const
{
    return (bool) (*byte_pointer_ & utils::access[index_]);
}
#endif //VECTOR_BIT_POINTER_H

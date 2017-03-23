//
// Created by svuatoslav on 3/24/17.
//

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
    bit_pointer(char* byte_pointer, size_t index);
    operator bool() const;
    const bool& operator = (const bool& value);
    const bit_pointer& operator = (const bit_pointer& that);
    bool operator ! ();
    bool operator==(const bit_pointer&)= delete;
    bool operator!=(const bit_pointer&)= delete;
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

bool bit_pointer::operator! ()
{
    return !operator bool() ;
}

#endif //VECTOR_BIT_POINTER_H

//---------------------------------------
//! @file Array.h
//! Implementation of the array class
//---------------------------------------

#ifndef HOMEWORK_2_ARRAY_H
#define HOMEWORK_2_ARRAY_H

#include <cstring>
#include <iostream>
#include <iomanip>

#define POISON 0xDADADADA

//---------------------------------------
//! Macro to test object integrity
//---------------------------------------

#ifndef ASSERT_OK
#ifdef LOG
#define ASSERT_OK(elem)             \
    if(!(elem)->ok())               \
    {                               \
        (elem)->dump(std::cerr);         \
        assert(!"Object is OK");    \
    }
#else
#define ASSERT_OK(elem)
#endif
#endif

//---------------------------------------
//! @brief Array class
//---------------------------------------

template<class T, size_t size>
class Array;

//---------------------------------------
//! @brief Compares two arrays
//! @return true if arrays are identical
//---------------------------------------

template<class T, size_t size>
bool operator==(const Array<T,size>& array1, const Array<T,size>& array2);

//---------------------------------------
//! @brief Compares two arrays
//! @return true if arrays are not identical
//---------------------------------------

template<class T, size_t size>
bool operator!=(const Array<T,size>& array1, const Array<T,size>& array2);

//---------------------------------------
//! @brief Lexicographically compares two arrays
//! @return true if first array is smaller
//---------------------------------------

template<class T, size_t size>
bool operator< (const Array<T,size>& array1, const Array<T,size>& array2);

//---------------------------------------
//! @brief Lexicographically compares two arrays
//! @return true if first array is smaller or arrays are equal
//---------------------------------------

template<class T, size_t size>
bool operator<=(const Array<T,size>& array1, const Array<T,size>& array2);

//---------------------------------------
//! @brief Lexicographically compares two arrays
//! @return true if first array is bigger
//---------------------------------------

template<class T, size_t size>
bool operator> (const Array<T,size>& array1, const Array<T,size>& array2);

//---------------------------------------
//! @brief Lexicographically compares two arrays
//! @return true if first array is bigger or arrays are equal
//---------------------------------------

template<class T, size_t size>
bool operator>=(const Array<T,size>& array1, const Array<T,size>& array2);

template<class T, size_t size>
class Array {
    static_assert(size>0, "Size must be greater than zero");
private:

//---------------------------------------
//! @brief data storage of the array
//---------------------------------------

    T data_[size];

//---------------------------------------
//! @brief beginning of the actual data in the array's storage
//---------------------------------------

    size_t begin_;

//---------------------------------------
//! @brief ending of the actual data in the array's storage
//---------------------------------------

    size_t end_;

//---------------------------------------
//! @brief capacity of the array's storage
//---------------------------------------

    size_t size_;

public:

//---------------------------------------
//! @brief array's constructor
//! @note fills the storage with poison
//---------------------------------------

    Array();

//---------------------------------------
//! @brief array's destructor
//! @note fills the storage and variables with poison
//---------------------------------------

    ~Array();

//---------------------------------------
//! @brief Returns a value reference from the array
//! @param position offset of the value in the array
//! @return value from the specified position in the array
//! @thwows std::out_of_range if position is out of array bounds
//---------------------------------------

    T& at(size_t position);

//---------------------------------------
//! @brief Returns a value reference from the array
//! @param position offset of the value in the array
//! @return value from the specified position in the array
//---------------------------------------

    T&operator[](size_t position);

//---------------------------------------
//! @brief Returns the first value from the array
//! @return value from the begin_ position in the array
//! @throw std::out_of_range if array is empty
//---------------------------------------

    T& front();

//---------------------------------------
//! @brief Returns the last value from the array
//! @return value from the end_ position in the array
//! @throw std::out_of_range if array is empty
//---------------------------------------

    T& back();

//---------------------------------------
//! @brief Returns a pointer to the array storage
//! @return a pointer to the array storage
//---------------------------------------

    T* data() const ;

//---------------------------------------
//! @brief Checks if the array is empty
//! @return true if the array is empty
//---------------------------------------

    bool empty() const;

//---------------------------------------
//! @brief Returns the current size of the array
//! @return the current size of the array
//---------------------------------------

    size_t current_size() const ;

//---------------------------------------
//! @brief Returns the capacity of the array's storage
//! @return the capacity of the array's storage
//---------------------------------------

    size_t max_size() const ;

//---------------------------------------
//! @brief Fills the array with value
//! @param value A value to fill array with
//---------------------------------------

    void fill(const T& value);

//---------------------------------------
//! @brief Swaps the containment of two arrays
//! @param that Array to swap containment with
//! -------------------------

    void swap(Array<T,size>& that);

//! -------------------------

    friend bool operator==<>(const Array<T,size>& array1, const Array<T,size>& array2);
    friend bool operator!=<>(const Array<T,size>& array1, const Array<T,size>& array2);
    friend bool operator< <>(const Array<T,size>& array1, const Array<T,size>& array2);
    friend bool operator<=<>(const Array<T,size>& array1, const Array<T,size>& array2);
    friend bool operator> <>(const Array<T,size>& array1, const Array<T,size>& array2);
    friend bool operator>=<>(const Array<T,size>& array1, const Array<T,size>& array2);

//! -------------------------

//---------------------------------------
//! @brief Silent verifier
//! @return true if the array is ok
//---------------------------------------

    bool ok() const;

//---------------------------------------
//! @brief dumper
//---------------------------------------

    void dump(std::ostream&) const ;

};

template<class T, size_t size>
Array<T,size>::Array():begin_(size-1),end_(0),size_(size) {
    std::memset(data_,POISON,sizeof(T)*size_);
}

template<class T, size_t size>
Array<T,size>::~Array() {
    std::memset(data_,POISON,sizeof(T)*size_);
    begin_=POISON;
    end_=POISON;
}

template<class T, size_t size>
T& Array<T,size>::at(size_t position)
{
    if(position<0||position>=size_)
        throw std::out_of_range("Position is out of array bounds");
    if(end_<position)
        end_=position;
    if(begin_>position)
        begin_=position;
    return data_[position];
}

template<class T, size_t size>
T& Array<T,size>::operator[](size_t position) {
    if(end_<position)
        end_=position;
    if(begin_>position)
        begin_=position;
    return data_[position];
}

template<class T, size_t size>
T &Array<T,size>::front() {
    if(begin_>end_)
        throw std::out_of_range("Array is empty");
    return data_[begin_];
}

template<class T, size_t size>
T &Array<T,size>::back() {
    if(begin_>end_)
        throw std::out_of_range("Array is empty");
    return data_[end_];
}

template<class T, size_t size>
T* Array<T,size>::data() const {
    return data_;
}

template<class T, size_t size>
bool Array<T,size>::empty() const {
    return end_>begin_;
}

template<class T, size_t size>
size_t Array<T,size>::current_size() const {
    return begin_>end_?0:end_-begin_+1;
};

template<class T, size_t size>
size_t Array<T,size>::max_size() const {
    return size_;
}

template<class T, size_t size>
void Array<T,size>::fill(const T &value) {
    begin_=0;
    end_=size_-1;
    for(int i = 0;i<size_;i++)
        data_[i]=value;
};

template<class T, size_t size>
void Array<T,size>::swap(Array<T,size>& that) {
    Array buffer = *this;
    *this=that;
    that=buffer;
}

template<class T, size_t size>
bool operator==(const Array<T,size>& array1, const Array<T,size>& array2){
    return memcmp(array1,array2,sizeof(Array<T,size>))==0;
}

template<class T, size_t size>
bool operator!=(const Array<T,size>& array1, const Array<T,size>& array2){
    return !memcmp(array1,array2,sizeof(Array<T,size>))==0;
}

template<class T, size_t size>
bool operator<(const Array<T,size>& array1, const Array<T,size>& array2) {
    return memcmp(array1,array2,sizeof(Array<T,size>))<0;
}

template<class T, size_t size>
bool operator<=(const Array<T,size>& array1, const Array<T,size>& array2){
    return memcmp(array1,array2,sizeof(Array<T,size>))<=0;
}

template<class T, size_t size>
bool operator>(const Array<T,size>& array1, const Array<T,size>& array2){
    return memcmp(array1,array2,sizeof(Array<T,size>))>0;
}

template<class T, size_t size>
bool operator>=(const Array<T,size>& array1, const Array<T,size>& array2){
    return memcmp(array1,array2,sizeof(Array<T,size>))>=0;
}

template<class T, size_t size>
bool Array<T,size>::ok() const {
    return !(end_<begin_&&(end_!=0||begin_!=size_-1)||begin_>=size_||end_>=size_);
}

template<class T, size_t size>
void Array<T,size>::dump(std::ostream& out) const {
    out<<"Array("<<(ok()?"OK":"ERROR")<<") ("<<this<<"):\n"<<
        "{\n"
            "\tdata_["<<size_<<"]:\n"<<
            "\t{\n";
    for(int i = 0;i<size_;i++){
        const int*casted = reinterpret_cast<const int*>(&data_[i]);
        out<<"\t\tdata_["<<i<<"] = ";
        for(int j = 0;j<sizeof(T)/4;j++)
            out<<"0x"<<std::setw(sizeof(T)*2)<<std::setfill('0')<<std::hex<<casted[j];
        out<<'\n';
    }
        out<<"\t}\n"<<
        "\tbegin_ = "<<begin_<<(begin_==POISON?" (POISON)":"")<<'\n'<<
        "\tend_ = "<<end_<<(end_==POISON?" (POISON)":"")<<'\n'<<
        "\tsize_ = "<<size_<<(size_==POISON?" (POISON)":"")<<'\n'<<
    "}\n";


}

#endif //HOMEWORK_2_ARRAY_H

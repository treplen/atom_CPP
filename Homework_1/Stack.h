//---------------------------------------
//! @file Stack.h
//! Implementation of a stack class
//!
//! @author Svuatoslav, 2017
//---------------------------------------

#ifndef MYSTACK_STACK_H
#define MYSTACK_STACK_H

#define LOG

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cassert>

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
//! Stack class
//---------------------------------------

template <typename T>
class Stack
{
private:
    size_t capacity_;
    size_t size_;
    T* array_;
public:
    Stack(size_t capacity);
    Stack(Stack<T>& stack);
    ~Stack();

//---------------------------------------
//! Returns a value from the top of the stack
//! @return a value from the top of the stack
//---------------------------------------

    T top() const;

//---------------------------------------
//! Checks if the stack is empty
//! @return emptiness of the stack
//! @throw out_of_range the stack is empty
//---------------------------------------

    bool empty() const;

//---------------------------------------
//! Checks if the stack is full
//! @return fulness of the stack
//---------------------------------------

    bool full() const;

//---------------------------------------
//! Returns the size of the stack
//! @return the size of the stack
//---------------------------------------

    size_t size() const;

//---------------------------------------
//! Returns the capacity of the stack
//! @return the capacity of the stack
//---------------------------------------

    size_t capacity() const;

//---------------------------------------
//! Pushes a value to the stack
//! @param value is an element to be pushed
//! @throw out_of_range the stack is full
//---------------------------------------

    void push(T value);

//---------------------------------------
//! Pops a value from the top of the stack
//! @return a value from the top of the stack
//! @throw out_of_range the stack is empty
//---------------------------------------

    T pop();

//---------------------------------------
//! Silent verifier
//---------------------------------------

    bool ok() const;

//---------------------------------------
//! Dumper
//---------------------------------------

    void dump(std::ostream& out) const;
};
//---------------------------------------
template <typename T>
Stack<T>::Stack(size_t capacity): capacity_(capacity), size_(0)
{
    if(capacity==0)
    {
        array_= nullptr;
        return;
    }
    try
    {
        array_=new T[capacity];
    }
    catch (std::bad_alloc)
    {
        array_= nullptr;
    }
}
//---------------------------------------
template <typename T>
Stack<T>::Stack(Stack<T>& stack): capacity_(stack.capacity_), size_(stack.size_)
{
    ASSERT_OK(&stack);
    if(stack.array_== nullptr)
        array_= nullptr;
    else
    {
        try
        {
            array_=new T[stack.capacity_];
        }
        catch (std::bad_alloc)
        {
            array_= nullptr;
        }
        if(array_!= nullptr) {
            try {
                for (int i = 0; i < size_; i++)
                    array_[i] = stack.array_[i];
            }
            catch (...) {
                delete[] array_;
                array_= nullptr;
            }
        }
    }
    ASSERT_OK(this);
}
//---------------------------------------
template <typename T>
Stack<T>::~Stack()
{
    delete[] array_;
    array_= nullptr;
}
//---------------------------------------
template <typename T>
T Stack<T>::top() const
{
    ASSERT_OK(this);
    if(size_==0)
        throw std::out_of_range("Stack is empty");
    return array_[size_-1];
}
//---------------------------------------
template <typename T>
bool Stack<T>::empty() const
{
    ASSERT_OK(this);
    return size_==0;
}
//---------------------------------------
template <typename T>
bool Stack<T>::full() const
{
    ASSERT_OK(this);
    return size_==capacity_;
}
//---------------------------------------
template <typename T>
size_t Stack<T>::size() const
{
    ASSERT_OK(this);
    return size_;
}
//---------------------------------------
template <typename T>
size_t Stack<T>::capacity() const
{
    ASSERT_OK(this);
    return capacity_;
}
//---------------------------------------
template <typename T>
void Stack<T>::push(T value)
{
    ASSERT_OK(this);
    if(size_==capacity_)
        throw std::out_of_range("Stack is full");
    array_[size_++]=value;
    ASSERT_OK(this);
}
//---------------------------------------
template <typename T>
T Stack<T>::pop()
{
    ASSERT_OK(this);
    if(size_==0)
        throw std::out_of_range("Stack is empty");
    T value = array_[--size_];
    ASSERT_OK(this)
    return value;
}
//---------------------------------------
template <typename T>
bool Stack<T>::ok() const
{
    return (array_!= nullptr&&capacity_!=0||array_== nullptr&&capacity_==0)&&size_<=capacity_;
}
//---------------------------------------
template <typename T>
void Stack<T>::dump(std::ostream& out) const
{
    out<<"Stack("<<(ok()?("ok"):("ERROR"))<<")\n\t{\n\tsize_\t\t = "<<size_<<"\n\tcapacity_\t = "<<capacity_<<
             "\n\tarray_ ["<<capacity_<<"]\n\t}\n";
}

#endif //MYSTACK_STACK_H

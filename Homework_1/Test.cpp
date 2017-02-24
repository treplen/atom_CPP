//
// Created by svuatoslav on 2/24/17.
//

#include <gtest/gtest.h>
#include "Stack.h"
#include <climits>

TEST(Constructor_Destructor__Test,Regular_Creation)
{
    Stack<int>* stack= nullptr;
    for(int i=1;i<100;i++) {
        ASSERT_NO_THROW(stack = new Stack<int>(i));
        ASSERT_EQ(stack->capacity(),i);
        ASSERT_EQ(stack->size(),0);
        ASSERT_NO_THROW(delete stack);
    }
}

TEST(Constructor_Destructor__Test,Zero_Elements_Creation)
{
    Stack<int>* stack= nullptr;
    ASSERT_NO_THROW(stack = new Stack<int>(0));
    ASSERT_EQ(stack->capacity(),0);
    ASSERT_EQ(stack->size(),0);
    ASSERT_NO_THROW(delete stack);
}

TEST(Constructor_Destructor__Test,Too_Many_Elements_Creation)
{
    Stack<double>* stack= nullptr;
    ASSERT_NO_THROW(stack = new Stack<double>(INT_MAX));
    ASSERT_FALSE(stack->ok());
    ASSERT_NO_THROW(delete stack);
}

TEST(Constructor_Destructor__Test,Copy_Constructor)
{
    Stack<int>* stack1= nullptr;
    Stack<int>* stack2= nullptr;
    srand(time(nullptr));
    ASSERT_NO_THROW(stack1 = new Stack<int>(100));
    for(int i = 0;i<100;i++)
        ASSERT_NO_THROW(stack1->push(rand()));
    ASSERT_NO_THROW(stack2=new Stack<int>(*stack1));
    for(int i = 0;i<100;i++)
        ASSERT_EQ(stack1->pop(),stack2->pop());
    ASSERT_NO_THROW(delete stack1);
    ASSERT_NO_THROW(delete stack2);
}

TEST(Constructor_Destructor__Test,Pointer_To_Destructed_Object)
{
    Stack<int>* stack;
    {
        Stack<int> stack1(100);
        stack=&stack1;
    }
    ASSERT_FALSE(stack->ok());
}

TEST(Status__Test,Get_Capacity)
{
    srand(time(0));
    for(int i=0;i<100;i++)
    {
        int size=rand();
        Stack<int>* stack = nullptr;
        ASSERT_NO_THROW(stack=new Stack<int>(size));
        ASSERT_EQ(size,stack->capacity());
        delete stack;
    }
}

TEST(Status__Test,Get_Size)
{
    srand(time(0));
    for(int i=0;i<100;i++)
    {
        int capacity=rand()%1000+1;
        int size=rand()%capacity;
        Stack<int>* stack = nullptr;
        ASSERT_NO_THROW(stack=new Stack<int>(capacity));
        for(int j = 0;j<size;j++)
            stack->push(0);
        ASSERT_EQ(size,stack->size());
        delete stack;
    }
}

TEST(Status__Test,Empty_Full)
{
    srand(time(0));
    for(int i=0;i<100;i++)
    {
        int capacity=rand()%1000+1;
        Stack<int>* stack = nullptr;
        ASSERT_NO_THROW(stack=new Stack<int>(capacity));
        ASSERT_TRUE(stack->empty());
        for(int j = 0;j<capacity;j++)
        {
            ASSERT_FALSE(stack->full());
            stack->push(0);
            ASSERT_FALSE(stack->empty());
        }
        ASSERT_TRUE(stack->full());
        for(int j = 0;j<capacity;j++)
        {
            ASSERT_FALSE(stack->empty());
            stack->pop();
            ASSERT_FALSE(stack->full());
        }
        ASSERT_TRUE(stack->empty());
        delete stack;
    }
}

TEST(Methods___Test,Push_Top)
{
    srand(time(0));
    Stack<int> stack(100);
    for(int i =0;i<100;i++)
    {
        int value = rand();
        ASSERT_NO_THROW(stack.push(value));
        ASSERT_EQ(value,stack.top());
    }
}

TEST(Methods___Test,Push_Pop)
{
    srand(time(0));
    Stack<int> stack(100);
    int array[100];
    for(int i =0;i<100;i++)
    {
        int value = rand();
        array[i]=value;
        ASSERT_NO_THROW(stack.push(value));
    }
    for(int i = 99;i>=0;i--)
    {
        int value=0;
        ASSERT_NO_THROW(value=stack.pop());
        ASSERT_EQ(value,array[i]);
    }
}

TEST(Methods___Test, Pop_Top_From_Empty)
{
    Stack<int>* stack;
    srand(time(0));
    stack=new Stack<int >(rand()%1000+1);
    ASSERT_THROW(stack->top(),std::out_of_range);
    ASSERT_THROW(stack->pop(),std::out_of_range);
    ASSERT_NO_THROW(stack->push(0));
    ASSERT_NO_THROW(stack->pop());
    ASSERT_THROW(stack->top(),std::out_of_range);
    ASSERT_THROW(stack->pop(),std::out_of_range);
}

TEST(Methods___Test, Push_To_Full)
{
    Stack<int>* stack;
    srand(time(0));
    int capacity = rand()%1000+1;
    stack=new Stack<int >(capacity);
    for(int i = 0;i<capacity;i++)
        ASSERT_NO_THROW(stack->push(0));
    ASSERT_THROW(stack->push(0),std::out_of_range);
    ASSERT_NO_THROW(stack->pop());
    ASSERT_NO_THROW(stack->push(0));
    ASSERT_THROW(stack->push(0),std::out_of_range);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
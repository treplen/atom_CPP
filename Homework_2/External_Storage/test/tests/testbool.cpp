////
//// Created by sl on 14.03.17.
////

#include "gtest/gtest.h"
#include <Array.h>

TEST(Array, Constructorbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 1;
    for (int i=0; i<20; i++)
        std::cout<<a[i];
    ASSERT_EQ(a[0], 1);
    for (int i=0; i<20; i++)
        a[i] = false;
    for (int i=0; i<20; i++)
        ASSERT_EQ(a[i], 0);
}

TEST(Array, CopyConstructorbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 1;
    Array<bool> b(a);
    for (int i=0; i<20; i++)
        ASSERT_EQ(1, b[i]);
}

TEST(Array,destruktorbool) {
    Array<bool> *a;
    a = new Array<bool>(20);
    delete a;
    ASSERT_FALSE(a->ok());
}

TEST(Array, pozition_valuebool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(0, a[i]);
    for (int i=0; i<10; i++)
        a[i]++;
    for (int i=0; i<10; i++)
        ASSERT_EQ(1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(0, a[i]);
}

TEST(Array, Atbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(0, a[i]);
    for (int i=0; i<10; i++)
        a.At(i) = 1;
    for (int i=0; i<10; i++)
        ASSERT_EQ(1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(0, a[i]);
}

TEST(Array,copytestbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 0;
    Array<bool> b(20);
    b=a;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        b[i]++;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        a[i] = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
}

TEST(Array,copysizetestbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 1;
    Array<bool> b(50);
    b=a;
    ASSERT_EQ(b.capacity(), a.capacity());
    Array<bool> c(10);
    c=a;
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}

TEST(Array,clontestbool)   ///why????????????
{
    int s = 10;
    Array<bool> a(s);
    for (int i=0; i<s; i++)
        a[i] = 1;
    Array<bool> b;
    b = a.clone();
    for (int i=0; i<s; i++)
        std::cout<<a[i];
    std::cout<<std::endl;

    for (int i=0; i<s; i++)
        std::cout<<b[i];
    std::cout<<std::endl;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        b[i]=!b[i];
    for (int i=0; i<20; i++)
        ASSERT_NE(b[i], a[i]);
    for (int i=0; i<20; i++)
        a[i]=!a[i];
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
}

TEST(Array,clonsizetest2bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 1;
    Array<bool> b(50);
    b=a.clone();
    ASSERT_EQ(b.capacity(), a.capacity());
    Array<bool> c(10);
    c=a.clone();
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Array,oktestbool)
{
    Array<bool> *a = new Array<bool>(20);
    for (int i=0; i<20; i++)
        a->At(i) = 1;
    ASSERT_EQ(1, a->ok());
   delete a;
   ASSERT_EQ(0, a->ok());
}

TEST(Array,capacitytestbool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 1;
    ASSERT_EQ(20,a.capacity());

}

TEST(Array, operationsbool) //problem with auto free res
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    ASSERT_EQ(*a, 0);
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
    a+=6;
    ASSERT_EQ(0,*a);
    a-=6;
    ASSERT_EQ(0,*a);
    ASSERT_EQ(0, *(a+8));
    a+=7;
    ASSERT_EQ(1, *(a-6));
}

TEST(Array, operations0bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = 0;
    ASSERT_EQ(*a,0);
}

TEST(Array, operations1bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
}

TEST(Array, operations2bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    ASSERT_EQ(*a, 0);
    ASSERT_EQ(0, *(a+8));
    a+=7;
    ASSERT_EQ(1, *a);
    ASSERT_EQ(1, *(a-6));
    a-=8;
    ASSERT_EQ(0, *(a+1));
}

TEST(Array, operations3bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    ASSERT_EQ(*a, 0);
    a+=6;
    ASSERT_EQ(0, *a);
    a-=6;
    ASSERT_EQ(0, *a);
}

TEST(Array, operations4bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    a.At(5) = 0;
    a+=5;
    ASSERT_EQ(0,*a);
}

TEST(Array,operations5bool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i % 2;
    ASSERT_EQ(*a,0);
    ASSERT_ANY_THROW(*(a-1));
    ASSERT_ANY_THROW(*(a+50));
    --a;
    ASSERT_ANY_THROW(*a);
    a+=50;
    ASSERT_ANY_THROW(*a);

}

TEST(Array, oversizebool)
{
    Array<bool> a(20);
    for (int i=0; i<20; i++)
        ASSERT_NO_THROW(a.At(i) = 1);
    ASSERT_ANY_THROW(a.At(21) = 0);
    ASSERT_ANY_THROW(a.At(-1) = 0);
}
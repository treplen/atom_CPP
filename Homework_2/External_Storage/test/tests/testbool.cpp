////
//// Created by sl on 14.03.17.
////

#include "gtest/gtest.h"
#include <Vector.h>

TEST(Array, Constructorbool)
{
    Vector<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 1;
    ASSERT_EQ(a[0], 1);
    for (int i=0; i<20; i++)
        a[i] = false;
    for (int i=0; i<20; i++)
        ASSERT_EQ(a[i], 0);
}

TEST(Array, CopyConstructorbool)
{
    Vector<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 1;
    Vector<bool> b(a);
    for (int i=0; i<20; i++)
        ASSERT_EQ(1, b[i]);
}

TEST(Array,destruktorbool) {
    Vector<bool> *a;
    a = new Vector<bool>(20);
    delete a;
    ASSERT_FALSE(a->ok());
}

TEST(Array, pozition_valuebool)
{
    Vector<bool> a(20);
    for (int i=0; i<20; i++)
        a[i] = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(0, a[i]);
    for (int i=0; i<10; i++)
        a[i]=!a[i];
    for (int i=0; i<10; i++)
        ASSERT_EQ(1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(0, a[i]);
}

TEST(Array, Atbool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(0, a[i]);
    for (int i=0; i<10; i++)
        a.at(i) = 1;
    for (int i=0; i<10; i++)
        ASSERT_EQ(1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(0, a[i]);
}

TEST(Array,copytestbool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = 0;
    Vector<bool> b(20);
    b=a;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        b[i]=!b[i];
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        a[i] = 0;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
}

TEST(Array,copysizetestbool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = 1;
    Vector<bool> b(50);
    b=a;
    ASSERT_EQ(b.capacity(), a.capacity());
    Vector<bool> c(10);
    c=a;
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}

TEST(Array,clontestbool)
{
    int s = 10;
    Vector<bool> a(s);
    for (int i=0; i<s; i++)
        a.push_back (1);
    Vector<bool> b;
    b = a.clone();
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
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = 1;
    Vector<bool> b(50);
    b=a.clone();
    ASSERT_EQ(b.capacity(), a.capacity());
    Vector<bool> c(10);
    c=a.clone();
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Array,oktestbool)
{
    Vector<bool> *a = new Vector<bool>(20);
    a->resize (20);
    for (int i=0; i<20; i++)
        a->at(i) = 1;
    ASSERT_EQ(1, a->ok());
   delete a;
   ASSERT_EQ(0, a->ok());
}

TEST(Array,capacitytestbool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.push_back (1);
    ASSERT_EQ(24,a.capacity());

}

TEST(Array, operationsbool) //problem with auto free res
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
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
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = 0;
    ASSERT_EQ(*a,0);
}

TEST(Array, operations1bool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
}

TEST(Array, operations2bool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
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
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
    ASSERT_EQ(*a, 0);
    a+=6;
    ASSERT_EQ(0, *a);
    a-=6;
    ASSERT_EQ(0, *a);
}

TEST(Array, operations4bool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
    a.at(5) = 0;
    a+=5;
    ASSERT_EQ(0,*a);
}

TEST(Array,operations5bool)
{
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        a.at(i) = i % 2;
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
    Vector<bool> a(20);
    a.resize (20);
    for (int i=0; i<20; i++)
        ASSERT_NO_THROW(a[i] = 1);
    ASSERT_ANY_THROW(a.at(21) = 0);
    ASSERT_ANY_THROW(a.at(-1) = 0);
}
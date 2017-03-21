//
// Created by sl on 14.03.17.
//

#include "gtest/gtest.h"
#include <Array.h>

TEST(Array, Constructor)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
    a[i] = i;
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, a[i]);
}

TEST(Array, CopyConstructor)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a[i] = i;
    Array<int> b(a);
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, b[i]);
}

TEST(Array,destruktor)
{
    Array<int> * a;
    a = new Array<int>(20);
    delete a;
    ASSERT_FALSE(a->ok());

}

TEST(Array, pozition_value)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a[i] = i;
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, a[i]);
    for (int i=0; i<10; i++)
        a[i]++;
    for (int i=0; i<10; i++)
        ASSERT_EQ(i+1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(i, a[i]);
}

TEST(Array, At)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, a[i]);
    for (int i=0; i<10; i++)
        a.At(i) = i+1;
    for (int i=0; i<10; i++)
        ASSERT_EQ(i+1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(i, a[i]);
}

TEST(Array,copytest)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    Array<int> b(20);
    b=a;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        b[i]++;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        a[i]++;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
}

TEST(Array,copysizetest)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    Array<int> b(50);
    b=a;
        ASSERT_EQ(b.capacity(), a.capacity());
    Array<int> c(10);
    c=a;
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Array,clontest)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    Array<int> b(20);
    b=a.clone();
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
    for (int i=0; i<20; i++)
        b[i]++;
    for (int i=0; i<20; i++)
        ASSERT_NE(b[i], a[i]);
    for (int i=0; i<20; i++)
        a[i]++;
    for (int i=0; i<20; i++)
        ASSERT_EQ(b[i], a[i]);
}

TEST(Array,clonsizetest2)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    Array<int> b(50);
    b=a.clone();
    ASSERT_EQ(b.capacity(), a.capacity());
    Array<int> c(10);
    c=a.clone();
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Array,oktest)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(1, a.ok());
    //delete a;
    //ASSERT_EQ(0, a.ok());
}

TEST(Array,capacitytest)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(20,a.capacity());

}

TEST(Array, operations) //problem with auto free res
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(*a,0);
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
    a+=6;
    ASSERT_EQ(6,*a);
    a-=6;
    ASSERT_EQ(0,*a);
    ASSERT_EQ(8, *(a+8));
    a+=7;
    ASSERT_EQ(1, *(a-6));
}

TEST(Array, operations0)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(*a,0);
}

TEST(Array, operations1)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
}

TEST(Array, operations2)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(*a,0);
    ASSERT_EQ(8, *(a+8));
    a+=7;
    ASSERT_EQ(7, *a);
    //ASSERT_EQ(1, *(a-6));
    a-=8;
    ASSERT_EQ(0, *(a+1));
}

TEST(Array, operations3)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(*a,0);
    a+=6;
    ASSERT_EQ(6,*a);
    a-=6;
    ASSERT_EQ(0,*a);
}

TEST(Array, operations4)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    a.At(5) = 10;
    a+=5;
    ASSERT_EQ(10,*a);
}

TEST(Array,operations5)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        a.At(i) = i;
    ASSERT_EQ(*a,0);
    ASSERT_ANY_THROW(*(a-1));
    ASSERT_ANY_THROW(*(a+50));
    --a;
    ASSERT_ANY_THROW(*a);
    a+=50;
    ASSERT_ANY_THROW(*a);

}

TEST(Array, oversize)
{
    Array<int> a(20);
    for (int i=0; i<20; i++)
        ASSERT_NO_THROW(a.At(i) = i);
    ASSERT_ANY_THROW(a.At(21)=21);
    ASSERT_ANY_THROW(a.At(-1)=21);
}
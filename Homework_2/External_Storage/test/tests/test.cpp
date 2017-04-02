//
// Created by sl on 14.03.17.
//

#include "gtest/gtest.h"
#include <Vector.h>

TEST(Vector, Constructor)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
    a[i] = i;
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, a[i]);
}

TEST(Vector, CopyConstructor)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a[i] = i;
    Vector<int> b(a);
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, b[i]);
}

TEST(Vector,destruktor)
{
    Vector<int> * a;
    a = new Vector<int>(20);
    delete a;
    ASSERT_FALSE(a->ok());

}

TEST(Vector, pozition_value)
{
    Vector<int> a(20);
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

TEST(Vector, at)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    for (int i=0; i<20; i++)
        ASSERT_EQ(i, a[i]);
    for (int i=0; i<10; i++)
        a.at(i) = i+1;
    for (int i=0; i<10; i++)
        ASSERT_EQ(i+1, a[i]);
    for (int i=10; i<20; i++)
        ASSERT_EQ(i, a[i]);
}

TEST(Vector,copytest)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    Vector<int> b(20);
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

TEST(Vector,copysizetest)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    Vector<int> b(50);
    b=a;
        ASSERT_EQ(b.capacity(), a.capacity());
    Vector<int> c(10);
    c=a;
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Vector,clontest)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    Vector<int> b(20);
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

TEST(Vector,clonsizetest2)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    Vector<int> b(50);
    b=a.clone();
    ASSERT_EQ(b.capacity(), a.capacity());
    Vector<int> c(10);
    c=a.clone();
    ASSERT_EQ(c.capacity(), a.capacity());
    ASSERT_EQ(b.capacity(), c.capacity());
}


TEST(Vector,oktest)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(1, a.ok());
    //delete a;
    //ASSERT_EQ(0, a.ok());
}

TEST(Vector,capacitytest)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(20,a.capacity());

}

TEST(Vector, operations) //problem with auto free res
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
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

TEST(Vector, operations0)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(*a,0);
}

TEST(Vector, operations1)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ++a;
    ASSERT_EQ(*a, 1);
    --a;
    ASSERT_EQ(*a, 0);
}

TEST(Vector, operations2)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(*a,0);
    ASSERT_EQ(8, *(a+8));
    a+=7;
    ASSERT_EQ(7, *a);
    //ASSERT_EQ(1, *(a-6));
    a-=8;
    ASSERT_EQ(0, *(a+1));
}

TEST(Vector, operations3)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(*a,0);
    a+=6;
    ASSERT_EQ(6,*a);
    a-=6;
    ASSERT_EQ(0,*a);
}

TEST(Vector, operations4)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    a.at(5) = 10;
    a+=5;
    ASSERT_EQ(10,*a);
}

TEST(Vector,operations5)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        a.at(i) = i;
    ASSERT_EQ(*a,0);
    ASSERT_ANY_THROW(*(a-1));
    ASSERT_ANY_THROW(*(a+50));
    --a;
    ASSERT_ANY_THROW(*a);
    a+=50;
    ASSERT_ANY_THROW(*a);

}

TEST(Vector, oversize)
{
    Vector<int> a(20);
    for (int i=0; i<20; i++)
        ASSERT_NO_THROW(a.at(i) = i);
    ASSERT_ANY_THROW(a.at(21)=21);
    ASSERT_ANY_THROW(a.at(-1)=21);
}
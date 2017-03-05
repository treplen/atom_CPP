#include "Array.h"
#include <gtest/gtest.h>

TEST(Constructor_Destructor__Test,Regular_Create_Destroy)
{
    Array<char,3>* array=nullptr;
    ASSERT_NO_THROW(array=(new Array<char,3>));
    ASSERT_TRUE(array->ok());
    ASSERT_NO_THROW(delete array);
}

TEST(Constructor_Destructor__Test,Copy_Constructor)
{
    Array<char,6> array;
    Array<char,6> copy(array);
    ASSERT_TRUE(array==copy);
}

TEST(Constructor_Destructor__Test,Bad_Pointer)
{
    Array<Array<int,67>,10>* array;
    {
        Array<Array<int,67>,10> a;
        ASSERT_TRUE(a.ok());
        array=&a;
    }
    ASSERT_FALSE(array->ok());
}

TEST(Operators__Test,Indexation)
{
    srand(time(0));
    Array<int,67> array;
    int nums[67];
    for(int i =0;i<67;i++)
    {
        nums[i]=rand();
        ASSERT_NO_THROW(array[i]=nums[i]);
    }
    for(int i=0;i<67;i++)
        ASSERT_EQ(nums[i],array[i]);
}

TEST(Operators__Test,Assignment)
{
    srand(time(0));
    Array<int,67> array;
    for(int i = 0;i<67;i++)
        array[i]=rand();
    Array<int,67> copy;
    ASSERT_NO_THROW(copy=array);
    ASSERT_TRUE(copy==array);
}

TEST(Compare_Operators__Test,Equals)
{
    srand(time(0));
    Array<int,67> array1;
    Array<int,67> array2;
    ASSERT_TRUE(array1==array2);
    for(int i = 0;i<67;i++)
    {
        int b = rand();
        array1[i]=b;
        array2[i]=b;
    }
    ASSERT_TRUE(array1==array2);
    ASSERT_FALSE(array1!=array2);
    array2[4]++;
    ASSERT_FALSE(array1==array2);
    ASSERT_TRUE(array1!=array2);
}

TEST(Compare_Operators__Test,GT_LT_GE_LE)
{
    srand(time(0));
    Array<int,67> array1;
    Array<int,67> array2;
    for(int i = 0;i<67;i++)
    {
        int b = rand();
        array1[i]=b;
        array2[i]=b;
    }
    ASSERT_FALSE(array1<array2);
    ASSERT_FALSE(array1>array2);
    ASSERT_TRUE(array1<=array2);
    ASSERT_TRUE(array1>=array2);
    array1[5]++;
    array2[6]++;
    ASSERT_FALSE(array1<array2);
    ASSERT_TRUE(array1>array2);
    ASSERT_FALSE(array1<=array2);
    ASSERT_TRUE(array1>=array2);
    array1[4]--;
    ASSERT_TRUE(array1<array2);
    ASSERT_FALSE(array1>array2);
    ASSERT_TRUE(array1<=array2);
    ASSERT_FALSE(array1>=array2);
}

TEST(Data_Access__Test,At)
{
    srand(time(0));
    Array<int,67> array;
    int nums[67];
    for(int i =0;i<67;i++)
    {
        nums[i]=rand();
        ASSERT_NO_THROW(array.at(i)=nums[i]);
    }
    for(int i=0;i<67;i++)
        ASSERT_EQ(nums[i],array.at(i));
    ASSERT_THROW(array.at(rand()+67),std::out_of_range);
}

TEST(Data_Access__Test,Data)
{
    srand(time(0));
    Array<int,67> array;
    int nums[67];
    for(int i =0;i<67;i++)
    {
        nums[i]=rand();
        ASSERT_NO_THROW(array.at(i)=nums[i]);
    }
    int* data = array.data();
    for(int i=0;i<67;i++)
        ASSERT_EQ(nums[i],data[i]);
    int b = rand();
    int i = rand()%67;
    data[i]=b;
    ASSERT_EQ(b,array[i]);
}

TEST(Data_Access__Test,Front_Back_Size_Empty)
{
    srand(time(0));
    Array<int,67> array;
    ASSERT_EQ(array.max_size(),67);
    ASSERT_TRUE(array.empty());
    ASSERT_EQ(array.current_size(),0);
    ASSERT_THROW(array.front(),std::out_of_range);
    ASSERT_THROW(array.back(),std::out_of_range);
    int i1 = rand()%67;
    int b1 = rand();
    array[i1]=b1;
    ASSERT_FALSE(array.empty());
    ASSERT_EQ(array.front(),b1);
    ASSERT_EQ(array.back(),b1);
    ASSERT_EQ(array.current_size(),1);
    int i2=i1;
    while (i2==i1)
        i2=rand()%67;
    int b2=rand();
    array[i2]=b2;
    ASSERT_FALSE(array.empty());
    ASSERT_EQ(array.front(),i2>i1?b1:b2);
    ASSERT_EQ(array.back(),i2>i1?b2:b1);
    ASSERT_EQ(array.current_size(),i2>i1?i2-i1+1:i1-i2+1);
}

TEST(Data_Fill_Methods__Test, Fill)
{
    srand(time(0));
    Array<int,67> array;
    int b=rand();
    array.fill(b);
    for(int i = 0; i<67; i++)
        ASSERT_EQ(b,array[i]);
}

TEST(Data_Fill_Methods__Test, Swap)
{
    srand(time(0));
    Array<int,67> array1, array2;
    int b1[67], b2[67];
    for(int i = 0; i<67; i++)
    {
        b1[i]=rand();
        b2[i]=rand();
        array1[i]=b1[i];
        array2[i]=b2[i];
    }
    array1.swap(array2);
    for(int i = 0; i<67; i++)
    {
        ASSERT_EQ(b1[i],array2[i]);
        ASSERT_EQ(b2[i],array1[i]);
    }
    array2.swap(array1);
    for(int i = 0; i<67; i++)
    {
        ASSERT_EQ(b1[i],array1[i]);
        ASSERT_EQ(b2[i],array2[i]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
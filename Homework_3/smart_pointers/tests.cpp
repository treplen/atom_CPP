
#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "auto_ptr.h"
#include "shared_ptr.h"

class TestClass
{
public:
    int NotZero;

    TestClass (int value = 1337) : NotZero (value) {};

    ~TestClass () { NotZero = 0; };

    bool ok () const { return NotZero != 0; }

    bool operator== (const TestClass &that) const { return NotZero == that.NotZero; }
};

TEST(unique_ptr__Test, constructor_destructor__Test)
{
    TestClass *ptr = new TestClass;
    unique_ptr<TestClass> *smrt_ptr = nullptr;
    ASSERT_NO_THROW (smrt_ptr = new unique_ptr<TestClass> ());
    ASSERT_EQ (smrt_ptr->get (), nullptr);
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_NO_THROW (smrt_ptr = new unique_ptr<TestClass> (ptr));
    ASSERT_EQ (ptr, smrt_ptr->get ());
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_FALSE (ptr->ok ());
}

TEST(unique_ptr__Test, zombie_object__Test)
{
    unique_ptr<TestClass> *smrt_ptr;
    {
        unique_ptr<TestClass> ptr;
        smrt_ptr = &ptr;
    }
    ASSERT_FALSE (smrt_ptr->ok ());
}

TEST(unique_ptr__Test, access_methods__Test)
{
    TestClass *ptr = new TestClass (rand ());
    unique_ptr<TestClass> smrt_ptr = ptr;
    ASSERT_EQ (*ptr, *smrt_ptr);
    ASSERT_EQ (ptr->NotZero, smrt_ptr->NotZero);
}

TEST(unique_ptr__Test, swap__Test)
{
    TestClass *ptr1 = new TestClass (rand ());
    TestClass *ptr2 = new TestClass (rand ());
    unique_ptr<TestClass> smrt_ptr1 = ptr1;
    unique_ptr<TestClass> smrt_ptr2 = ptr2;
    smrt_ptr1.swap (smrt_ptr2);
    ASSERT_EQ (smrt_ptr1.get (), ptr2);
    ASSERT_EQ (smrt_ptr2.get (), ptr1);
}

TEST(unique_ptr__Test, pointer_assignment__Test)
{
    TestClass *ptr1 = new TestClass (rand ());
    TestClass *ptr2 = new TestClass (rand ());
    unique_ptr<TestClass> smrt_ptr = ptr1;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = ptr2);
    ASSERT_FALSE (ptr1->ok ());
    ASSERT_TRUE (ptr2->ok ());
    ASSERT_TRUE (smrt_ptr->ok ());
    ASSERT_EQ (smrt_ptr.get (), ptr2);
    ASSERT_NE (smrt_ptr.get (), ptr1);
}

TEST(unique_ptr__Test, move_assignment__Test)
{
    TestClass *ptr = new TestClass;
    unique_ptr<TestClass> smrt_ptr;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = unique_ptr<TestClass> (ptr));
    ASSERT_EQ (smrt_ptr.get (), ptr);
}

TEST(unique_ptr__Test, bool_cast__Test)
{
    TestClass *ptr = new TestClass;
    unique_ptr<TestClass> smrt_ptr;
    ASSERT_FALSE (smrt_ptr);
    smrt_ptr = ptr;
    ASSERT_TRUE (smrt_ptr);
    smrt_ptr = nullptr;
    ASSERT_FALSE (smrt_ptr);
}

TEST(unique_ptr__Test, release_reset__Test)
{
    TestClass *ptr1 = new TestClass;
    TestClass *ptr2 = new TestClass;
    unique_ptr<TestClass> smrt_ptr;
    ASSERT_EQ (smrt_ptr.release (), nullptr);
    ASSERT_TRUE (smrt_ptr.ok ());
    smrt_ptr = ptr1;
    ASSERT_EQ (smrt_ptr.release (), ptr1);
    ASSERT_TRUE (smrt_ptr.ok ());
    ASSERT_TRUE (ptr1->ok ());
    smrt_ptr = ptr1;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr.reset (ptr2));
    ASSERT_FALSE (ptr1->ok ());
    ASSERT_EQ (smrt_ptr.get (), ptr2);
}

TEST(auto_ptr__Test, constructor_destructor__Test)
{
    TestClass *ptr = new TestClass;
    auto_ptr<TestClass> *smrt_ptr = nullptr;
    ASSERT_NO_THROW (smrt_ptr = new auto_ptr<TestClass> ());
    ASSERT_EQ (smrt_ptr->get (), nullptr);
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_NO_THROW (smrt_ptr = new auto_ptr<TestClass> (ptr));
    ASSERT_EQ (ptr, smrt_ptr->get ());
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_FALSE (ptr->ok ());
}

TEST(auto_ptr__Test, zombie_object__Test)
{
    auto_ptr<TestClass> *smrt_ptr;
    {
        auto_ptr<TestClass> ptr;
        smrt_ptr = &ptr;
    }
    ASSERT_FALSE (smrt_ptr->ok ());
}

TEST(auto_ptr__Test, copy_constructor__Test)
{
    TestClass *ptr = new TestClass;
    auto_ptr<TestClass> smrt_ptr1 = ptr;
    auto_ptr<TestClass> smrt_ptr2 (smrt_ptr1);
    ASSERT_TRUE (ptr->ok ());
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    ASSERT_EQ (smrt_ptr1.get (), nullptr);
    ASSERT_EQ (smrt_ptr2.get (), ptr);
}

TEST(auto_ptr__Test, assignment__Test)
{
    TestClass *ptr = new TestClass;
    auto_ptr<TestClass> smrt_ptr1 = ptr;
    auto_ptr<TestClass> smrt_ptr2;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr1 = smrt_ptr2);
    ASSERT_EQ (smrt_ptr1.get (), nullptr);
    ASSERT_EQ (smrt_ptr2.get (), ptr);
}

TEST(auto_ptr__Test, move_assignment__Test)
{
    TestClass *ptr = new TestClass;
    auto_ptr<TestClass> smrt_ptr;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = auto_ptr<TestClass> (ptr));
    ASSERT_EQ (smrt_ptr.get (), ptr);
}

TEST(shared_ptr__Test, constructor_destructor__Test)
{
    TestClass *ptr = new TestClass;
    shared_ptr<TestClass> *smrt_ptr = nullptr;
    ASSERT_NO_THROW (smrt_ptr = new shared_ptr<TestClass> ());
    ASSERT_EQ (smrt_ptr->get (), nullptr);
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_NO_THROW (smrt_ptr = new shared_ptr<TestClass> (ptr));
    ASSERT_EQ (ptr, smrt_ptr->get ());
    ASSERT_NO_FATAL_FAILURE (delete smrt_ptr);
    ASSERT_FALSE (ptr->ok ());
}

TEST(shared_ptr__Test, copy_constructor_destructor_for_shared__Test)
{
    TestClass *ptr = new TestClass;
    {
        shared_ptr<TestClass> smrt_ptr1 = ptr;
        {
            shared_ptr<TestClass> smrt_ptr2 (smrt_ptr1);
            ASSERT_EQ (smrt_ptr1.get (), smrt_ptr2.get ());
            ASSERT_TRUE (ptr->ok ());
        }
        ASSERT_TRUE (ptr->ok ());
    }
    ASSERT_FALSE (ptr->ok ());
}

TEST(shared_ptr__Test, pointer_assignment__Test)
{
    TestClass *ptr1 = new TestClass (rand ());
    TestClass *ptr2 = new TestClass (rand ());
    shared_ptr<TestClass> smrt_ptr = ptr1;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = ptr2);
    ASSERT_FALSE (ptr1->ok ());
    ASSERT_TRUE (ptr2->ok ());
    ASSERT_TRUE (smrt_ptr->ok ());
    ASSERT_EQ (smrt_ptr.get (), ptr2);
    ASSERT_NE (smrt_ptr.get (), ptr1);
}

TEST(shared_ptr__Test, access_methods__Test)
{
    TestClass *ptr = new TestClass (rand ());
    shared_ptr<TestClass> smrt_ptr;
    ASSERT_ANY_THROW (*smrt_ptr);
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = ptr);
    ASSERT_EQ (*ptr, *smrt_ptr);
    ASSERT_EQ (ptr->NotZero, smrt_ptr->NotZero);
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = nullptr);
    ASSERT_ANY_THROW (*smrt_ptr);
}

TEST(shared_ptr__Test, assignment__Test)
{
    TestClass *ptr = new TestClass;
    shared_ptr<TestClass> smrt_ptr1 = ptr;
    shared_ptr<TestClass> smrt_ptr2;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr2 = smrt_ptr1);
    ASSERT_EQ (smrt_ptr1.get (), smrt_ptr2.get ());
}

TEST(shared_ptr__Test, move_assignment__Test)
{
    TestClass *ptr = new TestClass;
    shared_ptr<TestClass> smrt_ptr;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr = shared_ptr<TestClass> (ptr));
    ASSERT_EQ (smrt_ptr.get (), ptr);
}

TEST(shared_ptr__Test, bool_cast__Test)
{
    TestClass *ptr = new TestClass;
    shared_ptr<TestClass> smrt_ptr;
    ASSERT_FALSE (smrt_ptr);
    smrt_ptr = ptr;
    ASSERT_TRUE (smrt_ptr);
    smrt_ptr = nullptr;
    ASSERT_FALSE (smrt_ptr);
}

TEST(shared_ptr__Test, release_reset__Test)
{
    TestClass *ptr1 = new TestClass;
    TestClass *ptr2 = new TestClass;
    shared_ptr<TestClass> smrt_ptr1;
    shared_ptr<TestClass> smrt_ptr2;
    ASSERT_EQ (smrt_ptr1.release (), nullptr);
    ASSERT_EQ (smrt_ptr2.release (), nullptr);
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    smrt_ptr1 = ptr1;
    smrt_ptr2 = smrt_ptr1;
    ASSERT_EQ (smrt_ptr1.release (), ptr1);
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    ASSERT_TRUE (ptr1->ok ());
    ASSERT_EQ (smrt_ptr1.get (), nullptr);
    ASSERT_EQ (smrt_ptr2.get (), ptr1);
    ASSERT_EQ (smrt_ptr2.release (), ptr1);
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    ASSERT_TRUE (ptr1->ok ());
    ASSERT_EQ (smrt_ptr1.get (), nullptr);
    ASSERT_EQ (smrt_ptr2.get (), nullptr);
    smrt_ptr1 = ptr1;
    smrt_ptr2 = smrt_ptr1;
    ASSERT_NO_FATAL_FAILURE (smrt_ptr1.reset (ptr2));
    ASSERT_TRUE (ptr1->ok ());
    ASSERT_TRUE (ptr2->ok ());
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    ASSERT_EQ (smrt_ptr1.get (), ptr2);
    ASSERT_EQ (smrt_ptr2.get (), ptr1);
    ASSERT_NO_FATAL_FAILURE (smrt_ptr2.reset ());
    smrt_ptr2 = smrt_ptr1;
    ASSERT_FALSE (ptr1->ok ());
    ASSERT_TRUE (ptr2->ok ());
    ASSERT_TRUE (smrt_ptr1.ok ());
    ASSERT_TRUE (smrt_ptr2.ok ());
    ASSERT_EQ (smrt_ptr1.get (), ptr2);
    ASSERT_EQ (smrt_ptr2.get (), ptr2);
}

int main (int argc, char **argv)
{
    srand ((unsigned int) time (0));
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}

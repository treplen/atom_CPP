//
// Created by svuatoslav on 3/24/17.
//

#ifndef HOMEWORK_3_UTILS_H
#define HOMEWORK_3_UTILS_H

#include <iostream>
#include <cassert>

#define ERROR_LOG

#define ERROR_STREAM utils::ostream(std::cerr)
#define LOG_STREAM utils::ostream(std::cout)

#ifdef FULL_LOG

#define INFO( object )          \
if(!(object).ok())              \
{                               \
    (object).dump(ERROR_STREAM);\
    assert(!"Object is OK");    \
}                               \
else                            \
{                               \
    (object).dump(LOG_STREAM);  \
}

#else
#ifdef ERROR_LOG

#define INFO( object )          \
if(!(object).ok())              \
{                               \
    (object).dump(ERROR_STREAM);\
    assert(!"Object is ok");    \
}

#else
#define INFO( object )
#endif
#endif

namespace utils
{

    const int POISON_INT = 0xEDAEDAED;
    const void *POISON_PTR = (void *) 0xEDAEDAEDAEDA;

    class ostream
    {
        int displacement_;
        std::ostream *out_;
    public:
        template<typename T>
        ostream &print (T &&value);

        template<typename T, typename... Args>
        ostream &print (T &&value, Args...);

        template<typename T, typename... Args>
        ostream &println (T &&value, Args...);

        ostream &println ();

        ostream (std::ostream &out, int displacement = 0);

        ostream &operator+= (int displacement);

        ostream &operator-= (int displacement);

        ostream &operator++ ();

        ostream &operator-- ();
    };

    utils::ostream::ostream (std::ostream &out, int displacement) : displacement_ (displacement), out_ (&out)
    {
    }

    utils::ostream &utils::ostream::operator+= (int displacement)
    {
        displacement_ += displacement;
        return *this;
    }

    utils::ostream &utils::ostream::operator-= (int displacement)
    {
        displacement_ -= displacement;
        return *this;
    }

    template<typename T>
    ostream &ostream::print (T &&value)
    {
        (*out_) << value;
        return *this;
    }

    template<typename T, typename... Args>
    utils::ostream &utils::ostream::print (T &&value, Args... args)
    {
        (*out_) << value;
        print (args...);
        return *this;
    }

    template<typename T, typename... Args>
    ostream &ostream::println (T &&value, Args... args)
    {
        for (int i = 0; i < displacement_; i++)
            out_->put ('\t');
        print (value, args...);
        out_->put ('\n');
        return *this;
    }

    ostream &ostream::println ()
    {
        out_->put ('\n');
        return *this;
    }

    ostream &ostream::operator++ ()
    {
        displacement_++;
        return *this;
    }

    ostream &ostream::operator-- ()
    {
        displacement_--;
        return *this;
    }

}
#endif //HOMEWORK_3_UTILS_H

//
// Created by svuatoslav on 3/29/17.
//

#ifndef EXCEPTIONS_GOOD_EXCEPTION_H
#define EXCEPTIONS_GOOD_EXCEPTION_H

#define RETBUFLEN 1024

#include <exception>
#include <string>

class good_exception: public std::exception
{
    char* what_;
public:
    good_exception(int errcode,const char* what,const char* where, good_exception* why=nullptr);

    virtual const char *what () const noexcept ;

    ~good_exception ();
};


#endif //EXCEPTIONS_GOOD_EXCEPTION_H

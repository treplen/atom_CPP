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
    int errcode_;
    std::string what_;
    std::string where_;
    static char ret_buffer[RETBUFLEN];
public:
    good_exception(int errcode,const char* what,const char* where);

    virtual const char *what () const noexcept ;
};


#endif //EXCEPTIONS_GOOD_EXCEPTION_H

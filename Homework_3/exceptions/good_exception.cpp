#include "good_exception.h"
#include <cstring>
#include <iostream>
#include <cassert>

int ilen(int val)
{
    long val_=val;
    int ret=0;
    if(val_<0)
    {
        ret++;
        val_*=-1;
    }
    ++val_;
    for(;val_!=0;val_/=10)
    {
        ++ret;
    }
    return ret;
}

char* itoa(int val)
{
    long val_ = val;
    int len = ilen (val);
    int first=0;
    char* ret = new char[len+1];
    ret[len] = 0;
    if(val_<0)
    {
        ret[0] = '-';
        val_*=-1;
        first++;
    }
    for(int i=len-1;i>=first;--i)
    {
        ret[i]=val_%10+'0';
        val_/=10;
    }
    return ret;
}

good_exception::good_exception (int errcode, const char *what, const char *where,good_exception* why)
{
    const char* prev = why== nullptr?"":why->what ();
    //%what (errcode = %errcode) in %where[ because:\n%why->what()]
    unsigned long len = strlen (what) + 12 + ilen(errcode) + 5 + strlen (where) + (why== nullptr?0:(10 + strlen (prev)));
    what_ = new(std::nothrow) char[len+1];
    if(what_== nullptr)
        return;
    what_[0]=0;
    strcat (what_,what);
    strcat (what_," (errcode = ");
    char* err = itoa (errcode);
    strcat (what_,err);
    delete[] err;
    strcat (what_,") in ");
    strcat (what_,where);
    if(why!= nullptr)
    {
        strcat (what_," because:\n");
        strcat (what_,why->what ());
    }
    assert(strlen (what_)==len);
}

const char *good_exception::what () const noexcept
{
    if(what_== nullptr)
        return "An error occurred while forming this exception :(";
    return what_;
}

good_exception::~good_exception ()
{
    delete what_;
}

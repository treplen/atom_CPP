#include "good_exception.h"
#include <cstring>

int ilen(int val)
{
    int ret=0;
    if(val<0)
    {
        ret++;
        val*=-1;
    }
    ++val;
    for(;val>0;val/=10)
    {
        ++ret;
    }
    return ret;
}

char* itoa(int val)
{
    int len = ilen (val);
    int first=0;
    char* ret = new char[len+1];
    ret[len] = 0;
    if(val<0)
    {
        ret[0] = '-';
        val*=-1;
        first++;
    }
    for(int i=len-1;i>=first;--i)
    {
        ret[i]=val%10+'0';
        val/=10;
    }
    return ret;
}

char good_exception::ret_buffer[RETBUFLEN] = "";

good_exception::good_exception (int errcode, const char *what, const char *where):errcode_(errcode),what_(what),where_(where)
{
}

const char *good_exception::what () const noexcept
{
    std::string ret;
    //%what (errcode = %errcode) in %where[ @ %address]
    unsigned long len = what_.length () + 12 + ilen(errcode_) + 5 + where_.length () + 1;
    ret.reserve (len);
    ret+=what_;
    ret+=" (errcode = ";
    char* errc = itoa (errcode_);
    ret+=errc;
    delete errc;
    ret+=") in ";
    ret += where_;
    if(ret.length ()+1>RETBUFLEN)
        return "Your exception is too long :(";
    strcpy (ret_buffer,ret.c_str ());
    return ret_buffer;
}

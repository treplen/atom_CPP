#include <iostream>
#include "good_exception.h"

int main ()
{
    good_exception e(INT32_MIN,"Error","Fishing");
    good_exception n(12,"Cthulhu summoned",__PRETTY_FUNCTION__,&e);
    std::cout<<n.what ();
    return 0;
}
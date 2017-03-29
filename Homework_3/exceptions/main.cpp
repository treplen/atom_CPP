#include <iostream>
#include "good_exception.h"

int main ()
{
    good_exception e(43,"Error",__PRETTY_FUNCTION__);
    std::cout<<e.what ();
    return 0;
}
#include "shared_ptr.h"

int main ()
{
    shared_ptr<int> a (new int);
    a.dump (utils::ostream (std::cout));
    return 0;
}
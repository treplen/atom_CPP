#include <iostream>
#include "VCPU.h"

int main ()
{
    VCPU CPU;
    std::ifstream in ("testout", std::ios_base::binary);
    CPU.load (in);
    in.close ();
    int value;
    std::cout << "Input a value to calculate factorial: ";
    std::cin >> value;
    CPU.push (value);
    int ret = CPU.execute ();
    if (ret)
        return ret;
    std::cout << CPU.pop ();
    return 0;
}
#include <iostream>

#include <Array.h>

int main()
{
    Array <int> a(20);
    for (int i=0; i<20; i++)
        a[i] = i;
    for (int i=0; i<20; i++)
        std::cout << a[i]<<std::endl;

    Array <bool> b(20);
    for (int i=0; i<20 ;i++)
        b[i]=false;
    b[10]=true;
    b[10]=false;
    for (int i=0; i<20; i++)
        std::cout << b[i]<<std::endl;
    std::cout << a.capacity()<<std::endl;
    std::cout << b.capacity()<<std::endl;

    for (Iterator<int> i=a.begin(); i!=a.end(); ++i){
        std::cout<<(*i)<<std::endl;
    }


    return 0;
}
#include <iostream>
#include <vector>
#include <Array.h>
int main(int argc, char** argv)
{
//    std::vector<int> v(23);
//
//    std::cout<<v.capacity();
//    std::cout<<v.size();
    Array <int> a;
    a.push_back(12);
    a.push_back(2);
    a.push_back(12);
    a.push_back(12);
    a.push_back(2);
    a.push_back(12);
    a.pop_back();
    a.pop_back();
    a.pop_back();
    std::cout<<a.size();
    std::cout<<a.capacity();
//    for (int i=0; i<20; i++)
//        a[i] = i;
//    for (int i=0; i<20; i++)
//        std::cout << a[i]<<std::endl;
//
//    Array <bool> b(20);
//    for (int i=0; i<20 ;i++)
//        b[i]=false;
//    b[10]=true;
//    b[10]=false;
//    for (int i=0; i<20; i++)
//        std::cout << b[i]<<std::endl;
//    std::cout << a.capacity()<<std::endl;
//    std::cout << b.capacity()<<std::endl;
//
//    for (Iterator<int> i=a.begin(); i!=a.end(); ++i){
//        std::cout<<(*i)<<std::endl;
//    }


    return 0;
}
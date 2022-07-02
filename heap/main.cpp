#include <iostream>
#include "heap.hpp"


int main(int argc, char const *argv[])
{
    heap<int> a;
    a.insert(25);
    a.insert(24);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    a.insert(24);
    a.insert(12);
    std::cout << "Pocetni heap" << std::endl;
    for (auto i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }

    std::cout << "\nMax "<<a.max() << std::endl;
    std::cout << "Min "<<a.min() << std::endl;
    std::cout << "Removing min"<<std::endl;
    a.removeMin();
        for (auto i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    a.removeMax();
    std::cout << "\nRemoving max" << std::endl;
         for (auto i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\nInorder print" << std::endl;
    std::cout << a << std::endl;

    std::cout << "Testiranje kontruktora,destruktora i operator=" << std::endl;
    std::cout << "a "<<a << std::endl;

    heap<int> b=a;
    std::cout << "b " <<b<< std::endl;
    heap<int>c;
    c=b;
    std::cout << "c "<<c << std::endl;
    heap<int>d;
    d=std::move(c);
    std::cout << "d "<<d << std::endl;
    return 0;
}

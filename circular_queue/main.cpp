#include <iostream>
#include "qeuecirc.hpp"
#include <queue>

void printaj(queue<int> &a)
{
    for (auto i = 0; i < a.capacity(); i++)
    {
        std::cout << a[i] << ',';
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    queue<int> a{10};
    queue<int> b{10};
    std::cout << "Test push()" << std::endl;
    for (auto i = 0; i < a.capacity(); i++)
    {
        a.push(i);
    }
    printaj(a);

    std::cout << "Test push()" << std::endl;
    for (auto i = 10; i > 0; --i)
    {
        b.push(i);
    }
    printaj(b);

    // std::cout << "Test pop()" << std::endl;
    // for (auto i = 0; i < a.capacity()/2; i++)
    // {
    //     a.pop();
    // }
    // printaj(a);

    // std::cout << "Test konstruktora" << std::endl;
    // std::cout << "A:" << std::endl;
    // printaj(a);
    // std::cout << "B(copy):" << std::endl;
    // queue<int> b{a};
    // printaj(b);
    // std::cout << "C(move)" << std::endl;
    // queue<int>c{std::move(b)};
    // printaj(c);


    // std::cout << "Test realokacija i cirkularnog buffera" << std::endl;
    // std::cout << "Realokacija" << std::endl;
    // for (auto i = 1; i < 7; i++)
    // {
    //     a.push(i);
    // }
    // printaj(a);
    // std::cout << "Cirkularni buffer" << std::endl;
    // for (auto i = 0; i < 6; i++)
    // {
    //    a.pop();
    // }
    // printaj(a);
    // std::cout << "Kada indeks izlaza stigne indeks ulaza onda se oni resetuju na 0 jer je red prazan" << std::endl;
    // for (auto i = 0; i < 5; i++)
    // {
    //     a.pop();
    // }
    // a.pop();
    // printaj(a);
    // a.push(4);
    // printaj(a);
    // std::cout << "Size:"<<a.size() << std::endl;
    // std::cout << "Capacity:"<<a.capacity() << std::endl;
    // std::cout << "Empty ispitivanje" << std::endl;
    // if (a.empty())std::cout << "a is empty" << std::endl;
    // else std::cout << "a is not empty" << std::endl;
    return 0;
}

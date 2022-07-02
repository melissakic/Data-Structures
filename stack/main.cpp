#include <iostream>
#include "stackniz.hpp"

int main(int argc, char const *argv[])
{
    stack<int>a;
    a.push(2);
    a.push(3);
    a.push(6);
    a.pop();
    std::cout << a.front() << std::endl;
        
    return 0;
}

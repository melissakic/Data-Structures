#include <iostream>
#include "list.hpp"

int main(int argc, char const *argv[])
{
    mojaLista<int> a{2, 5, 6, 1, 2, 5};
    auto c = a.begin();
    auto f = a.end();
    --f;
    --f;
    ++c;
    a.erase(c, f);
    std::cout << a.size() << std::endl;
    for (auto i : a)
    {
        std::cout << i << std::endl;
    }

    return 0;
}

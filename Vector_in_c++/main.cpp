#include "MojVektor.hpp"


int main(int argc, char const *argv[])
{
    MojVector<int> a{2,1,1};
    auto c=a.begin();
    auto f=&a;
    return 0;
}

#include <iostream>
#include "hash.hpp"

int main(int argc, char const *argv[])
{
    UnorderedMap<std::string, std::string> mapa;
    mapa.emplace("kljuc1", "vrijednost1");
    mapa.emplace("kljuc2", "vrijednost2");
    mapa.emplace("kljuc3", "vrijednost3");
    mapa.emplace("kljuc4", "vrijednost4");
    mapa.emplace("kljuc5", "vrijednost5");
    mapa["kljuc6"] = "vrijednost6";
    for (auto it = mapa.begin(); it != mapa.end(); ++it)
    {
        std::cout << "Key: " << it->first << ", value: " << it->second << std::endl;
    }
    mapa["kljuc1"] = "nova vrijednost1";
    auto it = mapa.find("kljuc1");
    if (it != mapa.end())
    {
        std::cout << "Element pronadjen: " << it->second << std::endl;
    }
    else
    {
        std::cout << "Element ne postoji" << std::endl;
    }

    for (auto i:mapa)
    {
       std::cout << i.second << " ";
    }
    
    return 0;
}

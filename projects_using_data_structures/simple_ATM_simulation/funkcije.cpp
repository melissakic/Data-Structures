#include "helper.hpp"


void Banka::nova_transakcija()
{
    time_t vrijeme = time(0);
    std::string dt = ctime(&vrijeme);
    int unos;
    std::cout << "Unesite iznos za transakciju" << std::endl;
    std::cin >> unos;
    transakcije.push(stanje(unos,dt));
}

void Banka::potvrdi_transakciju()
{
    if (transakcije.empty())
    {
        std::cout << "Nema transakcija na cekanju" << std::endl;
        return;
    }
    racun =racun + transakcije.front();
    transakcije.pop();
}

void Banka::trenutna_transakcija()
{
    if (transakcije.empty())
    {
        std::cout << "Nema transakcija na cekanju" << std::endl;
        return;
    }
    std::cout << transakcije.front().iznos_<<"KM"<<" "<<transakcije.front().vrijeme_<< std::endl;
}

void Banka::odbaci()
{
    if (transakcije.empty())
    {
        std::cout << "Nema transakcija na cekanju" << std::endl;
        return;
    }
    transakcije.pop();
}

void Banka::stanjeracuna(){
    std::cout << racun.iznos_<<"KM" << std::endl;
}
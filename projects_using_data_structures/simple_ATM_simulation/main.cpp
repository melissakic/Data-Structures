#include <queue>
#include <iostream>
#include <string>
#include <ctime>
#include "helper.hpp"

int main(void)
{
    Banka mojracun;
    int izbor;
    while (1)
    {
        std::cout << "****************************************************" << std::endl;
        std::cout << "Odabiri" << std::endl;
        std::cout << "          1.Nova transakcija" << std::endl;
        std::cout << "          2.Potvrdi transakciju" << std::endl;
        std::cout << "          3.Trenutna transakcija" << std::endl;
        std::cout << "          4.Odbaci posljednju transakciju" << std::endl;
        std::cout << "          5.Stanje racuna" << std::endl;
        std::cout << "          6.Izlaz" << std::endl;
        std::cout << "Unos:";
        std::cin >> izbor;
        switch (izbor)
        {
        case 1:
            mojracun.nova_transakcija();
            break;
        case 2:
            mojracun.potvrdi_transakciju();
            break;
        case 3:
            mojracun.trenutna_transakcija();
            break;
        case 4:
            mojracun.odbaci();
            break;
        case 5:
            mojracun.stanjeracuna();
            break;
        }
        if (izbor==6)break;
    }

    return 0;
}

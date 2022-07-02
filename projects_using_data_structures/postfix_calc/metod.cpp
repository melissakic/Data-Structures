#include "helper.hpp"

void PostfixCalc::calculate()
{
    std::string izraz;
    std::getline(std::cin, izraz);

    for (char i : izraz)
    {
        if (i == ' ')
            continue;

        if (i == '+' || i == '-' || i == '*' || i == '/')
        {
            if (stek.size() < 2)
            { 
                std::cout << "nevalidan unos pokusajte ponovo" << std::endl;
                return;
            }
            int temp = stek.top();
            stek.pop();
            switch (i)
            {
            case '+':
                stek.top() = stek.top() + temp;
                break;
            case '-':
                stek.top() = stek.top() - temp;
                break;
            case '*':
                stek.top() = stek.top() * temp;
                break;
            case '/':
                stek.top() = stek.top() / temp;
                break;
            }
            continue;
        }
        stek.push(i - '0');
    }

    if (stek.size() > 1)
    {
        std::cout << "nevalidan unos pokusajte ponovo" << std::endl;
        return;
    }
    std::cout << stek.top() << std::endl;
}
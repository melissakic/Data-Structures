#include <iostream>
#include <stack>

bool hijerarhija(char , char);
bool otvorena_zagrada(char);
bool zatvorena_zagrada(char);
bool podudarne_zagrade(char, char);

int main()
{
    std::stack<char> zagrade;
    bool valid = true;
    char c;
    while (std::cin >> c)
    {
        if (zagrade.empty())
        {
            if (otvorena_zagrada(c))
                zagrade.push(c);
            else if (zatvorena_zagrada(c))
            {
                valid = false;
                break;
            }
        }
        else if (otvorena_zagrada(c))
        {
            if (hijerarhija(c, zagrade.top()))
                zagrade.push(c);
            else
            {
                valid = false;
                break;
            }
        }
        else if (zatvorena_zagrada(c))
        {

            if (podudarne_zagrade(zagrade.top(), c))
            {
                zagrade.pop();
            }
            else
            {
                valid = false;
                break;
            }
        }
    }

    if (zagrade.empty() && valid)
        std::cout << "dobar" << std::endl;
    else
        std::cout << "nece moci" << std::endl;
    return 0;
}

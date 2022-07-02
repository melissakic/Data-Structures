#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <list>

class PostfixCalc
{
private:
    std::stack<int> stek;

public:
    void calculate();
};
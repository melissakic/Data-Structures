bool hijerarhija(char c, char top)
{
    if (top == '<' || top == '(')
    {
        if (c == '<')
            return true;
        else
            return false;
    }
    else if (top == '[')
    {
        if (c == '<' || c == '(')
            return true;
        else
            return false;
    }
    else if (top == '{')
        return true;
    else
        false;
    return false;
}

bool otvorena_zagrada(char c)
{
    return c == '(' || c == '[' || c == '<' || c == '{';
}

bool zatvorena_zagrada(char c)
{
    return c == ')' || c == ']' || c == '>' || c == '}';
}

bool podudarne_zagrade(char l, char r)
{
    return (l == '(' && r == ')') || (l == '[' && r == ']') || (l == '<' && r == '>') || (l == '{' && r == '}');
}

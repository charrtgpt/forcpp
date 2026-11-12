
#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {}
    return (*this);
}

RPN::~RPN()
{}

int RPN::calculate(const std::string &expression) const
{
    std::stack<int> numbers;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.length() == 1 &&
            token[0] >= '0' && token[0] <= '9')
        {
            numbers.push(token[0] - '0');
        }
        else if (token == "+" || token == "-" ||
                 token == "*" || token == "/")
        {
            if (numbers.size() < 2)
                throw std::runtime_error("Error");

            int b = numbers.top();
            numbers.pop();

            int a = numbers.top();
            numbers.pop();

            int result;

            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else
            {
                if (b == 0)
                    throw std::runtime_error("Error");
                result = a / b;
            }

            numbers.push(result);
        }
        else
            throw std::runtime_error("Error");
    }

    if (numbers.size() != 1)
        throw std::runtime_error("Error");
    return numbers.top();
}

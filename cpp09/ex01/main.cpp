
#include "RPN.hpp"
#include <iostream>
#include <exception>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try
    {
        RPN calculator;

        int result = calculator.calculate(av[1]);

        std::cout << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }

    return (0);
}

#include "span.hpp"
#include <iostream>
#include <vector>

int main()
{
    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << '\n';
    std::cout << sp.longestSpan() << '\n';

    Span p(10);
     
    std::vector<int> numbers;

    numbers.push_back(6);
    numbers.push_back(3);
    numbers.push_back(17);
    numbers.push_back(9);
    numbers.push_back(12);


    p.addRange(numbers.begin(), numbers.end());

    std::cout << "Shortest span: " << p.shortestSpan() << std::endl;
    std::cout << "Longest span: " << p.longestSpan() << std::endl;

    return 0;
}

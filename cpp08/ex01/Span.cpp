#include "Span.hpp"
#include <algorithm>


Span::Span(unsigned int n) : maxSize(n)
{
}

Span::Span(const Span &other)
        : numbers(other.numbers), maxSize(other.maxSize) 
{
}

Span &Span::operator=(const Span &other)
{
    if(this != &other)
    {
        numbers = other.numbers;
        maxSize = other.maxSize;
    }
    return *this;
}

Span::~Span()
{}

void Span::addNumber(int number)
{
    if(numbers.size() >= maxSize)
        throw std::runtime_error("error: span is full");
    
    numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
    if (numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to calculate a span");

    std::vector<int> sorted(numbers);

    std::sort(sorted.begin(), sorted.end());

    unsigned int shortest =
        static_cast<unsigned int>(sorted[1]) -
        static_cast<unsigned int>(sorted[0]);

    for (std::size_t i = 1; i < sorted.size() - 1; i++)
    {
        unsigned int distance =
            static_cast<unsigned int>(sorted[i + 1]) -
            static_cast<unsigned int>(sorted[i]);

        if (distance < shortest)
            shortest = distance;
    }

    return shortest;
}

unsigned int Span::longestSpan() const
{
    if (numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to calculate a span");

    std::vector<int>::const_iterator minIt =
        std::min_element(numbers.begin(), numbers.end());

    std::vector<int>::const_iterator maxIt =
        std::max_element(numbers.begin(), numbers.end());

    return static_cast<unsigned int>(*maxIt) -
           static_cast<unsigned int>(*minIt);
}


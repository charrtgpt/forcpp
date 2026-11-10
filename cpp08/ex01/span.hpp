
#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>

class Span
{
private:
    std::vector<int> numbers;
    unsigned int maxSize;

public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int number);

    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

    template <typename Iterator>
    void addRange(Iterator first, Iterator last);
};

template <typename Iterator>
void Span::addRange(Iterator first, Iterator last)
{
    while (first != last)
    {
        addNumber(*first);
        ++first;
    }
}

#endif


#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>

class Span
{
private:
    std::vector<int> _numbers;
    unsigned int _maxSize;

public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int number);

    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;
};

#endif

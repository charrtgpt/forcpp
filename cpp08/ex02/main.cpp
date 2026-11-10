
#include "MutantStack.hpp"
#include <iostream>

int main()
{
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);
    mstack.push(18);

    std::cout << "Top: " << mstack.top() << std::endl;

    std::cout << "Size: " << mstack.size() << std::endl;

    MutantStack<int>::iterator it;

    for (it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}
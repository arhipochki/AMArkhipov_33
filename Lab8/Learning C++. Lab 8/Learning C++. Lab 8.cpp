#include <iostream>
#include <string>

#include "DoubleLinkedList.h"

int main()
{
    int size = 10;
    DoubleLinkedList<int> dll;

    std::cout << "Is dll empty?: " << (dll.empty() ? "true" : "false") << "\n";

    for (int i = 0; i < size; i++)
        dll.push_back(i);

    dll.push_front(dll.back() + dll.front() + 2);

    for (auto el : dll)
        el *= 2;

    std::cout << "Current dll size and elements: " << dll.size() << "\n";
    for (auto el : dll)
        std::cout << el << "\n";

    dll.pop_back(); dll.pop_front();

    std::cout << "After pops:\n";
    for (auto it = dll.begin(); it != dll.end(); it++)
        std::cout << it << "\n";

    std::cout << "After pops reversed:\n";
    for (auto it = dll.rbegin(); it != dll.rend(); it++)
        std::cout << it << "\n";

    DoubleLinkedList<std::string> s_dll;

    for (int i = 0; i < size; i++)
        s_dll.push_back(std::to_string(i * 2));

    std::cout << "Current s_dll:\n";
    for (auto el : s_dll)
        std::cout << el << "\n";

    s_dll.pop_back(); s_dll.pop_front();

    std::cout << "After pops:\n";
    for (auto it = s_dll.begin(); it != s_dll.end(); it++)
        std::cout << it << "\n";

    std::cout << "After pops reversed:\n";
    for (auto it = s_dll.rbegin(); it != s_dll.rend(); it++)
        std::cout << it << "\n";

    return 0;
}
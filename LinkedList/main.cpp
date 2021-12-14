#include <iostream>

#include "LinkedList.hpp"
#include "LinkedList.cpp"

void print(const List<int> &list)
{
    for (auto &element : list)
    {
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

int main()
{
    List<int> list;

    std::cout << list.is_empty() << std::endl;

    for (int i = 0; i < 20; i++)
    {
        list.push_front(i);
    }

    print(list);

    std::cout << list.is_empty() << std::endl;
    std::cout << list.size() << std::endl;

    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;

    list.clear();

    std::cout << list.is_empty() << std::endl;

    for (int i = 0; i < 20; i++)
    {
        list.push_back(i);
    }

    print(list);

    std::cout << list[11] << std::endl;
    std::cout << list[18] << std::endl;

    for (int i = 0; i < 5; i++)
    {
        list.pop_back();
    }

    print(list);

    for (int i = 0; i < 5; i++)
    {
        list.pop_front();
    }

    print(list);

    list.remove(11);

    print(list);

    list.reverse();

    print(list);

    return 0;
}

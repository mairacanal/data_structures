#include <iostream>

#include "Vector.hpp"
#include "Vector.cpp"

void print(Vector<int> &vector)
{
    for (auto &element : vector)
    {
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

int main()
{
    Vector<int> vector;

    std::cout << vector.capacity() << std::endl;
    std::cout << vector.is_empty() << std::endl;

    for (int i = 0; i < 40; i++)
    {
        vector.push(i);
    }

    print(vector);

    std::cout << vector.capacity() << std::endl;
    std::cout << vector.is_empty() << std::endl;

    for (int i = 20; i < 30; i++)
    {
        vector.prepend(i);
    }

    print(vector);

    std::cout << vector.find(10) << std::endl;
    std::cout << vector.find(28) << std::endl;
    std::cout << vector.find(100) << std::endl;

    vector.insert(100, 20);

    print(vector);

    for (int i = 0; i < 35; i++)
    {
        vector.pop();
    }

    print(vector);

    vector.drop(10);

    print(vector);

    vector.remove(20);

    print(vector);

    return 0;

}

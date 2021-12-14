#include <iostream>
#include "array.hpp"

int main() {

    Array<int, 8> array;

    for (int i = 0; i < array.size(); i++) {
        array[i] = i;
    }

    for (int element : array) {
        std::cout << element << std::endl;
    }

    for (Array<int, 8>::iterator it = array.begin(); it != array.end(); it++) {
        std::cout << *it << std::endl;
    }

}

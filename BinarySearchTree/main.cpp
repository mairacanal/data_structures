#include "BinarySearchTree.h"
#include <random>

int main() {

    BinarySearchTree<int> tree{};

    std::cout << "Is empty? ";
    std::cout << tree.isEmpty() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    std::array<int, 10> numbers {23, 2, 5, 9, 10, 3, 8, 73, 45, 21};
    for (int i = 0; i < 10; i++)
        tree.insert(numbers[i]);

    tree.print();

    std::cout << "Is empty? ";
    std::cout << tree.isEmpty() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    std::cout << "Min value: ";
    std::cout << tree.findMin() << std::endl;

    std::cout << "Max value: ";
    std::cout << tree.findMax() << std::endl;

    tree.remove(8);
    tree.remove(23);

    tree.print();

    std::cout << "Min value: ";
    std::cout << tree.findMin() << std::endl;

    std::cout << "Max value: ";
    std::cout << tree.findMax() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    std::cout << "Element 23 exists? ";
    std::cout << tree.find(23) << std::endl;

    std::cout << "Element 1 exists? ";
    std::cout << tree.find(1) << std::endl;

    std::cout << "Precessor of element 3: ";
    std::cout << tree.prev(3) << std::endl;

    std::cout << "Sucessor of element 3: ";
    std::cout << tree.next(3) << std::endl;

    std::cout << "Sucessor of element 45: ";
    std::cout << tree.next(45) << std::endl;

    BinarySearchTree<int> clone{tree};

    clone.print();

    tree.empty();

    std::cout << "Is empty? ";
    std::cout << tree.isEmpty() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    clone.print();

}

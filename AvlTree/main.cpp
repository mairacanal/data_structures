#include "AvlTree.h"

int main()
{
    AvlTree<int> tree {};

    std::cout << "Is empty? ";
    std::cout << tree.isEmpty() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    for (int i = 1; i <= 10; i++)
        tree.insert(i);

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

    tree.print();

    std::cout << "Min value: ";
    std::cout << tree.findMin() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    std::cout << "Element 23 exists? ";
    std::cout << tree.find(23) << std::endl;

    std::cout << "Element 1 exists? ";
    std::cout << tree.find(1) << std::endl;

    std::cout << "Sucessor of element 7: ";
    std::cout << tree.next(7) << std::endl;

    std::cout << "Sucessor of element 1: ";
    std::cout << tree.next(1) << std::endl;

    AvlTree<int> clone { tree };

    clone.print();

    tree.empty();

    std::cout << "Is empty? ";
    std::cout << tree.isEmpty() << std::endl;

    std::cout << "Size: ";
    std::cout << tree.getCount() << std::endl;

    clone.print();
}

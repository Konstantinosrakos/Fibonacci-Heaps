#include "Utilities.h"
#include <iostream>

// Implementation of the printTree method
void Utilities::printTree(Node* node, int depth) const{
    if (node == nullptr) {
        return;
    }

    // Print the current node with indentation based on the depth
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << node->getKey() << " (Degree: " << node->getDegree() << ", Marked: " << (node->getMark() ? "true" : "false") << ")" << std::endl;

    // Recursively print each child with increased depth
    Node* child = node->getChild();
    if (child != nullptr) {
        Node* startChild = child;
        do {
            printTree(child, depth + 1); // Call the private method
            child = child->getRight();
        } while (child != startChild);
    }
}

// Implementation of the printHeap method
void Utilities::printHeap(FibonacciHeap* heap) const{
    if (heap->getMinNode() == nullptr) {
        std::cout << "The heap is empty." << std::endl;
        return;
    }

    std::cout << "Fibonacci Heap:" << std::endl;
    std::cout << "Number of nodes:" << heap->getSize() << std::endl;

    Node* current = heap->getMinNode();
    if (current != nullptr) {
        Node* start = current;
        do {
            printTree(current);
            current = current->getRight();
        } while (current != start);
    }
    std::cout << "\n\n\n\n";
}

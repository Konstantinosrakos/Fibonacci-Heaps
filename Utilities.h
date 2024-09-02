#pragma once
#include "FibonacciHeap.h" 
/**
 * @class Utilities
 * @brief Provides utilites function on the heap that do not alterate
 * it in any way.
 */
class Utilities {
public:
    // Public method to print the heap
    void printHeap(FibonacciHeap* heap) const;

private:
    // Private method to recursively print the tree
    void printTree(Node* node, int depth = 0) const;
};

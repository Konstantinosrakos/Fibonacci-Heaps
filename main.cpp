#include "Node.h"
#include "Utilities.h"
#include "FibonacciHeap.h"
#include <iostream>

int main() {
    // Create a new Fibonacci Heap
    FibonacciHeap* heap = new FibonacciHeap();
    Utilities* utility = new Utilities();
    // Insert nodes into the Fibonacci Heap
    heap->insert(10);
    heap->insert(20);
    heap->insert(5);
    heap->insert(15);

    std::cout << "Inserted nodes with values 10, 20, 5, 15." << std::endl;
    std::cout << "Current minimum value: " << heap->getMinValue() << std::endl;

    // Extract the minimum node
    Node* minNode = heap->extractMin();
    std::cout << "Extracted the minimum node with value: " << minNode->getKey() << std::endl;
    delete minNode; // Free the memory of the extracted node

    std::cout << "New minimum value after extraction: " << heap->getMinValue() << std::endl;
    std::cout << "\nHeap structure at the moment:" << std::endl;
    utility->printHeap(heap);
    // Decrease key of an existing node
    Node* node20 = heap->getMinNode()->getRight(); // assuming this is the node with value 20
    heap->decreaseKey(node20, 2);

    std::cout << "Decreased key of node with original value 20 to 2." << std::endl;
    std::cout << "Current minimum value: " << heap->getMinValue() << std::endl;
    std::cout << "\nHeap structure at the moment:" << std::endl;
    utility->printHeap(heap);
    // Delete a node from the heap
    Node* node15 = heap->getMinNode()->getRight(); // assuming this is the node with value 15
    heap->deleteNode(node15);

    std::cout << "Deleted a node from the heap." << std::endl;
    std::cout << "Current minimum value: " << heap->getMinValue() << std::endl;
    std::cout << "\nHeap structure at the moment:" << std::endl;
    utility->printHeap(heap);
    // Create another heap and merge with the current heap
    FibonacciHeap* anotherHeap = new FibonacciHeap();
    anotherHeap->insert(25);
    anotherHeap->insert(30);

    std::cout << "Created another heap and inserted nodes with values 25, 30." << std::endl;

    heap->unionHeap(anotherHeap);

    std::cout << "Merged the two heaps." << std::endl;
    std::cout << "Current minimum value after merging: " << heap->getMinValue() << std::endl;
    std::cout << "\nHeap structure at the moment:" << std::endl;
    utility->printHeap(heap);
    // Clean up the heap
    delete heap;  // This will also delete all nodes within the heap
    delete utility;
    std::cout << "Heap deleted successfully." << std::endl;

   
    return 0;
}





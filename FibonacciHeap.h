#pragma once
#include "Node.h"

/**
 * @class FibonacciHeap
 * @brief A Fibonacci Heap data structure.
 *
 * A Fibonacci Heap is a priority queue data structure that supports
 * a variety of operations, including insertion, extracting the minimum,
 * decreasing key values, and merging heaps.
 */
class FibonacciHeap
{
private:
    Node* minNode;    ///< Pointer to the minimum node in the heap
    int numNodes;     ///< Total number of nodes in the heap

    /**
     * @brief Restructures the heap after an operation to maintain the heap property.
     *
     * This method consolidates trees of the same degree to ensure that there is only
     * one tree of each degree in the heap.
     */
    void consolidate();

    /**
     * @brief Links two nodes during consolidation.
     *
     * This method links node y as a child of node x. It is used during the
     * consolidation process to ensure the heap property is maintained.
     *
     * @param y The node to be linked.
     * @param x The node to which y will be linked.
     */
    void link(Node* y, Node* x);

    /**
     * @brief Cuts node x from its parent y.
     *
     * This method removes node x from its parent y and adds it to the root list.
     * It is used in the cut operation and as part of the cascading cut process.
     *
     * @param x The node to be cut.
     * @param y The parent node from which x is to be cut.
     */
    void cut(Node* x, Node* y);

    /**
     * @brief Performs a cascading cut on the parent node y.
     *
     * This method recursively cuts nodes from their parents if necessary.
     * It is part of the cascading cut process used to maintain the heap properties.
     *
     * @param y The parent node on which to perform the cascading cut.
     */
    void cascadingCut(Node* y);

    /**
     * @brief Decreases the degree of the heap.
     *
     * This method is called when the degree of a node needs to be decreased.
     */
    void decreaseDegree();

    /**
     * @brief Sets the pointer to the minimum node in the heap.
     *
     * This method updates the pointer to the node with the smallest key.
     *
     * @param sNode A pointer to the new minimum node.
     */
    void setMinNode(Node* sNode);

    /**
     * @brief Deletes all nodes starting from the given node.
     *
     * This method recursively frees all nodes in the heap starting from the specified node.
     *
     * @param node The starting node for deletion.
     */
    void deleteAllNodes(Node* node);
public:
    /**
     * @brief Constructs a Fibonacci Heap.
     */
    FibonacciHeap();

    /**
     * @brief Destroys the Fibonacci Heap.
     *
     * This destructor frees all nodes in the heap to avoid memory leaks.
     */
    ~FibonacciHeap();

    /**
     * @brief Inserts a new node with the given value into the heap.
     *
     * This method creates a new node with the specified value and adds it to the heap.
     *
     * @param value The value of the new node.
     */
    void insert(int value);

    /**
     * @brief Removes and returns the node with the minimum key.
     *
     * This method extracts the node with the smallest key from the heap and restructures
     * the heap accordingly.
     *
     * @return Node* The node with the minimum key.
     */
    Node* extractMin();

    /**
     * @brief Decreases the key of a given node.
     *
     * This method updates the key of a specified node to a new, smaller value.
     *
     * @param x The node whose key is to be decreased.
     * @param newKey The new, smaller key value.
     */
    void decreaseKey(Node* x, int newKey);

    /**
     * @brief Deletes a given node from the heap.
     *
     * This method removes a specified node from the heap and restructures the heap.
     *
     * @param x The node to be deleted.
     */
    void deleteNode(Node* x);

    /**
     * @brief Merges another Fibonacci heap with this one.
     *
     * This method combines the contents of another Fibonacci heap with the current heap.
     *
     * @param otherHeap The other Fibonacci heap to be merged with this one.
     */
    void unionHeap(FibonacciHeap* otherHeap);

    /**
     * @brief Checks if the heap is empty.
     *
     * This method determines whether the heap contains any nodes.
     *
     * @return True if the heap is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the minimum value in the heap.
     *
     * This method retrieves the value of the node with the smallest key.
     *
     * @return int The minimum value in the heap.
     */
    int getMinValue() const;

    /**
     * @brief Returns the number of nodes in the heap.
     *
     * This method provides the total count of nodes currently in the heap.
     *
     * @return int The number of nodes in the heap.
     */
    int getSize() const;

    /**
     * @brief Gets the pointer to the minimum node in the heap.
     *
     * This method retrieves the node with the smallest key in the heap.
     *
     * @return Node* A pointer to the minimum node.
     */
    Node* getMinNode() const;

};

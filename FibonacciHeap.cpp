#include "FibonacciHeap.h"
#include <cmath>
#include <unordered_map>
#include <iostream>

/**
 * @brief Restructures the heap after an operation to maintain the heap property.
 */
void FibonacciHeap::consolidate() {
    int maxDegree = int(std::log(this->getSize()) / std::log(2)) + 1;

    std::unordered_map<int, Node*> degreeTable;

    Node* startNode = this->getMinNode();
    Node* currentNode = startNode;

    do {
        Node* x = currentNode;
        int d = x->getDegree();
        Node* nextNode = currentNode->getRight();

        while (degreeTable.find(d) != degreeTable.end()) {
            Node* y = degreeTable[d];
            if (x->getKey() > y->getKey()) {
                std::swap(x, y);
            }
            x->link(y);
            degreeTable.erase(d);
            d += 1;
        }
        degreeTable[d] = x;
        currentNode = nextNode;

    } while (currentNode != startNode);

    this->setMinNode(nullptr);

    for (const auto& entry : degreeTable) {
        Node* node = entry.second;
        if (node != nullptr) {
            if (this->getMinNode() == nullptr) {
                this->setMinNode(node);
                node->setRight(node);
                node->setLeft(node);
            }
            else {
                node->setLeft(this->getMinNode());
                node->setRight(this->getMinNode()->getRight());
                this->getMinNode()->getRight()->setLeft(node);
                this->getMinNode()->setRight(node);

                if (this->getMinNode()->getKey() > node->getKey()) {
                    this->setMinNode(node);
                }
            }
        }
    }
}

/**
 * @brief Links two nodes during consolidation.
 *
 * @param y The node to be linked.
 * @param x The node to which y will be linked.
 */
void FibonacciHeap::link(Node* y, Node* x) {
    y->setLeft(y);
    y->setRight(y);
    y->setParent(x);

    if (x->getChild() == nullptr) {
        x->setChild(y);
    }
    else {
        Node* xChild = x->getChild();
        y->setRight(xChild);
        y->setLeft(xChild->getLeft());
        xChild->getLeft()->setRight(y);
        xChild->setLeft(y);
    }

    x->incrementDegree();
    y->setMark(false);
}

/**
 * @brief Cuts node x from its parent y.
 *
 * @param x The node to be cut.
 * @param y The parent node from which x is to be cut.
 */
void FibonacciHeap::cut(Node* x, Node* y) {
    y->removeChild(x);
    this->getMinNode()->addSibling(x);
    x->setMark(false);
}

/**
 * @brief Performs a cascading cut on the parent node y.
 *
 * @param y The parent node on which to perform the cascading cut.
 */
void FibonacciHeap::cascadingCut(Node* y) {
    Node* zNode = y->getParent();
    if (zNode != nullptr) {
        if (!zNode->getMark()) {
            zNode->setMark(true);
        }
        else {
            this->cut(y, zNode);
            this->cascadingCut(zNode);
        }
    }
}

/**
 * @brief Decreases the degree of the heap.
 */
void FibonacciHeap::decreaseDegree() {
    this->numNodes -= 1;
}

/**
 * @brief Constructs a Fibonacci Heap.
 */
FibonacciHeap::FibonacciHeap() : minNode(nullptr), numNodes(0) {}

/**
 * @brief Destroys the Fibonacci Heap.
 */
FibonacciHeap::~FibonacciHeap() {
    if (minNode != nullptr) {
        deleteAllNodes(minNode);
    }
}

/**
 * @brief Inserts a new node with the given value into the heap.
 *
 * @param value The value of the new node.
 */
void FibonacciHeap::insert(int value) {
    Node* newNode = new Node(value);

    if (this->minNode == nullptr) {
        this->minNode = newNode;
    }
    else {
        newNode->setRight(this->minNode);
        newNode->setLeft(this->minNode->getLeft());
        this->minNode->getLeft()->setRight(newNode);
        this->minNode->setLeft(newNode);

        if (newNode->getKey() < this->minNode->getKey()) {
            this->minNode = newNode;
        }
    }

    this->numNodes += 1;
}

/**
 * @brief Merges another Fibonacci heap with this one.
 *
 * @param otherHeap The other Fibonacci heap to be merged with this one.
 */
void FibonacciHeap::unionHeap(FibonacciHeap* otherHeap) {
    if (otherHeap == nullptr || otherHeap->isEmpty()) {
        return;
    }

    if (this->isEmpty()) {
        this->setMinNode(otherHeap->getMinNode());
        this->numNodes = otherHeap->numNodes;
    }
    else {
        Node* thisRight = this->getMinNode()->getRight();
        Node* otherLeft = otherHeap->getMinNode()->getLeft();

        this->getMinNode()->setRight(otherHeap->getMinNode());
        otherHeap->getMinNode()->setLeft(this->getMinNode());

        thisRight->setLeft(otherLeft);
        otherLeft->setRight(thisRight);

        if (otherHeap->getMinValue() < this->getMinValue()) {
            this->setMinNode(otherHeap->getMinNode());
        }

        this->numNodes += otherHeap->numNodes;
    }

    otherHeap->minNode = nullptr;
    otherHeap->numNodes = 0;
    delete otherHeap;
}

/**
 * @brief Removes and returns the node with the minimum key.
 *
 * @return Node* The node with the minimum key.
 */
Node* FibonacciHeap::extractMin() {
    Node* zNode = this->getMinNode();
    if (zNode != nullptr) {
        Node* zChild = zNode->getChild();
        while (zChild != nullptr ) {
            Node* nextChild = zChild->getRight();
            zNode->removeChild(zChild);
            zNode->addSibling(zChild);
            
            if (zChild == nextChild)
            {
                break;
            }
            zChild = nextChild;
        }

        Node* leftSibling = zNode->getLeft();
        Node* rightSibling = zNode->getRight();
        leftSibling->setRight(rightSibling);
        rightSibling->setLeft(leftSibling);

        if (zNode == zNode->getRight()) {
            this->setMinNode(nullptr);
        }
        else {
            this->setMinNode(rightSibling);
            this->consolidate();
        }
        this->decreaseDegree();
    }
    return zNode;
}

/**
 * @brief Decreases the key of a given node.
 *
 * @param x The node whose key is to be decreased.
 * @param newKey The new, smaller key value.
 */
void FibonacciHeap::decreaseKey(Node* x, int newKey) {
    if (newKey > x->getKey()) {
        std::cout << "Decreasing the key failed, because the new key is greater than the current key.\n";
        return;
    }
    x->setKey(newKey);
    Node* xParent = x->getParent();
    
    if (xParent != nullptr) {
        if (x->getKey() < xParent->getKey()) {
            this->cut(x, xParent);
            this->cascadingCut(xParent);
        }
    }
    if (x->getKey() < this->getMinNode()->getKey()) {
        this->setMinNode(x);
    }
}

/**
 * @brief Deletes a given node by decreasing the key to -1 assuming
 * all values are positive.
 *
 * @param x The node that will be deleted.
 */
void FibonacciHeap::deleteNode(Node* x)
{
    this->decreaseKey(x, -1);
    delete this->extractMin();
    return;
}

/**
 * @brief Checks if the heap is empty.
 *
 * @return True if the heap is empty, false otherwise.
 */
bool FibonacciHeap::isEmpty() const {
    return this->minNode == nullptr;
}

/**
 * @brief Returns the minimum value in the heap.
 *
 * @return int The minimum value in the heap.
 */
int FibonacciHeap::getMinValue() const {
    return this->getMinNode()->getKey();
}

/**
 * @brief Returns the number of nodes in the heap.
 *
 * @return int The number of nodes in the heap.
 */
int FibonacciHeap::getSize() const {
    return this->numNodes;
}

/**
 * @brief Gets the pointer to the minimum node in the heap.
 *
 * @return Node* A pointer to the minimum node.
 */
Node* FibonacciHeap::getMinNode() const {
    return this->minNode;
}

/**
 * @brief Sets the pointer to the minimum node in the heap.
 *
 * @param sNode A pointer to the new minimum node.
 */
void FibonacciHeap::setMinNode(Node* sNode) {
    this->minNode = sNode;
}

/**
 * @brief Deletes all nodes starting from the given node.
 *
 * @param node The starting node for deletion.
 */
void FibonacciHeap::deleteAllNodes(Node* node) {
    if (node == nullptr) return;

    Node* start = node;
    do {
        Node* next = node->getRight();
        if (node->getChild() != nullptr) {
            deleteAllNodes(node->getChild());
        }
        delete node;
        node = next;
    } while (node != start);
}

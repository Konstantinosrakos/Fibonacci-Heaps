#include "Node.h"

/**
 * @brief Constructs a new Node with the given value.
 *
 * @param value The key/value of the node.
 */
Node::Node(int value)
    : key(value), parent(nullptr), child(nullptr),
    left(this), right(this), degree(0), marked(false) {}

/**
 * @brief Returns the key/value of the node.
 *
 * @return int The key of the node.
 */
int Node::getKey() const {
    return key;
}

/**
 * @brief Sets the key/value of the node.
 *
 * @param newKey The new key of the node.
 */
void Node::setKey(int newKey)
{
    this->key = newKey;
}

/**
 * @brief Sets the parent of the node.
 *
 * @param sParent Pointer to the parent node.
 */
void Node::setParent(Node* sParent) {
    this->parent = sParent;
}

/**
 * @brief Returns the parent of the node.
 *
 * @return Node* The parent node.
 */
Node* Node::getParent() const {
    return parent;
}

/**
 * @brief Returns the child of the node.
 *
 * @return Node* The child node.
 */
Node* Node::getChild() const {
    return child;
}

/**
 * @brief Sets the child of the node.
 *
 * @param sChild Pointer to the child node.
 */
void Node::setChild(Node* sChild) {
    this->child = sChild;
}

/**
 * @brief Sets the left sibling of the node.
 *
 * @param sLeft Pointer to the left sibling node.
 */
void Node::setLeft(Node* sLeft) {
    this->left = sLeft;
}

/**
 * @brief Returns the left sibling of the node.
 *
 * @return Node* The left sibling node.
 */
Node* Node::getLeft() const {
    return left;
}

/**
 * @brief Sets the right sibling of the node.
 *
 * @param sRight Pointer to the right sibling node.
 */
void Node::setRight(Node* sRight) {
    this->right = sRight;
}

/**
 * @brief Returns the right sibling of the node.
 *
 * @return Node* The right sibling node.
 */
Node* Node::getRight() const {
    return right;
}

/**
 * @brief Increments the degree of the node.
 */
void Node::incrementDegree()
{
    this->degree += 1;
}

/**
 * @brief Decreases the degree of the node and marks it if it loses a child.
 */
void Node::decreaseDegree()
{
    this->degree -= 1;
    this->marked = true;
}

/**
 * @brief Returns the mark status of the node.
 *
 * @return bool True if the node is marked, false otherwise.
 */
bool Node::getMark() const {
    return this->marked;
}

/**
 * @brief Sets the mark status of the node.
 *
 * @param mark The mark status to be set.
 */
void Node::setMark(bool mark) {
    this->marked = mark;
}

/**
 * @brief Returns the degree of the node.
 *
 * @return int The degree of the node (number of children).
 */
int Node::getDegree() const {
    return this->degree;
}

/**
 * @brief Adds a sibling to the right of this node.
 *
 * @param newSibling Pointer to the new sibling node.
 */
void Node::addSibling(Node* newSibling) {
    newSibling->setLeft(this);
    newSibling->setRight(this->getRight());
    (this->getRight())->setLeft(newSibling);
    this->setRight(newSibling);
    newSibling->setParent(this->getParent());
}

/**
 * @brief Adds a child to this node.
 *
 * @param newChild Pointer to the new child node.
 */
void Node::addChild(Node* newChild)
{
    newChild->setParent(this);
    if (this->child == nullptr) {
        // If this node has no children, the new child becomes the only child
        this->child = newChild;
        newChild->setLeft(newChild);
        newChild->setRight(newChild);
    }
    else {
        // If this node already has children, insert the new child into the child list
        Node* firstChild = this->getChild();
        Node* lastChild = firstChild->getLeft();

        lastChild->setRight(newChild);
        newChild->setLeft(lastChild);
        newChild->setRight(firstChild);
        firstChild->setLeft(newChild);
    }
    // Increase the degree of this node since it now has an additional child
    this->incrementDegree();

    // Mark node false as it is made a child node
    newChild->setMark(false);
}

/**
 * @brief Removes a child from this node.
 *
 * @param childNode Pointer to the child node to be removed.
 */
void Node::removeChild(Node* childNode) {
    // If it is an only child
    if (childNode->getRight() == childNode) {
        this->setChild(nullptr);
    }
    else {
        Node* leftSibling = childNode->getLeft();
        Node* rightSibling = childNode->getRight();

        leftSibling->setRight(rightSibling);
        rightSibling->setLeft(leftSibling);

        // If this was the first child of the child list, update it.
        if (childNode == this->getChild()) {
            this->setChild(childNode->getRight());
        }
    }

    childNode->setLeft(childNode);
    childNode->setRight(childNode);

    childNode->setParent(nullptr);

    this->decreaseDegree();
}

/**
 * @brief Links a node as a child of this node.
 *
 * @param childNode Pointer to the node to be linked as a child.
 */
void Node::link(Node* childNode) {
    this->addChild(childNode);
}

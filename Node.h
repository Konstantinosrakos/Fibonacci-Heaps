#pragma once

/**
 * @class Node
 * @brief Represents a node in a Fibonacci heap.
 *
 * Each node contains a key, pointers to its parent, child, left and right siblings,
 * the degree of the node (number of children), and a mark indicating whether it has lost a child.
 */
class Node
{
private:
    int key;               ///< The key/value of the node
    Node* parent;          ///< Pointer to the parent node
    Node* child;           ///< Pointer to one of the children
    Node* left;            ///< Pointer to the left sibling
    Node* right;           ///< Pointer to the right sibling
    int degree;            ///< Number of children
    bool marked;           ///< Indicates if the node is marked (lost a child)

public:
    /**
     * @brief Constructs a new Node with the given value.
     *
     * @param value The key/value of the node.
     */
    Node(int value);

    /**
     * @brief Returns the key/value of the node.
     *
     * @return int The key of the node.
     */
    int getKey() const;

    /**
     * @brief Sets the key/value of the node.
     *
     * @param newKey The new key of the node.
     */
    void setKey(int newKey);

    /**
     * @brief Returns the parent of the node.
     *
     * @return Node* The parent node.
     */
    Node* getParent() const;

    /**
     * @brief Sets the parent of the node.
     *
     * @param sParent Pointer to the parent node.
     */
    void setParent(Node* sParent);

    /**
     * @brief Returns the child of the node.
     *
     * @return Node* The child node.
     */
    Node* getChild() const;

    /**
     * @brief Sets the child of the node.
     *
     * @param sChild Pointer to the child node.
     */
    void setChild(Node* sChild);

    /**
     * @brief Returns the left sibling of the node.
     *
     * @return Node* The left sibling node.
     */
    Node* getLeft() const;

    /**
     * @brief Sets the left sibling of the node.
     *
     * @param sLeft Pointer to the left sibling node.
     */
    void setLeft(Node* sLeft);

    /**
     * @brief Returns the right sibling of the node.
     *
     * @return Node* The right sibling node.
     */
    Node* getRight() const;

    /**
     * @brief Sets the right sibling of the node.
     *
     * @param sRight Pointer to the right sibling node.
     */
    void setRight(Node* sRight);

    /**
     * @brief Returns the degree of the node.
     *
     * @return int The degree of the node (number of children).
     */
    int getDegree() const;

    /**
     * @brief Increments the degree of the node.
     */
    void incrementDegree();

    /**
     * @brief Decreases the degree of the node and marks it if it loses a child.
     */
    void decreaseDegree();

    /**
     * @brief Returns the mark status of the node.
     *
     * @return bool True if the node is marked, false otherwise.
     */
    bool getMark() const;

    /**
     * @brief Sets the mark status of the node.
     *
     * @param mark The mark status to be set.
     */
    void setMark(bool mark);

    /**
     * @brief Adds a sibling to the right of this node.
     *
     * @param newSibling Pointer to the new sibling node.
     */
    void addSibling(Node* newSibling);

    /**
     * @brief Adds a child to this node.
     *
     * @param newChild Pointer to the new child node.
     */
    void addChild(Node* newChild);

    /**
     * @brief Removes a child from this node.
     *
     * @param childNode Pointer to the child node to be removed.
     */
    void removeChild(Node* childNode);

    /**
     * @brief Links a node as a child of this node.
     *
     * @param childNode Pointer to the node to be linked as a child.
     */
    void link(Node* childNode);
};

/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1, or 2
        inline size_t numChildren() const {
            return (left != nullptr) + (right != nullptr);
        }

        // true or false
        inline bool isLeaf() const {
            return left == nullptr && right == nullptr;
        }

        // number of hops to deepest leaf node
        inline size_t getHeight() const {
            return height;
        }
    };

public:
    /**
     * @brief AVLTree Create an empty AVL tree.
     */
    AVLTree();

    /**
     * Destruct the AVL tree and clear all memory associated with it.
     */
    ~AVLTree();

    /**
     * @brief AVLTree Create a deep copy of another AVL tree.
     * @param other The tree to copy data from.
     */
    AVLTree(const AVLTree& other);

    /**
     * @brief operator = Copy the data from another AVL tree to this one.
     * @param other The tree to copy data from.
     * @return A reference to myself.
     */
    AVLTree& operator=(const AVLTree& other);

    /**
     * @brief insert Insert a new key-value pair.
     * Duplicate values are ignored.
     * @param key The key to insert.
     * @param value The value to insert.
     * @return True iff a new node was created, false if the key is a duplicate.
     */
    bool insert(const std::string& key, size_t value);

    /**
     * @brief remove Delete a key from the tree if it exists.
     * @param key The key to remove.
     * @return Whether or not the key was found and thus removed.
     */
    bool remove(const std::string& key);

    /**
     * @brief contains Check whether a given key exists in the tree.
     * @param key The key to search for.
     * @return Whether or not the key exists in the tree.
     */
    bool contains(const std::string& key) const;

    /**
     * @brief get Retrieve the value associated with a key.
     * @param key The key to search for.
     * @return An optional containing the value if found, or std::nullopt if not.
     */
    std::optional<size_t> get(const std::string& key) const;

    /**
     * @brief operator [] Get a reference to a key within the tree, or insert a new key
     * if it does not exist.
     * @param key The key to access or insert.
     * @return A reference to the value associated with the key.
     */
    size_t& operator[](const std::string& key);

    /**
     * @brief findRange Return all values with keys in the specified range.
     * @param lowKey The inclusive lower bound of the range.
     * @param highKey The inclusive upper bound of the range.
     * @return A vector containing all values within the range (inclusive).
     */
    std::vector<size_t> findRange(const std::string& lowKey,
                                  const std::string& highKey) const;

    /**
     * @brief keys Get all the keys contained within this tree.
     * @return A vector containing all keys within this tree.
     */
    std::vector<std::string> keys() const;

    /**
     * @brief size Get the number of nodes within this tree.
     * @return The nubmer of nodes in the tree.
     */
    size_t size() const;

    /**
     * @brief getHeight Get the current height of this tree.
     * @return The height of the root node.
     */
    size_t getHeight() const;

    /**
     * @brief getBalance Get the current balance factor of this tree.
     * @return The balance factor of the root node.
     */
    int getBalance() const;

    friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree);

private:
    AVLNode* root = nullptr;
    size_t treeSize = 0;

    // Get a node's height (max of its left and right heights)
    static int nodeHeight(AVLNode* node);

    // helper for operator<< that recurses through and prints stuff sideways
    // right-child-first traversal, also adds indentation and such
    // (basically just turn your head sideways)
    void printTree(std::ostream& os, const AVLNode* node, int indent) const;

    // Helper for contains that traverses the tree (bst order) and checks
    // if any keys match
    bool contains(const AVLNode* node, const std::string& key) const;

    // Helper for get that traverses the tree (bst order) and checks
    // if any keys match. If they do, return the key, otherwise return nullopt
    // This is operationally equivalent to contains ;)
    std::optional<size_t> get(const AVLNode* node, const std::string& key) const;

    // Helper for findRange that traverses the tree (in-order) and collects
    // every value that's within the range.
    void findRange(const AVLNode* node,
                   const std::string& lowKey,
                   const std::string& highKey,
                   std::vector<size_t>& result) const;

    // helper method for operator[] that returns a pointer to a node
    AVLNode* findNode(AVLNode* node, const std::string& key) const;

    // Helper for the destructor that recursively clears and deletes all nodes.
    void clear(AVLNode* node);

    // Helper for the copy and assignment operators.
    // Recursively creates a deep copy of each node
    AVLNode* copySubtree(const AVLNode* node);

    // Helper for keys that traverses the tree and collects all valid keys.
    void keys(const AVLNode* node, std::vector<std::string>& result) const;

    /* Helper methods for insert */

    // Recursive helper for insert; performs the actual insertion + does all the balancing
    // Performs rotations as needed on its way back up the tree
    AVLNode* insert(AVLNode*& node, const std::string& key, size_t value);

    // compute a node's balance factor as the different between the left and right heights
    int getBalance(const AVLNode* node) const;

    // perform a right-rotate around the given node
    // used on: left-left or left-right imbalances
    AVLTree::AVLNode* rotateRight(AVLNode*& y);

    // perform a left-rotate around the given node
    // used on: right-right or right-left imbalances
    AVLTree::AVLNode* rotateLeft(AVLNode*& x);

    /* Helper methods for remove */

    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);

    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);

    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);
};

#endif //AVLTREE_H

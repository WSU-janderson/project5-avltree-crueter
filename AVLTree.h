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
    AVLTree();

    ~AVLTree();

    AVLTree(const AVLTree& other);

    AVLTree& operator=(const AVLTree& other);

    /**
     * @brief insert Insert a new key-value pair.
     * Duplicate values are ignored.
     * @param key The key to insert.
     * @param value The value to insert.
     * @return True iff a new node was created, false if the key is a duplicate.
     */
    bool insert(const std::string& key, size_t value);

    bool remove(const std::string& key);

    /**
     * @brief contains Check whether a given key exists in the tree.
     * @param key The key to search for.
     * @return Whether or not the key exists in the tree.
     */
    bool contains(const std::string& key) const;

    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);

    std::vector<size_t> findRange(const std::string& lowKey,
                                  const std::string& highKey) const;

    std::vector<std::string> keys() const;

    size_t size() const;
    size_t getHeight() const;
    size_t getBalance() const;

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

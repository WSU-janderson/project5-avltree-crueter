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

    bool insert(const std::string& key, size_t value);
    bool remove(const std::string& key);
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
    void printTree(std::ostream& os, const AVLNode* node, int indent) const;

    /* Helper methods for insert */

    // overlaoded insert that does the recursive insert
    AVLNode* insert(AVLNode*& node, const std::string& key, size_t value);

    // get a node's balance
    int getBalance(const AVLNode* node) const;

    // rotate the tree right
    AVLTree::AVLNode* rotateRight(AVLNode*& y);

    // rotate the tree left
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

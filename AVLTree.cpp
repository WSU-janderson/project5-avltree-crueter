#include "AVLTree.h"

#include <iostream>
#include <string>

AVLTree::AVLTree()
{
    // TODO
}

AVLTree::~AVLTree()
{
    // TODO
}

AVLTree::AVLTree(const AVLTree& other)
{
    // TODO
}

AVLTree& AVLTree::operator=(const AVLTree& other)
{
    // TODO
    return *this;
}

bool AVLTree::insert(const std::string& key, size_t value)
{
    size_t oldSize = treeSize;
    root = insert(root, key, value);
    return treeSize > oldSize; // true only if a new node was added}
}

bool AVLTree::remove(const std::string& key)
{
    // TODO
    return false;
}

bool AVLTree::contains(const std::string& key) const
{
    return contains(root, key);
}

std::optional<size_t> AVLTree::get(const std::string& key) const
{
    return get(root, key);
}

size_t& AVLTree::operator[](const std::string& key)
{
    insert(key, 0);
    return findNode(root, key)->value;
}

std::vector<size_t> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const
{
    std::vector<size_t> result;
    findRange(root, lowKey, highKey, result);
    return result;}

std::vector<std::string> AVLTree::keys() const
{
    // TODO
    return {};
}

size_t AVLTree::size() const
{
    return treeSize;
}

size_t AVLTree::getHeight() const
{
    return root ? root->height : 0;
}

size_t AVLTree::getBalance() const
{
    return getBalance(root);
}

int AVLTree::nodeHeight(AVLNode* node){
    return 1
           + std::max((node->left ? node->left->height : 0),
                      (node->right ? node->right->height : 0));
}

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
    avlTree.printTree(os, avlTree.root, 0);
    return os;
}

void AVLTree::printTree(std::ostream& os, const AVLNode* node, int indent) const {
    if (node == nullptr) {
        return;
    }

    // right child first
    printTree(os, node->right, indent + 8);

    // I hate std::string's overrides
    os
        << std::string(indent, ' ')
        << std::string("{")
        << node->key
        << std::string(": ")
        << std::to_string(node->value)
        << std::string("}\n");

    // Then left child
    printTree(os, node->left, indent + 8);
}

bool AVLTree::contains(const AVLNode* node, const string& key) const {
    // end of tree = does not exist :(
    if (node == nullptr) {
        return false;
    }

    // key found. :)
    if (key == node->key) {
        return true;
    }

    // traversal
    if (key < node->key) {
        return contains(node->left, key);
    } else {
        return contains(node->right, key);
    }
}

std::optional<size_t> AVLTree::get(const AVLNode* node, const string& key) const {
    // end of tree = does not exist :(
    if (node == nullptr) {
        return std::nullopt;
    }

    // key found. :)
    if (key == node->key) {
        return node->value;
    }

    // traversal
    if (key < node->key) {
        return get(node->left, key);
    } else {
        return get(node->right, key);
    }
}

void AVLTree::findRange(const AVLNode* node,
                        const string& lowKey,
                        const string& highKey,
                        std::vector<size_t>& result) const
{
    // do I need to keep writing "base case"
    // I hope we understand this :)
    if (node == nullptr) {
        return;
    }

    // iff the left *might* overlap with the range,
    // check it!
    if (lowKey < node->key || lowKey == node->key) {
        findRange(node->left, lowKey, highKey, result);
    }

    // check current node
    if (node->key >= lowKey && node->key <= highKey) {
        result.push_back(node->value);
    }

    // iff the right *might* overlap with the range,
    // check it!
    if (highKey > node->key || highKey == node->key) {
        findRange(node->right, lowKey, highKey, result);
    }
}

/* Insert helpers */
AVLTree::AVLNode* AVLTree::insert(AVLNode*& node, const string& key, size_t value)
{
    // base case; nothing at the specified slot, so insert
    if (node == nullptr) {
        treeSize++;
        return new AVLNode(key, value);
    }

    // key is duped so we just return itself
    if (key == node->key) {
        return node;
    }

    // the recursion
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else {
        node->right = insert(node->right, key, value);
    }

    // update height
    node->height = nodeHeight(node);

    // If we're unbalanced...
    int balance = getBalance(node);

    // rotate left/right depending on which direction we're balanced
    // and where the current key "would" go
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // we're balanced :)
    return node;
}

int AVLTree::getBalance(const AVLNode* node) const
{
    if (!node) return 0;

    int leftH = node->left ? node->left->height : 0;
    int rightH = node->right ? node->right->height : 0;
    return leftH - rightH;
}

AVLTree::AVLNode* AVLTree::rotateRight(AVLNode*& y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    // update heights
    y->height = nodeHeight(y);
    x->height = nodeHeight(x);

    return x;
}

AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode*& x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    // update heights
    y->height = nodeHeight(y);
    x->height = nodeHeight(x);

    return y;
}

bool AVLTree::removeNode(AVLNode*& current)
{
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;

    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode*& current, KeyType key)
{
    return false;
}

void AVLTree::balanceNode(AVLNode*& node) {}

AVLTree::AVLNode* AVLTree::findNode(AVLNode* node, const std::string& key) const
{
    if (!node)
        return nullptr;
    if (key == node->key)
        return node;
    return key < node->key ? findNode(node->left, key) : findNode(node->right, key);
}

#include "AVLTree.h"

#include <string>

AVLTree::AVLTree() {
    // TODO
}

AVLTree::~AVLTree() {
    // TODO
}

AVLTree::AVLTree(const AVLTree& other) {
    // TODO
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    // TODO
    return *this;
}

bool AVLTree::insert(const std::string& key, size_t value) {
    // TODO
    return false;
}

bool AVLTree::remove(const std::string& key) {
    // TODO
    return false;
}

bool AVLTree::contains(const std::string& key) const {
    // TODO
    return false;
}

std::optional<size_t> AVLTree::get(const std::string& key) const {
    // TODO
    return std::nullopt;
}

size_t& AVLTree::operator[](const std::string& key) {
    // TODO
    static size_t asdfgh = 0;
    return asdfgh;
}

std::vector<size_t> AVLTree::findRange(const std::string& lowKey,
                                       const std::string& highKey) const {
    // TODO
    return {};
}

std::vector<std::string> AVLTree::keys() const {
    // TODO
    return {};
}

size_t AVLTree::size() const {
    // TODO: O(1)
    return 0;
}

size_t AVLTree::getHeight() const {
    // TODO: O(1)
    return 0;
}

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
    // TODO: print tree sideways with indentation
    return os;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
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

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

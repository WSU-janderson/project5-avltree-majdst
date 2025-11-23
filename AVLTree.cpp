// Project 5 --> Majid Dousti
// Fall 2025
#include "AVLTree.h"

#include <string>
#include "AVLTree.h"
#include <iostream>
#include <algorithm>

using namespace std;

// returns--> children of a node
size_t AVLTree::AVLNode::numChildren() const {
    size_t count = 0;
    if (this-> left != nullptr) count++;
    if (this->right != nullptr) count++;
    return count;
}

//node--> no children
bool AVLTree::AVLNode::isLeaf() const {
    return (this->left == nullptr && this->right == nullptr);
}

//height in node
size_t AVLTree::AVLNode::getHeight() const{ return this->height;}

AVLTree::AVLTree() {
    root = nullptr;
    numElements = 0;
}
//null pointer preventing crush
int AVLTree::height(AVLNode* node) const {
    if (node == nullptr){return 0;}
    return node->height;
}
//node balance --> check
int AVLTree::getBalance(AVLNode* node) const {
    if (node == nullptr){return 0;}
    return height(node->left) - height(node->right);
    //positive means left is heavy-->negative means right is heavy
}

//right rotation--> fixing the left heavier
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;
    //rotation is done

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    //heights update

    return x; //-->this is new root
}

//left rotation --> fixing the right heavier
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;
    //rotation is done

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    //heights update

    return x; //-->this is new root
}

AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    x->left = y;
    y->right = T2;
    //rotation is done

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    //heights update

    return y; //-->this is new root
}

//Balance Node
void AVLTree::balanceNode(AVLNode*& node) {
    if (node == nullptr) return;

    //height update
    node -> height = 1 + std::max(height(node->left), height(node->right));

    //check balance
    int balance = getBalance(node);

    if (balance > 1) {

        //zigzag check
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    }
}
bool AVLTree::insert(const KeyType& key, ValueType value) {
    bool success = false;
    insertHelper(root, key, value, success);

    if (success){numElements++;}
    return success;
}

void AVLTree::insertHelper(AVLNode*& node, const KeyType& key, ValueType value, bool& success) {
    if (node == nullptr) {
        node = new AVLNode(key, value);
        success = true;
        return;
    }
    if (key < node->key) {
        insertHelper(node->left, key, value, success);

    } else if (key > node->key) {
        insertHelper(node->right, key, value, success);
    }else {
        success = false;
        return;
    }if (success){balanceNode(node);}
}

bool AVLTree::remove(const KeyType& key) {
    //recursion part
    if (removeHelper(root, key)) {
        numElements--;
        return true;
    }
    return false;
}

//Node finding with recursive
bool AVLTree::removeHelper(AVLNode*& current, const KeyType& key) {
    if (current == nullptr) return false;
    bool success = false;

    if (key < current -> key) {
        success = removeHelper(current->left, key);
    } else if (key > current->key) {
        success = removeHelper(current->right, key);
    } else {
        success = removeNode(current);
    }
    if (success) {
        balanceNode(current);
    }
    return success;
}
// node deleter
bool AVLTree::removeNode(AVLNode*& current) {

    if (!current) return false;
    AVLNode* toDelete = current;

    //leaf remover
    if (current -> isLeaf()) {
        current = nullptr;
        delete toDelete;
    }
    //one child
    else if (current -> numChildren() == 1) {
        if (current -> right) {
            current = current -> right;
        } else {
            current = current -> left;
        }
        delete toDelete;
    }//two children
    else {
        AVLNode* smallestInRight = current->right;
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
//fixing the size int
        std::string newKey = smallestInRight ->key;
        size_t newValue = smallestInRight ->value;

        //recursive again-->remove
        removeHelper(current->right, smallestInRight->key);

        //updating every node
        current->key = newKey;
        current->value = newValue;
    }
    return true;
}
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

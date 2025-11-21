/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>

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

        // Node creator
        AVLNode(KeyType k, ValueType v): key(k), value(v), height(1), left(nullptr), right(nullptr) {}

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator = (const AVLTree& other);
    ~AVLTree();

    // Core operations
    bool insert(const KeyType& key, ValueType value);
    bool remove(const KeyType& key);
    bool contains(const KeyType& key) const;

    //Range & Info
    std::vector<ValueType> findRange(const KeyType& lowKey, const KeyType& highKey) const;
    std::vector<KeyType> keys() const;
    size_t size() const;
    size_t getHeight() const;

    //Printing to have access to private data
    friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree);


    private:
    AVLNode* root;
    //size O(1) tracker
    size_t numElements;

    //Ta inja omadam-->
    int height(AVLNode* node) const;
    int getBalance(AVLNode* node) const;

    // Rotation
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);

    void balanceNode(AVLNode*& node); //It will fix the node balance
    // This is new to me--> reference to the pointer

    //Interesting part--> Recursive
    void insertHelper(AVLNode*& node, const KeyType& key, ValueType value, bool& success);

    // search - get
    const ValueType* getHelper(AVLNode* node, const KeyType& key) const;
    bool containsHelper(AVLNode* node, const KeyType& key) const;
    ValueType& bracketHelper(AVLNode*& node, const KeyType& key);

    //Remove
    bool removeHelper(AVLNode*& current, const KeyType& key);
    bool removeNode(AVLNode*& current);

    //Managing Memory
    AVLNode* copyHelper(const AVLNode* otherNode);
    void destroyHelper(AVLNode* node);

    void printSideways(std::ostream& os, AVLNode* node, int depth) const;
};

#endif //AVLTREE_H

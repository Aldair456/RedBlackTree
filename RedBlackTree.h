//
// Created by aldai on 5/7/2024.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Node.h"

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void InsertViolation(Node*& node);
    void BSTInsert(Node*& root, Node* node);
    void DeleteViolation(Node *&node, Node *parent);
    void transplant(Node* node, Node* node_change);
    void deleteNode(Node* node);
    Node* search(Node* root, int key);
    void deleteTree(Node *node);

public:
    ~RedBlackTree();

    RedBlackTree() : root(nullptr) {}
    void insert(int data);
    void remove(int data);
    Node* search(int key);
    Node*minimum(Node* node);

};

#endif //REDBLACKTREE_H

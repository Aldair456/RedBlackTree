//
// Created by aldai on 5/7/2024.
//

#ifndef NODE_H
#define NODE_H
#include "iostream"
using namespace std;
enum Color { RED, BLACK };

struct Node {
    int data;
     Color color;
     Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(
    nullptr), right(nullptr), parent(nullptr) {}
};

#endif //NODE_H

#ifndef TTTREE_H
#define TTTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ttTree
{
public:
    ttTree();
    void printTree(ostream &out);
    bool contains(int target);
    void buildTree(ifstream &input);
    bool deleteNode(int target);

private:
    struct node
    {
        node *left;
        node *middle;
        node *right;
        int leftKey;
        int rightKey;
    };
    node *root;
    vector<int> line;
    node *createNode(const int x, node *left, node *middle, node *right);
    bool isLeafNode(node *x);
    node *add(node *x, node *newNode);
    node *insert(const int &key, node *root);
    void print(node *node, ostream &out);
    bool searchTreeHelper(node *x, int value);
    void printTreeHelper(node *x, ostream &out);
    bool deleteHelper(node *x, int target);
    bool deleteLeft(node *x);
    bool deleteRight(node *x);
    bool deleteMid(node *x);
    void moveLeft(node *x);
    void moveRight(node *x,node *left, int Key);
};

#endif
#ifndef TRIETREE_H
#define TRIETREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

class trieTree
{
public:
    trieTree();
    void buildTree();
    bool contains(string key);
    void printTree();
    bool deleteNode(string key);

private:
    struct node
    {
        node *children[ALPHABET_SIZE];
        bool isEndOfWord;
    };

    node *root;
    node *createNode();
    bool search(string key);
    void insert(string key);
    void printHelper(node *x);
    bool isLeafNode(node *node);
    bool isOneChild(node *x);
    bool deleteHelper(node *x, string target, int i);
};

#endif
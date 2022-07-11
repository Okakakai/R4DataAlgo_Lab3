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
    void contains(string key);
    // void printTree();

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
    bool deleteNode(node *x, string key);
    // void printHelper(node *x);
    bool isLeafNode(node *node);
};

#endif
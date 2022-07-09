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
    void printTree(ostream &out = cout);
    void contains();
    void buildTree(ifstream &input);
    void timeTaken();

private:
    struct node
    {
        node *left;
        node *middle;
        node *right;
        int leftKey;
        int rightKey;
        vector<int> leftLines;
        vector<int> rightLines;
    };
    node *root;
    vector<int> evenNumbers;
    node *createNode(const int x, node *left, node *middle, node *right);
    bool isLeafNode(node *x);
    node *add(node *x, node *n);
    node *insert(const int &key, int line, node *root, int &distWord);
    bool searchTreeHelper(node *x, string value, vector<int> &lines);
    void printLines(node *x, bool isLeft, ostream &out);
    void print(node *x, ostream &out);
    void printTreeHelper(node *x, ostream &out);
    int findHeight(node *x);
};

#endif
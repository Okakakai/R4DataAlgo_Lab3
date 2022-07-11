#include <bits/stdc++.h>
#include "trieTree.h"
using namespace std;

trieTree::trieTree()
{
    root = NULL;
    root = createNode();
}

void trieTree::buildTree()
{
    string keys[] = {"car", "card", "try", "tried", "cat"};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
    {
        cout << keys[i] << endl;
        insert(keys[i]);
    }
    cout << "===== output ====" << endl;
    char output = 'a';
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (root->children[j])
        {
            char temp = output + j;
            cout << temp << endl;
        }
        cout << endl;
    }
}

trieTree::node *trieTree::createNode()
{
    struct node *pNode = new node;
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

bool trieTree::contains(string target)
{
    bool found = search(target);
    if (found)
    {
        std::cout << target;
        std::cout << " is in the document" << endl;
        return true;
    }
    else
    {
        std::cout << "\"" << target << "\" "
                  << "is not in the document" << endl;
        ;
        return false;
    }
}
void trieTree::insert(string key)
{
    struct node *x = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        cout << "======== key =======" << endl;
        cout << key[i] << endl;
        cout << "========index=======" << endl;
        cout << index << endl;
        if (!x->children[index])
            x->children[index] = createNode();

        x = x->children[index];
    }

    x->isEndOfWord = true;
}

bool trieTree::search(string key)
{
    struct node *x = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!x->children[index])
        {
            return false;
        }

        x = x->children[index];
    }

    return (x->isEndOfWord);
}

void trieTree::printTree()
{
    printHelper(root);
}

void trieTree::printHelper(node *x)
{
    char arphabet = 'a';
    if (x->isEndOfWord)
    {
        for (int j = 0; j < ALPHABET_SIZE; j++)
        {
            if (root->children[j])
            {
                char temp = arphabet + j;
                cout << temp << endl;
            }
            cout << endl;
        }
    }
    if (!x->isEndOfWord)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            printHelper(x->children[i]);
            char temp = arphabet + i;
            cout << temp << endl;
        }
    }
}

bool trieTree::isLeafNode(node *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (!node->children[i])
        {
            return false;
        }
    }
    return true;
}

bool trieTree::isOneChild(node *node)
{
    int flag = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            flag++;
        }
        if (flag > 1)
        {
            return false;
        }
    }
    if (flag == 1)
    {
        return true;
    }
    return false;
}

bool trieTree::deleteNode(string target)
{
    struct node *x = root;
    string keys;
    for (int i = 0; i < target.length(); i++)
    {
        keys.push_back(target[i]);
    }
    std::vector<node *> vec = std::vector<node *>();
    node *tmp = NULL;
    for (int i = 0; i < target.length(); i++)
    {
        if (i == 0)
        {
            tmp = x->children[target[i] - 'a'];
        }
        else
        {
            tmp = tmp->children[target[i] - 'a'];
        }
        vec.push_back(tmp);
    }
    node *endian = vec[target.length() - 1];
    if (!isLeafNode(endian))
    {
        vec[target.length() - 1]->isEndOfWord = false;
        return false;
    }
    for (int i = target.length() - 1; i >= 0; i--)
    {
        if (i != target.length() - 1 && vec.at(i)->isEndOfWord)
        {
            break;
        }
        if (i == 0 || (!isLeafNode(vec.at(i)) && !isOneChild(vec.at(i))))
        {
            free(vec.at(i)->children[target[target.length() - i - 1] - 'a']);
            break;
        }
    }
    return true;
}
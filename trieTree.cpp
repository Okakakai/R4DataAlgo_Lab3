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

void trieTree::contains(string target)
{
    bool found = search(target);
    if (found)
    {
        std::cout << target;
        std::cout << " is in the document" << endl;
    }
    else
    {
        std::cout << "\"" << target << "\" "
                  << "is not in the document";
    }
    std::cout << endl;
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

// void trieTree::printTree()
// {
//     printHelper(root);
// }

// void trieTree::printHelper(node *x)
// {
//     char arphabet = 'a';
//     if (x->isEndOfWord)
//     {
//         for (int j = 0; j < ALPHABET_SIZE; j++)
//         {
//             if (root->children[j])
//             {
//                 char temp = arphabet + j;
//                 cout << temp << endl;
//             }
//             cout << endl;
//         }
//     }
//     if (!x->isEndOfWord)
//     {
//         for (int i = 0; i < ALPHABET_SIZE; i++)
//         {
//             printHelper(x->children[i]);
//             char temp = arphabet + i;
//             cout << temp << endl;
//         }
//     }
// }

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

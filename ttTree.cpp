#include "ttTree.h"
#include <iomanip>
#include <sstream>

ttTree::ttTree()
{
    root = NULL;
}

void ttTree::printTree(ostream &out)
{
    out << "2-3 Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

bool ttTree::contains(int target)
{
    bool found = searchTreeHelper(root, target);
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
    return found;
}

void ttTree::buildTree(ifstream &input)
{
    std::cout << "-----------------------------------------------------" << endl;
    std::cout << "build 2-3 tree" << endl;
    int line = 1, treeHeight = 0, num = 0;
    string tmpInput, tmpLine;
    string strNum;

    while (!input.eof())
    {
        getline(input, tmpInput);
        stringstream tmpLine(tmpInput);
        while (getline(tmpLine, strNum, ' '))
        {
            num = stoi(strNum);
            root = insert(num, root);
            contains(num);
            num = 0;
        }
    }
}

ttTree::node *ttTree::createNode(const int x, node *left, node *middle, node *right)
{
    node *t = new node();
    t->leftKey = x;
    t->left = left;
    t->middle = middle;
    t->right = right;
    return t;
}

bool ttTree::isLeafNode(node *x)
{
    if (x->left == NULL && x->middle == NULL && x->right == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ttTree::node *ttTree::add(node *x, node *newNode)
{
    if (x->rightKey == 0)
    {
        if (x->leftKey < newNode->leftKey)
        {
            x->rightKey = newNode->leftKey;
            x->middle = newNode->left;
            x->right = newNode->middle;
        }
        else
        { // SWAP
            x->rightKey = x->leftKey;
            x->leftKey = newNode->leftKey;
            x->right = x->middle;
            x->middle = newNode->middle;
            x->left = newNode->left;
        }
        return x;
    }
    // ADD TO LEFT
    else if (x->leftKey >= newNode->leftKey)
    {
        node *newNodeNode = createNode(x->leftKey, newNode, x, NULL);
        x->left = x->middle;
        x->middle = x->right;
        x->right = NULL;
        x->leftKey = x->rightKey;
        x->rightKey = 0;

        return newNodeNode;
    }
    // ADD TO CENTER
    else if (x->rightKey >= newNode->leftKey)
    {
        node *newNodeNode = createNode(x->rightKey, newNode->middle, x->right, NULL);
        x->middle = newNode->left;
        newNode->middle = newNodeNode;
        newNode->left = x;
        x->rightKey = 0;
        x->right = NULL;

        return newNode;
    }
    // ADD TO RIGHT
    else
    {
        node *newNodeNode = createNode(x->rightKey, x, newNode, NULL);
        x->right = NULL;
        x->rightKey = 0;

        return newNodeNode;
    }
}

ttTree::node *ttTree::insert(const int &key, node *root)
{
    if (root == NULL)
    {
        node *newNode = createNode(key, NULL, NULL, NULL);
        return newNode;
    }
    if (key == root->leftKey || key == root->rightKey)
    {
        if (key != root->leftKey)
        {
            return root;
        }
    }
    if (isLeafNode(root))
    {
        node *newNode = createNode(key, NULL, NULL, NULL);
        node *finalNode = add(root, newNode);
        return finalNode;
    }
    // LEFT
    if (key < root->leftKey)
    {
        node *newNode = insert(key, root->left);
        if (newNode == root->left)
            return root;
        else
            return add(root, newNode);
    }
    // MIDDLE
    else if (root->rightKey == 0 || key < root->rightKey)
    {
        node *newNode = insert(key, root->middle);
        if (newNode == root->middle)
            return root;
        else
            return add(root, newNode);
    }
    // RIGHT
    else
    {
        node *newNode = insert(key, root->right);
        if (newNode == root->right)
            return root;
        else
            return add(root, newNode);
    }
}

bool ttTree::searchTreeHelper(node *x, int value)
{
    if (root == NULL)
    {
        return false;
    }
    if (value == x->leftKey)
    {
        return true;
    }
    if (value == x->rightKey)
    {
        return true;
    }
    if (isLeafNode(x))
        return false;
    else if (x->rightKey != 0)
    {
        if (value < x->leftKey)
        {
            return searchTreeHelper(x->left, value);
        }
        else if (value > x->leftKey && value < x->rightKey)
        {
            return searchTreeHelper(x->middle, value);
        }
        else
        {
            return searchTreeHelper(x->right, value);
        }
    }
    else
    {
        if (value < x->leftKey)
            return searchTreeHelper(x->left, value);
        else
            return searchTreeHelper(x->middle, value);
    }
}

void ttTree::printTreeHelper(node *x, ostream &out)
{
    if (x != NULL)
    {
        if (isLeafNode(x))
        {
            print(x, out);
        }
        else
        {

            printTreeHelper(x->left, out);
            out << setw(30) << std::left;
            out << x->leftKey;
            out << endl;
            if (x->middle)
            {
                printTreeHelper(x->middle, out);
                if (x->rightKey != 0)
                {
                    out << setw(30) << std::left;
                    out << x->rightKey;
                    out << endl;
                }
            }
            printTreeHelper(x->right, out);
        }
    }
}

void ttTree::print(node *x, ostream &out)
{
    if (x != NULL)
    {
        if (x->rightKey == 0)
        {
            out << setw(30) << std::left;
            out << x->leftKey;
            out << endl;
        }
        else
        {
            out << setw(30) << std::left;
            out << x->leftKey;
            out << endl;
            out << setw(30) << std::left;
            out << x->rightKey;
            out << endl;
        }
    }
}

bool ttTree::deleteHelper(node *x, int target)
{
    std::cout << "--------------------------------" << endl;
    if (x->leftKey == target || (x->rightKey != 0 && x->rightKey == target))
    {
        // データの発見
        if (x->left == NULL)
        {
            // leaf
            if (x->leftKey == target)
            {
                x->leftKey = x->rightKey;
            }
            x->rightKey = 0;
            return x->leftKey == 0;
        }
        else
        {
            // node
            if (x->leftKey == target)
            {
                node *searchMinNode;
                cout << "--------------------";
                searchMinNode = x->middle;
                while (searchMinNode->left != NULL)
                {
                    searchMinNode = searchMinNode->left;
                }
                x->leftKey = searchMinNode->leftKey;
                if (deleteHelper(x->middle, x->leftKey))
                {
                    return deleteRight(x);
                }
            }
            else
            {
                node *searchMinNode;
                searchMinNode = x->right;
                while (searchMinNode->left != NULL)
                {
                    searchMinNode = searchMinNode->left;
                }
                x->rightKey = searchMinNode->leftKey;
                if (deleteHelper(x->right, x->rightKey))
                {
                    return deleteRight(x);
                }
            }
        }
    }
    else if (target < x->leftKey)
    {
        if (deleteHelper(x->left, target))
        {
            return deleteLeft(x);
        }
    }
    else if (x->rightKey == 0 || target < x->rightKey)
    {
        if (deleteHelper(x->middle, target))
        {
            return deleteMid(x);
        }
    }
    else
    {
        if (deleteHelper(x->right, target))
        {
            return deleteRight(x);
        }
    }
    return false;
}

bool ttTree::deleteLeft(node *x)
{
    if (x->left->leftKey == 0)
    {
        //空の葉ならリンクを切る
        x->left = NULL;
    }
    if (x->middle->rightKey != 0)
    {
        // 隣の節は子が３つ
        x->left = createNode(x->leftKey, x->left, x->middle->left, NULL);
        x->leftKey = x->middle->leftKey;
        moveLeft(x->middle);
        return false;
    }
    else if (x->rightKey != 0)
    {
        // node の子が三つ
        moveRight(x->middle, x->left, x->leftKey);
        moveLeft(x);
        return false;
    }
    else
    {
        // node の子が２つ
        node *node1 = x->middle;
        x->rightKey = node1->leftKey;
        x->middle = node1->left;
        x->right = node1->middle;
        return true;
    }
}

void ttTree::moveLeft(node *x)
{
    x->left = x->middle;
    x->middle = x->right;
    x->right = NULL;
    x->leftKey = x->rightKey;
    x->rightKey = 0;
}

void ttTree::moveRight(node *x, node *left, int leftKey)
{
    x->right = x->middle;
    x->middle = x->left;
    x->left = left;
    x->rightKey = x->leftKey;
    x->leftKey = leftKey;
}

bool ttTree::deleteRight(node *x)
{
    //空の葉ならばリンクを切る
    if (x->right->leftKey == 0)
    {
        x->right = NULL;
    }
    // 中央の子と調節する
    if (x->middle->rightKey != 0)
    {
        // 子が三つある
        x->right = createNode(x->rightKey, x->middle->right, x->right, NULL);
        x->rightKey = x->middle->rightKey;
        x->middle->right = NULL;
        x->middle->rightKey = 0;
    }
    else
    {
        node *node1 = x->middle;
        node1->right = x->right;
        node1->rightKey = x->rightKey;
        x->right = NULL;
        x->rightKey = 0;
    }
    return false;
}

bool ttTree::deleteMid(node *x)
{
    // 空の葉ならばリンクを切る
    if (x->middle->leftKey == 0)
    {
        x->middle = NULL;
    }
    if (x->rightKey != 0)
    {
        // 右の子と調整する
        if (x->right->rightKey != 0)
        {
            // 子が３つある
            x->middle = createNode(x->rightKey, x->middle, x->right->left, NULL);
            x->rightKey = x->right->leftKey;
            moveLeft(x->right);
        }
        else
        {
            // 子が２つ
            moveRight(x->right, x->middle, x->rightKey);
            x->middle = x->right;
            x->right = NULL;
            x->rightKey = 0;
            return false;
        }
    }
    else
    {
        // 左の子と調整する
        if (x->left->rightKey != 0)
        {
            // 子が３つある
            x->middle = createNode(x->leftKey, x->left->right, x->middle, NULL);
            x->leftKey = x->left->rightKey;
            x->left->right = NULL;
            x->left->rightKey = 0;
            return false;
        }
        else
        {
            // 子が二つ
            node *node1 = x->left;
            x->rightKey = x->leftKey;
            x->leftKey = node1->leftKey;
            x->right = x->middle;
            x->middle = node1->middle;
            x->left = node1->left;
            return true;
        }
    }
    return true;
}

bool ttTree::deleteNode(int target)
{
    bool ok = contains(target);
    if (!ok)
    {
        std::cout << target;
        std::cout << " is not document" << endl;
        return false;
    }

    if (root == NULL)
    {
        std::cout << " there is not tree" << endl;
        return false;
    }
    std::cout << "・・・DELETING ・・・・\n ---------------------" << endl;
    if (isLeafNode(root))
    {
        if (root->leftKey == target)
        {
            if (root->rightKey != 0)
            {
                root->leftKey = root->rightKey;
                root->rightKey = 0;
            }
            else
            {
                root->leftKey = 0;
            }
            std::cout << " deleted root key " << endl;
            return true;
        }
        else if (root->rightKey == target)
        {
            root->rightKey = 0;
            std::cout << " deleted root key" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    deleteHelper(root, target);

    return true;
}

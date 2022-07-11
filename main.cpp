#include <iostream>
#include <fstream>
#include "ttTree.h"
#include "trieTree.h"
using namespace std;

int main(int argc, char *argv[])
{
    char choice;
    char option;

    if (argc != 2)
    {
        cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (input.is_open())
    {
        cout << endl;
        cout << "=====================================================" << endl;
        cout << "- Program Main Menu" << endl;
        cout << "=====================================================" << endl;
        cout << "Options: " << endl;
        cout << "(a) 2-3 Tree " << endl;
        cout << "(b) trie Tree " << endl;
        cout << "(c) --- " << endl;
        cout << "Choice: ";
        cin >> option;

        if (option == 'a')
        { // 2-3 Tree
            ttTree myTree;
            myTree.buildTree(input);
            input.close();
            while (1)
            {
                choice = 0;
                cout << "Options: (a) display index, (b) search, (c) delete (d) quit\n";
                cin >> choice;

                // Print index
                if (choice == 'a')
                    myTree.printTree(cout);

                // Search index
                else if (choice == 'b')
                {
                    myTree.contains(10);
                    myTree.contains(19);
                }

                // delete
                else if (choice == 'c')
                {
                    int target;
                    cout << "Delete Num : ";
                    cin >> target;
                    myTree.deleteNode(target);
                }

                // Quit
                else
                    break;
            }
        }
        if (option == 'b')
        {
            trieTree trieTree;
            trieTree.buildTree();
            while (1)
            {
                choice = 0;
                cout << "Options: (a) ----, (b) search, (c) delete (d) quit\n";
                cin >> choice;

                // Print index
                // if (choice == 'a')
                // {
                //     trieTree.printTree();
                // }
                // Search index
                if (choice == 'b')
                {
                    string word1, word2, word3;
                    word1 = "card";
                    word2 = "carp";
                    word3 = "trie";
                    trieTree.contains(word1);
                    trieTree.contains(word2);
                    trieTree.contains(word3);
                }

                // delete
                else if (choice == 'c')
                {
                    int target;
                    cout << "Delete Num : ";
                    cin >> target;
                }

                // Quit
                else break;
            }
        }
    }

    else
    {
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
    cout << endl;
    return 0;
}

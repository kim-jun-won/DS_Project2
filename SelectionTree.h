#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* winner; // Array of winner tree nodes
    SelectionTreeNode* root; // Pointer to the root node of the selection tree
    ofstream* fout;  // Pointer to the output file stream
     
public:
    SelectionTree(ofstream* fout) {  // Constructor: Initializes the selection tree with a given output file stream
        
        this->fout = fout;
        // Create the root node and an array of winner tree nodes
        root = new SelectionTreeNode();
        winner = new SelectionTreeNode[16];
        // Create a default LoanBookData object for initialization
        LoanBookData* data = new LoanBookData();
        data->setBookData("{", 0, " ", 0);
        for (int i = 1; i <= 15; i++)
        {
            winner[i].setBookData(data);
        }
        // Create the hierarchical structure of winner tree nodes
        root->setRightChild(&winner[1]);
        for (int i = 1; i <= 7; i++)
        {
            winner[i].setLeftChild(&winner[i * 2]);
            winner[i].setRightChild(&winner[i * 2 + 1]);
        }
        // Set parent pointers for each winner tree node
        for (int i = 2; i <= 15; i++)
        {
            winner[i].setParent(&winner[i / 2]);
        }


    }

    ~SelectionTree() {

    }
    // getter setter
    SelectionTreeNode* getwinner() { return winner;  }
    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
};
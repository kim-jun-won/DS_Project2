#pragma once
#include "LoanBookData.h"

class LoanBookHeapNode
{
private:
    LoanBookData* pData;
    LoanBookHeapNode* pLeft;
    LoanBookHeapNode* pRight;
    LoanBookHeapNode* pParent;

public:
    // Constructor: Initializes pointers to null
    LoanBookHeapNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
    }
    ~LoanBookHeapNode() {

    }
  
    void setBookData(LoanBookData* data) { this->pData = data; }   // Setter for loan book data
    void setLeftChild(LoanBookHeapNode* pL) { this->pLeft = pL; } // Setter for the left child
    void setRightChild(LoanBookHeapNode* pR) { this->pRight = pR; } // Setter for the right child
    void setParent(LoanBookHeapNode* pP) { this->pParent = pP; } // Setter for the parent node
     
    LoanBookData* getBookData() { return pData; } // Getter for loan book data
    LoanBookHeapNode* getLeftChild() { return pLeft; }    // Getter for the left child
    LoanBookHeapNode* getRightChild() { return pRight; } // Getter for the right child
    LoanBookHeapNode* getParent() { return pParent; }  // Getter for the parent node
};
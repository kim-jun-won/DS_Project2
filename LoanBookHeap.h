#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root; // Pointer to the root node of the heap
   
public:
    int heapsize; // Variable to track the size of the heap

public:
    LoanBookHeap() {  // Constructor: Initializes the root and heap size
        this->root = NULL;
        this->heapsize = 0;
     
    };     // Destructor
    ~LoanBookHeap() {

    }
    // Setter for the root of the heap
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    // Getter for the root of the heap
    LoanBookHeapNode* getRoot() { return root; }
    // Function to perform the heapifyUp operation
    void heapifyUp(LoanBookHeapNode* pN);
    // Function to perform the heapifyDown operation
    void heapifyDown(LoanBookHeapNode* pN);
    // Function to insert a new LoanBookData into the heap
    bool Insert(LoanBookData* data);
};

#pragma once
#include "LoanBookData.h"
#include <map>

class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {

	}
	// Set the leftmost child of the node
	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; } // Set the parent of the node

	BpTreeNode* getParent() { return pParent; } // Get the parent of the node
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; } // Get the leftmost child of the node
	// Virtual functions for handling linked list navigation 
	virtual void setNext(BpTreeNode* pN) {} 
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }
	// Virtual functions for inserting and deleting data and index mappings
	virtual void insertDataMap(string n, LoanBookData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}
	// Virtual functions for accessing data and index mapping
	virtual map<string, BpTreeNode*>* getIndexMap() { return nullptr; }
	virtual map<string, LoanBookData*>* getDataMap() { return nullptr; }

};

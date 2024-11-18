#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>

class BpTree {

private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;

public:
	BpTree(ofstream* fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree();
	/* essential */
	bool		Insert(LoanBookData* newData); // insert
	bool		excessDataNode(BpTreeNode* pDataNode); // excessDataNode and if pDataNode's map count is more than order return true
	bool		excessIndexNode(BpTreeNode* pIndexNode); // same as escessDataNode
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);

};

#endif

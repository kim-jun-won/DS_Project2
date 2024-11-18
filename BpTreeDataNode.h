#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_
#include <map>
using namespace std;
#include "BpTreeNode.h"
// class BpTreeDataNode
class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, LoanBookData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}
	~BpTreeDataNode() {

	}

	void setNext(BpTreeNode* pN) { pNext = pN; } // set pNext as pN
	void setPrev(BpTreeNode* pN) { pPrev = pN; } // set pPrev as pN
	BpTreeNode* getNext() { return pNext; }		 // getNext
	BpTreeNode* getPrev() { return pPrev; }		 // getPrev
	// Insert DataMap in pN
	void insertDataMap(string name, LoanBookData* pN) {
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN));
	}
	// deleteMap in map which name is name
	void deleteMap(string name) {
		mapData.erase(name);
	}
	map<string, LoanBookData*>* getDataMap() { return &mapData; }
};

#endif

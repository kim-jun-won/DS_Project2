#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
#include <map>
//template <class T>
class BpTreeIndexNode : public BpTreeNode {
private:
	map <string, BpTreeNode*> mapIndex;

public:
	BpTreeIndexNode() {};
	~BpTreeIndexNode() {

	};

	// insertIndexMap 
	void insertIndexMap(string name, BpTreeNode* pN) {
		mapIndex.insert(map<string, BpTreeNode*>::value_type(name, pN));
	}
	// deleteMap
	void deleteMap(string name) {
		mapIndex.erase(name);
	}
	map <string, BpTreeNode*>* getIndexMap() { return &mapIndex; }

};

#endif
#include "BpTree.h"
#include <cmath>



bool BpTree::Insert(LoanBookData* newData) {

	int count[8] = { 3,3,3,4,4,2,2,2 };

	// if first data input
	if (root == nullptr)
	{
		// create new BpTreeNode , and set root as newNode
		BpTreeNode* data = new BpTreeDataNode;
		data->insertDataMap(newData->getName(), newData);
		data->setNext(nullptr);
		data->setPrev(nullptr);

		root = data;
		return true;
	}

	// is second data is input
	BpTreeNode* cur = searchDataNode(newData->getName());
	bool flag = searchBook(newData->getName());
	// if data is not exsisted in Bptree
	if (flag == false)
	{
		map<string, LoanBookData*>* a = cur->getDataMap();
		pair<string, LoanBookData*> data;
		data.first = newData->getName();
		data.second = newData;
		a->insert(data);
		// whiel cur is not nullptr -> repeat split
		// changing cur as cur's parent
		while (cur != nullptr)
		{
			// if it is DataNode and moret than order
			if (cur->getMostLeftChild() == nullptr && excessDataNode(cur))
			{
				splitDataNode(cur);
			}
			// if it is IndexNode and more than order
			else if (cur->getMostLeftChild() != nullptr && excessIndexNode(cur))
			{
				splitIndexNode(cur);
			}
			else {
				break;
			}
			cur = cur->getParent();
		}
		return true;
	}
	// if key is already existed in Bptree update loanBookCount
	else
	{
		int loancount = 0;
		int bookcode = 0;
		// change cur pointer to dataNode if cur is IndexNode
		if (cur->getIndexMap() != nullptr)
		{
			while (cur->getMostLeftChild() != nullptr)
				cur = cur->getMostLeftChild();
		}
		// while cur is not nullptr
		while (cur != nullptr)
		{
			// set a as cur DataMap
			map<string, LoanBookData*>* a = cur->getDataMap();
			auto itr = a->begin();
			while (itr != a->end())
			{
				// if data is targt Data update LaonCount
				if (itr->first == newData->getName())
				{
					itr->second->updateCount();
					loancount = itr->second->getLoanCount();
					bookcode = itr->second->getCode();

					break;
				}
				itr++;
			}
			cur = cur->getNext();
		}

		// is laoncount is more than fixed loan count return false
		if (loancount >= count[bookcode/100])
		{
			newData->setloancount(count[bookcode / 100]);
			return false;
		}
		
	}

	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	// in this case when order is three
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	// in this case when order is three
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {

	map<string, LoanBookData*>* a = pDataNode->getDataMap();
	auto itr = a->begin();
	int order = this->order;
	int split = ceil((order - 1) / 2.0) + 1;
	// crete newBpTreeNode data1 and data2 and insert data 
	// [first] , [second,third]
	BpTreeNode* data1 = new BpTreeDataNode;
	BpTreeNode* data2 = new BpTreeDataNode;

	for (int i = 0; i < split - 1; i++)
	{
		data1->insertDataMap(itr->first, itr->second);
		itr++;
	}
	string name = itr->first;
	for (int i = split; i <= order; i++)
	{
		data2->insertDataMap(itr->first, itr->second);
		itr++;
	}
	// delete exsited dataNode in pDataNode
	map<string, LoanBookData*>* b = pDataNode->getDataMap();
	auto it = b->begin();
	it++;
	for (; it != b->end();)
	{
		b->erase(it++);
	}
	// if pDatNode's parent is not nullptr -> if indexNode is existed
	if (pDataNode->getParent() != nullptr) 
	{
		// insert data2 in pDataNode's parent
		BpTreeNode* a = pDataNode->getParent();
		a->insertIndexMap(name, data2);
		// connect parent with data1 and data2
		if (a->getIndexMap()->begin()->first == name)
		{
			a->setMostLeftChild(pDataNode);
		}
		data2->setNext(pDataNode->getNext());
		if (pDataNode->getNext() != nullptr)
		{
			pDataNode->getNext()->setPrev(data2);
		}
		
		data2->setParent(a);
	}
	// if pDataNode's parent is nullptr
	else { 
		// create new BpTreeNode
		BpTreeNode* newIndexNode = new BpTreeIndexNode();
		// insert data2 in newIndexNode
		newIndexNode->insertIndexMap(name, data2);
		newIndexNode->setMostLeftChild(pDataNode);
		// connect IndexMap with data1 and data2
		pDataNode->setParent(newIndexNode);
		data2->setParent(newIndexNode);
		// set root as newIndexNode
		root = newIndexNode;
	}

	pDataNode->setNext(data2);
	data2->setPrev(pDataNode);
}
// split IndexNode
void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	map<string, BpTreeNode*>* a = pIndexNode->getIndexMap();
	auto itr = a->begin();

	// create new indexNode data1 and data2
	BpTreeNode* data1 = new BpTreeIndexNode();
	BpTreeNode* data2 = new BpTreeIndexNode();

	// split indexNode and connect left and right
	data1->insertIndexMap(itr->first, itr->second); itr++;
	data1->setMostLeftChild(pIndexNode->getMostLeftChild());
	string name = itr->first;
	data2->setMostLeftChild(itr->second);
	itr->second->setParent(data2);
	itr++;
	data2->insertIndexMap(itr->first, itr->second);
	itr->second->setParent(data2);


	// If the number of index nodes exceeds the number, and an index node exists above, just add it above.
	if (pIndexNode->getParent() != nullptr)
	{
		BpTreeNode* a = pIndexNode->getParent(); // ais BpTreeIndexNode
		a->insertIndexMap(name, data2);
		// If the inserted IndexMap is entered as the first index, mostleftChild must be changed.
		if (a->getIndexMap()->begin()->first == name)
		{
			a->setMostLeftChild(data1);
			data2->setParent(a);
			pIndexNode->setParent(a);
		}

		// In other cases, just put data2 into the parent's IndexNode and delete the existing IndexNode except for the first data.
		else
		{
			data2->setParent(a);
			pIndexNode->setParent(a);

			map<string, BpTreeNode*>* b = pIndexNode->getIndexMap();
			auto it = b->begin();
			it++;
			for (; it != b->end();)
			{
				b->erase(it++);
			}
		}

	}
	else
		{
		// create newIndexNode
		BpTreeNode* newIndexNode = new BpTreeIndexNode();
		newIndexNode->insertIndexMap(name, data2); // insert data2 in newIndexNode
		newIndexNode->setMostLeftChild(pIndexNode); // set leftMostchild as pIndexNode
		pIndexNode->setParent(newIndexNode); // connect pIndexNode and NewIndexNode and data2
		data2->setParent(newIndexNode);

		// erase pIndexNode 
		map<string, BpTreeNode*>* b = pIndexNode->getIndexMap();
		auto it = b->begin();
		it++;
		for (; it != b->end();)
		{
			b->erase(it++);
		}

		root = newIndexNode;
	}

}

BpTreeNode* BpTree::searchDataNode(string name) {

	BpTreeNode* pCur = root;
	// while pCur is leafNode
	while (pCur->getMostLeftChild() != nullptr)
	{
		map<string, BpTreeNode*>* a;
		a = pCur->getIndexMap();
		auto iter = a->begin();
		// Compare the names while inspecting the iterator from beginning to end.
		while (iter != a->end())
		{
			if (name == iter->first)
				return pCur;
			else if (name < iter->first && iter == a->begin())
			{
				pCur = pCur->getMostLeftChild();
				break;
			}
			else if (name < iter->first)
			{
				iter--;
				pCur = iter->second;
				break;
			}
			else if(name > iter->first)
				iter++;
		}
		// If iter reaches the end, decrement iter by 1 and store iter->second(BpTreeNode*) value in pCur value.
		if (iter == a->end())
		{
			iter--;
			pCur = iter->second;
		}
	}
	// return pCur
	return pCur;
}
// searchBook
bool BpTree::searchBook(string name) {
	// save pCur as searchDataNode
	BpTreeNode* pCur = searchDataNode(name);
	// if pCur is IndexMap -> find name Node! -> return ture
	if (pCur->getIndexMap() != nullptr)
	{
		return true;
	}
	else
	{
		// pCur points to the leaf BpTreeNode where the corresponding data may exist
		map<string, LoanBookData*>* b = pCur->getDataMap();
		// if find name return true else return false
		if (b->find(name) != b->end())
			return true;
		else
			return false;
	}
	
}

bool BpTree::searchRange(string start, string end) {
	return true;
}

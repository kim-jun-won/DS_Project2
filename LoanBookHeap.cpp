                                                                                                                                                                                                                              #include "LoanBookHeap.h"
#include <queue>

queue<LoanBookHeapNode*> q;

// find lastheapNode
LoanBookHeapNode* FindlastHeapNode(LoanBookHeapNode* pN)
{
    // pN is root
    LoanBookHeapNode* cur = pN;
    // if there is only one node
    if (cur->getLeftChild() == nullptr && cur->getRightChild() == nullptr) {
        return cur;
    }

    // Use a single queue
    std::queue<LoanBookHeapNode*> q;
    q.push(cur);

    // Traverse the heap using the queue
    while (!q.empty())
    {
        cur = q.front();
        q.pop();

        // if cur's left child is not nullptr, push it into the queue
        if (cur->getLeftChild() != nullptr) {
            q.push(cur->getLeftChild());
        }
        // if cur's right child is not nullptr, push it into the queue
        if (cur->getRightChild() != nullptr) {
            q.push(cur->getRightChild());
        }
    }

    // The last node will be the last element dequeued from the queue
    return cur;
}

// heapifyup
void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
	LoanBookHeapNode* cur = pN;
	if(cur->getParent() == nullptr) return;
	// while cur is not nullptr and cur's parent Node book name is bigger than cur's bookName
	while (cur->getParent() != nullptr && 
				cur->getParent()->getBookData()->getName() > cur->getBookData()->getName())
	{
		LoanBookData* copy = cur->getParent()->getBookData();
		cur->getParent()->setBookData(cur->getBookData());
		cur->setBookData(copy);

		cur = cur->getParent();
	}
}
// heapifyDown
void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
	
	LoanBookHeapNode* lastnode = FindlastHeapNode(pN); // save pointer in lasnode
	LoanBookHeapNode* p = lastnode->getParent();	   // set p as lastnode's parent

	LoanBookData* lastdata = lastnode->getBookData(); // save lastnode's data in lastdata

	// if p is nullptr -> heap has only one data
	if (p == nullptr) {
		this->setRoot(nullptr); // set root as nullptr
		return;
	}
	// if root's leftchidl or rightchild is lastNode
	if (p->getLeftChild() == lastnode) p->setLeftChild(nullptr);
	else if (p->getRightChild() == lastnode) p->setRightChild(nullptr);

	pN->setBookData(lastdata);

	LoanBookHeapNode* cur = pN;

	while (cur->getLeftChild() != nullptr || cur->getRightChild() != nullptr) {
		// declare largerChidle
		LoanBookHeapNode* largerChild = nullptr;
		// save largerChild as less alphabetic order
		if (cur->getRightChild() == nullptr ||
			(cur->getLeftChild()->getBookData()->getName() < cur->getRightChild()->getBookData()->getName())) {
			largerChild = cur->getLeftChild();
		}
		else {
			largerChild = cur->getRightChild();
		}

		// change cur and largerChidle
		if (cur->getBookData()->getName() > largerChild->getBookData()->getName()) {
			LoanBookData* copy = cur->getBookData();
			cur->setBookData(largerChild->getBookData());
			largerChild->setBookData(copy);

			cur = largerChild;
		}
		// if largerchild's order is less than cur's order
		else {
			break; // break
		}
	}
}
// insert
bool LoanBookHeap::Insert(LoanBookData* data) {

	// if heap is empty
	if (root == nullptr)
	{
		LoanBookHeapNode* newNode = new LoanBookHeapNode(); // create newNode
		root = newNode; // set root as newNode
		newNode->setBookData(data); // set data in newNode
		return true; // return true
	}
	else if (root->getLeftChild() == nullptr) // if root's left is nullptr -> insert data in left
	{
		LoanBookHeapNode* newNode = new LoanBookHeapNode();
		root->setLeftChild(newNode);
		newNode->setParent(root);
		newNode->setBookData(data);
		heapifyUp(newNode);
		return true;
	}
	else if (root->getRightChild() == nullptr) // ir root's right is nullptr -> insert data in right
	{
		LoanBookHeapNode* newNode = new LoanBookHeapNode();
		root->setRightChild(newNode);
		newNode->setParent(root);
		newNode->setBookData(data);
		heapifyUp(newNode);
		return true;
	}
	// data inserted in location that depth is more than 3
	else
	{
		queue<LoanBookHeapNode*> q2;

		LoanBookHeapNode* cur = root; // Pointer to the current node, starting from the root
		LoanBookHeapNode* pcur = nullptr; // Pointer to the parent node of the current node

		LoanBookHeapNode* newNode = new LoanBookHeapNode(); // Create a new heap node
		newNode->setBookData(data); // Set the book data for the new node
		// Traverse the heap to find the first available position for insertion
		while (cur->getLeftChild() != nullptr && cur->getRightChild() != nullptr)
		{
			q2.push(cur->getLeftChild()); q2.push(cur->getRightChild());
			// Enqueue the left child         // Enqueue the right child
			cur = q2.front();  // Move to the next level
			if(!q2.empty()) q2.pop();
		}

		// Check if the left child of the current node is null
		if (cur->getLeftChild() == nullptr)
		{
			cur->setLeftChild(newNode); // Set the new node as the left child
			newNode->setParent(cur);   // Set the current node as the parent of the new node

		}
		// Check if the right child of the current node is null
		else if (cur->getRightChild() == nullptr)
		{
			cur->setRightChild(newNode);   // Set the new node as the right child
			newNode->setParent(cur);       // Set the current node as the parent of the new node
		}
		// heapfiyUp
		heapifyUp(newNode);

		
		return true;
	}
}



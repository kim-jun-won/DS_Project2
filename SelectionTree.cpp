#include "SelectionTree.h"
#include <map>
// indorder traversal to save data in ascending order
void inorder(map<string, LoanBookData*>* print, LoanBookHeapNode* cur)
{
	pair<string, LoanBookData*> a;
	if (cur->getLeftChild() != nullptr) // if cur's left child is not nullptr
	{
		inorder(print, cur->getLeftChild()); // inorder(print,cur's leftchild)
	}
	if (cur->getRightChild() != nullptr) // if cur's right child is not nullptr
	{
		inorder(print, cur->getRightChild()); // inorder(print, cur's rightchild)
	}
	a.first = cur->getBookData()->getName();
	a.second = cur->getBookData();
	print->insert(a); // insert a in print

}

// Insert newData in Selection Tree
bool SelectionTree::Insert(LoanBookData* newData) {
	
	// set code as code/100
	int code = (newData->getCode()) / 100;
	// save heaproot as winnerTree's appropriate heap
	LoanBookHeap* heaproot = winner[code+8].getHeap();
	if (heaproot != nullptr) // if heaproot is not nullptr
	{
		heaproot->Insert(newData); // add data in heaproot
	}
	else if (heaproot == nullptr) // if heaproot is nullptr
	{
		LoanBookHeap* newheap = new LoanBookHeap(); // create new heap
		newheap->Insert(newData);
		winner[code + 8].setHeap(newheap);
	}
	
        LoanBookData* insertdata = winner[code+8].getHeap()->getRoot()->getBookData();

	winner[code + 8].setBookData(insertdata);

	// rearragne selction Tree
	int k = 8;
	int j = k;
	for (int i = k - 1; i >= k / 2 && j != 1; i--)
	{
		if (winner[j+7].getBookData()->getName() > winner[j + 6].getBookData()->getName())	{
			winner[i].setBookData(winner[j+6].getBookData());
		}
		else {
			winner[i].setBookData(winner[j+7].getBookData());
		}
		j -= 2;
	}
	
	for (int i = k / 2 - 1; i >= 1; i--)
	{
		int j = 2 * i;
		if (winner[j].getBookData()->getName() > winner[j + 1].getBookData()->getName()) {
			winner[i].setBookData(winner[j + 1].getBookData());
		}
		else {
			winner[i].setBookData(winner[j].getBookData());
		}

	}

	root->setBookData(winner[1].getBookData());

	return true;
}
// delete root Node in SelectionTree
bool SelectionTree::Delete() {
	if (root == nullptr) return false;
	int n = 0;
	LoanBookData* data = new LoanBookData();
	data->setBookData("{", 0, " ", 0);
	// While traversing the winnertree, if a selectiontree node with the same name as the root is encountered, a default value is added there.
	for (int i = 1; i <= 15; i++)
	{
		if (winner[i].getBookData()->getName() == root->getBookData()->getName())
		{
			winner[i].setBookData(data);
			if (i >= 8)
			{
				winner[i].getHeap()->heapifyDown(winner[i].getHeap()->getRoot());
				n = i;
				break;
			}
		}
	}
	LoanBookHeap* heaproot = winner[n].getHeap();
	
	// if heapdata is more than two
	if (heaproot->getRoot() != nullptr)
	{
		winner[n].setBookData(heaproot->getRoot()->getBookData());
	}
	
	// winner tree rearragne
	int k = 8;
	int j = k;
	for (int i = k - 1; i >= k / 2 && j != 1; i--)
	{
		if (winner[j + 7].getBookData()->getName() > winner[j + 6].getBookData()->getName()) {
			winner[i].setBookData(winner[j + 6].getBookData());
		}
		else {
			winner[i].setBookData(winner[j + 7].getBookData());
		}
		j -= 2;
	}

	for (int i = k / 2 - 1; i >= 1; i--)
	{
		int j = 2 * i;
		if (winner[j].getBookData()->getName() > winner[j + 1].getBookData()->getName()) {
			winner[i].setBookData(winner[j + 1].getBookData());
		}
		else {
			winner[i].setBookData(winner[j].getBookData());
		}

	}

	root->setBookData(winner[1].getBookData());

	return true;
}

bool SelectionTree::printBookData(int bookCode) {
	// Extract the group number from the book code
	bookCode = bookCode / 100;
	LoanBookHeap* heap = winner[bookCode + 8].getHeap();

	if (heap != nullptr && heap->getRoot() == nullptr) // Check if the heap at the corresponding winner tree node is empty
	{
		return false; // Return false if the heap is empty
	}
	else {
		LoanBookHeap * print = winner[bookCode + 8].getHeap(); // Get the root of the heap to start the traversal
		LoanBookHeapNode* cur = print->getRoot();
		// Output header for the printed data
		*fout << "================PRINT_ST==================\n";
		map<string, LoanBookData*> a;  // Create a map to store book data during the inorder traversal
		inorder(&a, cur);
		auto itr = a.begin();
		while (itr != a.end())
		{
			*fout << itr->second->getName() << "/" << itr->second->getCode() << "/" << itr->second->getAuthor()
				<< "/" << itr->second->getYear() << "/" << itr->second->getLoanCount() << '\n';
			itr++;
		
		}
		
		*fout << "===========================================\n";
	}

	return true;
}






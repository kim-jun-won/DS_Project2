#include "Manager.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> vs;
	string temp;

	for (int i = 0; !(str[i] == 13  || str[i] == '\n' || str[i] == 0); i++)
	{
		if (str[i] == delimiter) 
		{
			vs.push_back(temp);
			temp.clear();

			continue;
		}

	
		temp.push_back(str[i]);
	}

	vs.push_back(temp); 

	return vs;
}

void Manager::run(const char* command)
{
	fin.open(command);
	flog.open("log.txt");

	if (!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}

	string line;
	vector<string> a; 
	while (!fin.eof()) // while fin is not end of file 
	{
		getline(fin, line); // geline
		a = split(line, '\t'); // save splited data in a
		// empty line
		if (a.size() == 0) 
		{
			cout << "Read Empty line";
		}
		// load
		else if (a.size()==1 && a[0] == "LOAD")
		{
			std::cout << "LOAD" << endl;
			if (LOAD()) printSuccessCode(a[0]);
			else printErrorCode(100);
		}
		else if (a[0] == "ADD")
		{
			if (a.size() == 5) {
				LoanBookData* newData = new LoanBookData; // create newData
				newData->setBookData(a[1], stoi(a[2]), a[3], stoi(a[4])); // set newDAta
				bool flag = bptree->Insert(newData);
				flog << "==========" << "ADD" << "==========\n";
				flog << a[1] << "/" << a[2] << "/" << a[3] << "/" << a[4] << '\n';
				flog << "===================================\n\n";
				if (!flag) // if flag is false insert data in selection Tree
				{
					this->stree->Insert(newData);
				}
			}
			else{ // if commmand form is not appropriate printErrorCode
				printErrorCode(200);
			}
		}
// search_bp
		else if (a[0] == "SEARCH_BP")
		{
			if (a.size() == 2) // Search bp name
				SEARCH_BP_BOOK(a[1]);
			else if (a.size() == 3) // Search bp range
				SEARCH_BP_RANGE(a[1], a[2]);
			else // else print Error code
				printErrorCode(300);
		}
		// print_bp
		else if(a.size()==1 && a[0] == "PRINT_BP")
		{
			PRINT_BP();
		}
		else if (a.size() == 2 && a[0] == "PRINT_ST")
		{
			PRINT_ST(stoi(a[1]));
		}
		else if (a.size() == 1 && a[0] == "DELETE")
		{
			if (DELETE()) printSuccessCode(a[0]);
			else printErrorCode(600);
		}

		a.clear();
		
	}

	fin.close(); // fin close
	flog.close(); // flog close
	return;
}

// LOAD
bool Manager::LOAD()
{
	ifstream a;
	a.open("Loan_Book.txt"); // open Loan_Book.txt
	if (!a){ // if cannot open file
		return false; // return false
	}

	string line;
	vector<string> data; // vector data to save splited data

	while (!a.eof()) // while a is not end of file
	{
		getline(a, line);
		data = split(line, '\t'); // save splited data in deimeter tab
		if (data.size() == 5) // create new book data an insert in bptree
		{
			LoanBookData* newdata = new LoanBookData; 
			newdata->setBookData(data[0], stoi(data[1]), data[2], stoi(data[3]));
			bptree->Insert(newdata);
		}
		data.clear(); // dat clear to save next data
	}
	a.close(); // close a
	return true;
}

bool Manager::ADD()
{
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book)
{
	BpTree* cur = bptree; // set cur as bptree pointer
	if (!cur->searchBook(book)) // if cannot find book data
	{
		printErrorCode(300); // print error code
		return false;
	}
	else {
		BpTreeNode* pcur = cur->searchDataNode(book); // set pcur as searchNode
		if (pcur->getIndexMap() != nullptr) // if pcur is indexNode
		{
			while (pcur->getMostLeftChild() != nullptr) // while pcur->GetMostChidle is not nullptr
				pcur = pcur->getMostLeftChild(); // change pcur

			while (pcur != nullptr) // while pcur is not nullptr
			{
				// go round DataNode and print target data
				auto itr = pcur->getDataMap();
				auto iter = itr->find(book);
				if (iter != itr->end())
				{
					flog << "===========" << "SEARCH_BP" << "===============" << '\n';
					flog << iter->second->getName() << "/" << iter->second->getCode() << "/"
						<< iter->second->getAuthor() << "/" << iter->second->getLoanCount() << '\n';
					flog << "===============================================" << "\n\n";

					return true;
				}
				pcur = pcur->getNext();
			}
		} // else if pcur is DataNode
		else
		{
			// go aroutn dataNode and print target data 
			auto iter = pcur->getDataMap()->begin();
			while (1)
			{
				if (iter->first == book)
				{
					flog << "===========" << "SEARCH_BP" << "===============" << '\n';
					flog << iter->second->getName() << "/" << iter->second->getCode() << "/"
						<< iter->second->getAuthor() << "/" << iter->second->getLoanCount() << '\n';
					flog << "===============================================" << "\n\n";
					break;
				}
				iter++;
			}
		}
		
	}
	return true;
}

// search bp _range
bool Manager::SEARCH_BP_RANGE(string s, string e)
{
	BpTree* cur = bptree; // set cur as this->Bptree 
	// if root is nullptr printErrorcocde
	if (cur->getRoot() == nullptr)
	{
		printErrorCode(400);
		return false;
	}

	// set k as rrot pointer and set k as left most dataNode
	BpTreeNode* k = cur->getRoot();
	while (k->getMostLeftChild() != nullptr)
	{
		k = k->getMostLeftChild();
	}

	// while iter data is bigger than start and smaller than last
	flog << "===========" << "SEARCH_BP" << "===============" << '\n';
	while (k != nullptr)
	{
		auto iter = k->getDataMap()->begin();
		while (iter != k->getDataMap()->end())
		{
			if (iter->first >= s && iter->first <= e)
			{
				// print data
				flog << iter->second->getName() << "/" << iter->second->getCode() << "/"
					<< iter->second->getAuthor() << "/" << iter->second->getLoanCount() << '\n';
			}
			else if (iter->first > e) break; // if searching data is bigger than last break

			iter++;
		}
		k = k->getNext();
	}
	flog << "===============================================" << "\n\n";

	return true;
}

bool Manager::PRINT_BP() // print BP
{
	BpTree* cur = this->bptree;
	if (cur->getRoot() == nullptr) // if bptree root is nullptr print error code
	{
		printErrorCode(400);
		return false;
	}

	BpTreeNode* k = cur->getRoot(); // set k as rrot pointer and set k as left most dataNode
	while (k->getMostLeftChild() != nullptr)
	{
		k = k->getMostLeftChild();
	}
	flog << "==========" << "PRINT_BP" << "==========" << '\n';
	// while k is not nullptr print data
	while (k != nullptr)
	{
		auto iter = k->getDataMap()->begin();
		while (iter != k->getDataMap()->end())
		{
			flog << iter->second->getName() << "/" << iter->second->getCode() << "/" 
				<< iter->second->getAuthor() << "/" << iter->second->getLoanCount() << '\n';
			iter++;
		}
		k = k->getNext();
	}
	flog << "========================================" << "\n\n";

	return true;
}

bool Manager::PRINT_ST(int code)
{
	if (!this->stree->printBookData(code)) // if printBookData is false
	{
		printErrorCode(500);
		return false;
	}

	return true;
}

bool Manager::DELETE()
{
	if (!stree->Delete()) return false;
	else return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(string &name) {//SUCCESS CODE PRINT 
	flog << "===========" <<  name << "============" << endl;
	flog << "Success" << endl;
	flog << "=====================================" << endl << endl;
}


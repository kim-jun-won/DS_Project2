#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
	}
	~Manager() //destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ofstream flog;


	void run(const char* command);
	bool LOAD();
	bool ADD();

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(int bookcode);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string &name);

};


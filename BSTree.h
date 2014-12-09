// BSTree.h				
// contains the BSTree class definitions.
#ifndef BSTREE_H
#define BSTREE_H
#include "Account.h"

class BSTree 
{
public:
	BSTree();
	virtual ~BSTree();

	bool Insert(Account* account);
	bool Retreive(const Account &toRetreieve, Account *&accountPtr) const;
	bool Retreive(int accountNumber, Account *&accountPtr) const;
	void Display() const;
	void Empty();
	bool isEmpty() const;

private:
	struct Node 
	{
		Node();
		Node(Account *accPtr);
		Account *pAcct;
		Node *right;
		Node *left;
	};
	Node *root;

	void Insert(Account* account, Node*& position);
	void Empty(Node* node);
	void Display(Node* node) const;
};

#endif
// BSTree.cpp			
// contains the BSTree class declarations.
#ifndef BSTREE_CPP
#define BSTREE_CPP
#include "BSTree.h"

BSTree::BSTree() : root(nullptr) {}
BSTree::Node::Node() : pAcct(nullptr), right(nullptr), left(nullptr) {}
BSTree::Node::Node(Account* account) : pAcct(account), right(nullptr), left(nullptr) {}

BSTree::~BSTree() 
{
	Empty();
}

bool BSTree::Insert(Account* account) 
{
	Insert(account, root);
	return(true);
}

void BSTree::Insert(Account* account, Node*& position) 
{
	if(position == nullptr) 
	{
		position = new Node(account);
	} 
	else 
	{
		if(*account < *position->pAcct) 
		{
			Insert(account, position->left);
		} 
		else 
		{
			Insert(account, position->right);
		}
	}
}

bool BSTree::Retreive(const Account &toRetreieve, Account *&accountPtr) const 
{
	Node* position = root;
	while(position != nullptr) 
	{
		if(toRetreieve == *position->pAcct) 
		{
			accountPtr = position->pAcct;
			return(true);
		} 
		else if(toRetreieve < *position->pAcct) 
		{
			position = position->left;
		} 
		else 
		{
			position = position->right;
		}
	}
	accountPtr = nullptr;
	return(false);
}

bool BSTree::Retreive(int accountNumber, Account *&accountPtr) const 
{
	Node* position = root;
	while(position != nullptr) 
	{
		if(accountNumber == position->pAcct->getAccountID()) 
		{
			accountPtr = position->pAcct;
			return(true);
		} 
		else if(accountNumber < position->pAcct->getAccountID()) 
		{
			position = position->left;
		} 
		else 
		{
			position = position->right;
		}
	}
	accountPtr = nullptr;
	return(false);
}

void BSTree::Display() const 
{
	Display(root);
}

void BSTree::Display(Node* node) const 
{
	if(node != nullptr)
	{
		Display(node->left);
		cout << *node->pAcct << endl;
		Display(node->right);
	}
}

void BSTree::Empty() 
{
	Empty(root);
}

void BSTree::Empty(Node* node) 
{
	if(node != nullptr) 
	{
		Empty(node->left);
		Empty(node->right);
		delete node->pAcct;
		delete node;
	}
}

bool BSTree::isEmpty() const 
{
	return(root == nullptr);
}
#endif
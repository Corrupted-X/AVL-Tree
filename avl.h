// ----------------------------------------------------
// Authors: Patrick Vandergrift
// Course-Section: CS355-01
// Assignment: Project 7
// Date due: 11/25/2025
// Description: This program is a AVL tree
// ----------------------------------------------------
#include <iostream>
using namespace std;


//Struct AVLNode
/********************************************************
Purpose: This is a struct that contains info about each node in
	the AVL tree
Public:  elemType info; int bfactor; AVLNode<elemType> *link;
	AVLNode<elemType> *rlink;
**********************************************************/
template <class elemType>
struct AVLNode
{
	elemType info;
	int bfactor;
	AVLNode<elemType> *lLink;
	AVLNode<elemType> *rLink;
};


//CLASS Area
/********************************************************
Purpose: This class creates an AVL tree
Private: void inorderPrint(AVLNode<elemType>* p)const;
	void postOrderPrint(AVLNode<elemType>* p)const;
	void preOrderPrint(AVLNode<elemType>* p)const;
Public:  Operations upon the AVL tree
methods: AVLType();
	void rotateToLeft(AVLNode<elemType>* &root);
	void rotateToRight(AVLNode<elemType>*& root);
	void balanceFromLeft(AVLNode<elemType>*& root);
	void balanceFromRight(AVLNode<elemType>*& root);
	void insertIntoAVL(AVLNode<elemType>*& root, AVLNode<elemType>* newNode);
	void insert(const elemType &newItem);
**********************************************************/
template <class elemType>
class AVLType
{
private:
	AVLNode<elemType>* root;
	int size;
	void inorderPrint(AVLNode<elemType>* p)const;	//Helper Inorder Print
	void postOrderPrint(AVLNode<elemType>* p)const;	//Helper Post-order Print
	void preOrderPrint(AVLNode<elemType>* p)const;	//Helper Pre-order Print
public:
	AVLType();	//Constructor
	AVLType(const AVLType<elemType>& oldCopy);		//Copy Constructor
	void rotateToLeft(AVLNode<elemType>* &root);	//Left Rotation
	void rotateToRight(AVLNode<elemType>*& root);	//Right Rotation
	void balanceFromLeft(AVLNode<elemType>*& root);		//Left Balance
	void balanceFromRight(AVLNode<elemType>*& root);	//Right Balance
	void insertIntoAVL(AVLNode<elemType>*& root, AVLNode<elemType>* newNode, bool& isTaller);
	void insert(const elemType &newItem);	//Insert
	void inorderTraversal()const;	//In-Order Print
	void preOrderTraversal()const;	//Pre-Order Print
	void postOrderTraversal()const;	//Post-Order Print
	void copyTree(AVLNode<elemType>*& newCopy, AVLNode<elemType>* oldCopy);	//Copy
	AVLType& operator=(const AVLType& oldCopy);		//Overloader
};

//AVLType<elemType>& operator=
/********************************************************
Purpose:  assignment operator overloader
Incoming: const AVLType<elemType&> oldCopy
Outgoing: Nothing
**********************************************************/
template<class elemType>
AVLType<elemType>& AVLType<elemType>::operator=(const AVLType<elemType>& oldCopy)
{
	if (this != &oldCopy)
	{
		copyTree(root, oldCopy.root);
	}
	return *this;
}

//AVLType<class elemType> AVLType
/********************************************************
Purpose:  Copy Constructor
Incoming: const AVLType<elemType&> oldCopy
Outgoing: Nothing
**********************************************************/
template<class elemType>
AVLType<elemType>::AVLType(const AVLType<elemType>& oldCopy)
{
	root = copyTree(root, oldCopy.root);
}

//AVLType<class elemType> AVLType
/********************************************************
Purpose:  Constructor
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
template<class elemType>
AVLType<elemType>::AVLType()
{
	root = nullptr;
	size = 0;
}

//void rotateToLeft
/********************************************************
Purpose:  Rotates elements left to meant the requirements
	for an AVL tree
Incoming: AVLNode<elemType>*& root
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::rotateToLeft(AVLNode<elemType>*& root)
{
	AVLNode<elemType>* p;

	if (root == nullptr)	//Case: Tree is empty
	{
		cout << "Error: Tree is empty" << endl;
	}
	else if (root->rLink == nullptr)	//Case: No right subtree
	{
		cout << "Error: Failed Rotation" << endl;
		cout << "Cause: No Right subtree" << endl;
	}
	else	//Case: Left Rotation
	{
		p = root->rLink;		
		root->rLink = p->lLink;	//Right subtree of p becomes Left subtree of the root

		p->lLink = root;		
		root = p;				//P becomes the new root value
	}
}

//void rotateToRight
/********************************************************
Purpose:  Rotates elements right to meant the requirements
	for an AVL tree
Incoming: AVLNode<elemType>*& root
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::rotateToRight(AVLNode<elemType>*& root)
{
	AVLNode<elemType>* p;

	if (root == nullptr)	//Case: Tree is empty
	{
		cout << "Error: Tree is empty" << endl;
	}
	else if (root->lLink == nullptr)	//Case: No left subtree
	{
		cout << "Error: Failed Rotation" << endl;
		cout << "Cause: No Left subtree" << endl;
	}
	else	//Case: Left Rotation
	{
		p = root->lLink;
		root->lLink = p->rLink;	//Left subtree of p becomes Right subtree of the root

		p->rLink = root;
		root = p;				//P becomes the new root value
	}
}

//void balanceFromLeft
/********************************************************
Purpose:  Corrects Balances for left subtree elements
Incoming: AVLNode<elemType>*& root
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::balanceFromLeft(AVLNode<elemType>*& root)
{
	AVLNode<elemType>* p;
	AVLNode<elemType>* w;

	p = root->lLink;

	switch (p->bfactor)
	{
	case -1:
		root->bfactor = 0;
		p->bfactor = 0;
		rotateToRight(root);
		break;
	case 0:
		cout << "Error: Failed to balance from the left" << endl;
		break;
	case 1:
		w = p->rLink;
		switch (w->bfactor)	//Logic: Adjust Balance Factors
		{
		case -1:
			root->bfactor = 1;
			p->bfactor = 0;
			break;
		case 0:
			root->bfactor = 0;
			p->bfactor = 0;
			break;
		case 1:
			root->bfactor = 0;
			p->bfactor = -1;
		}
		w->bfactor = 0;
		rotateToLeft(p);
		root->lLink = p;
		rotateToRight(root);
	}
}


//void balanceFromRight
/********************************************************
Purpose:  Corrects Balances for right subtree elements
Incoming: AVLNode<elemType>*& root
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::balanceFromRight(AVLNode<elemType>*& root)
{
	AVLNode<elemType>* p;
	AVLNode<elemType>* w;

	p = root->rLink;
	
	switch (p->bfactor)
	{
	case -1:
		w = p->lLink;
		switch (w->bfactor) //Logic: Adjust Balance Factors
		{
		case -1:
			root->bfactor = 0;
			p->bfactor = 1;
			break;
		case 0:
			root->bfactor = 0;
			p->bfactor = 0;
			break;
		case 1:
			root->bfactor = -1;
			p->bfactor = 0;
		}	//Logic End

		w->bfactor = 0;
		rotateToRight(p);
		root->rLink = p;
		rotateToLeft(root);
		break;
	case 0:
		cout << "Error: Failed to Balance from the Right" << endl;
		break;
	case 1:
		root->bfactor = 0;
		p->bfactor = 0;
		rotateToLeft(root);
	}//Switch End
}


//void insertIntoAVL
/********************************************************
Purpose:  Inserts elements into the AVL tree
Incoming: AVLNode<elemType>*& roo,t AVLNode<elemType>* newNode, 
	bool& isTaller
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::insertIntoAVL(AVLNode<elemType>*& root, 
	AVLNode<elemType>* newNode, bool& isTaller)
{
	if (root == nullptr)
	{
		root = newNode;
		isTaller = true;
	}
	else if(root->info == newNode->info)
	{
		cout << "Error: No Duplicates: " << newNode->info  << endl;
	}
	else if(root->info > newNode->info)
	{
		insertIntoAVL(root->lLink, newNode, isTaller);	//Insert

		if (isTaller)	//Logic: Left Subtree height after Insertion
		{
			switch (root->bfactor)
			{
			case -1:
				balanceFromLeft(root);
				isTaller = false;
				break;
			case 0:
				root->bfactor = -1;
				isTaller = true;
				break;
			case 1:
				root->bfactor = 0;
				isTaller = false;
			}
		}//Logic End
	}
	else
	{
		insertIntoAVL(root->rLink, newNode, isTaller);	//Insert

		if (isTaller)	//Logic: Right Subtree height after Insertion
		{
			switch (root->bfactor)
			{
			case -1:
				root->bfactor = 0;
				isTaller = false;
				break;
			case 0:
				root->bfactor = 1;
				isTaller = true;
				break;
			case 1:
				balanceFromRight(root);
				isTaller = false;
			}
		}//Logic End
	}
}	//End InsertIntoAVL


//void insert
/********************************************************
Purpose:  Allows users to input new nodes in the AVL tree
Incoming: const elemType& newItem
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::insert(const elemType& newItem)
{
	bool isTaller = false;
	AVLNode<elemType>* newNode;

	newNode = new AVLNode<elemType>;
	newNode->info = newItem;
	newNode->bfactor = 0;
	newNode->lLink = nullptr;
	newNode->rLink = nullptr;

	insertIntoAVL(root, newNode, isTaller);
}

//void inorderTraversal
/********************************************************
Purpose:  Prints AVL in order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::inorderTraversal()const
{
	inorderPrint(root);
}

//void inorderPrint
/********************************************************
Purpose:  Helps to Print AVL in order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::inorderPrint(AVLNode<elemType>* p)const
{
	if (p != nullptr)
	{
		inorderPrint(p->lLink);
		cout << p->info << endl;;
		inorderPrint(p->rLink);
	}
}

//void postOrderTraversal
/********************************************************
Purpose:  Prints AVL post-order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::postOrderTraversal()const
{
	postOrderPrint(root);
}

//void postOrderPrint
/********************************************************
Purpose:  Helps to Print AVL post-order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::postOrderPrint(AVLNode<elemType>* p)const
{
	if (p != nullptr)
	{
		postOrderPrint(p->lLink);
		postOrderPrint(p->rLink);
		cout << p->info << endl;
	}
}

//void preOrderTraversal
/********************************************************
Purpose:  Prints AVL pre-order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::preOrderTraversal()const
{
	preOrderPrint(root);
}

//void preOrderPrint
/********************************************************
Purpose:  Helps to Print AVL pre-order
Incoming: AVLNode<elemType>* p
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::preOrderPrint(AVLNode<elemType>* p)const
{
	if (p != nullptr)
	{
		cout << p->info << endl;
		preOrderPrint(p->lLink);
		preOrderPrint(p->rLink);
	}
}

//void copyAVL
/********************************************************
Purpose:  Copys the AVL tree
Incoming: AVLNode<elemType>*& newCopy, 
	AVLNode<elemType>* oldCopy
Outgoing: Nothing
**********************************************************/
template<class elemType>
void AVLType<elemType>::copyTree(AVLNode<elemType>*& newCopy, 
	AVLNode<elemType>* oldCopy)
{
	if (oldCopy == nullptr)
	{
		newCopy = nullptr;
	}
	else
	{
		newCopy = new AVLNode<elemType>;
		newCopy->info = oldCopy->info;
		newCopy->bfactor = oldCopy->bfactor;
		copyTree(newCopy->lLink, oldCopy->lLink);
		copyTree(newCopy->rLink, oldCopy->rLink);
	}
}
// ----------------------------------------------------
// Authors: Patrick Vandergrift
// Course-Section: CS355-01
// Assignment: Project 7
// Date due: 11/25/2025
// Description: This program is a AVL tree
// ----------------------------------------------------
#include <iostream>
#include <ctime>
#include "avl.h"
using namespace std;


//******************************
//DRIVER
//*******************************

int main()
{
	AVLType<int> avl, avl2;
	int value = 0;
	srand(time(0));
	for (int i=0; i<5; i++)
	{
		value = rand() % 100;
		avl.insert(value);
	}

	cout << "In-Order List Traversal" << endl;
	avl.inorderTraversal();
	cout << "Pre-Order List Traversal" << endl;
	avl.preOrderTraversal();
	cout << "Post-Order List Traversal" << endl;
	avl.postOrderTraversal();

	cout << endl;
	cout << "Copying" << endl;
	avl2 = avl;
	
	cout << "Copied In-Order List Traversal" << endl;
	avl2.inorderTraversal();

	return 0;
}
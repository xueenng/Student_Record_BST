
#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include<string>


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

int BST::getHeight(BTNode* cur) {
	if (cur == NULL) return -1;

	int leftHeight = getHeight(cur->left);
	int rightHeight = getHeight(cur->right);

	// Return the largest value + 1 for root edge (keep accumulating everytime return to caller)
	return max(leftHeight, rightHeight) + 1;
}


// Find and print all the nodes (student id) at the deepest level 
bool BST::deepestNodes() {

	// Variable declaration
	int nodeCount = 0;

	// Return false for empty tree
	if (root == NULL) return false;

	deepestNodes2(root, getHeight(root), nodeCount);
	return true;
}

void BST::deepestNodes2(BTNode* cur, int level, int& nodeCount) {

	// Return if the cur pointer is NULL
	if (!cur) return;
	else if (level == 0) {
		++nodeCount;
		cout << "Deepest node " << nodeCount << ": " << cur->item.id << endl;
	}
	else {
		deepestNodes2(cur->left, level - 1, nodeCount);
		deepestNodes2(cur->right, level - 1, nodeCount);
	}
}



//fucntion needed to print tree according to order
void BST::printTree(BTNode* cur, int& order, ostream& out) {
	if (cur == NULL) { //node is empty
		return;
	}

	if (order == 1)//ascending
	{
		printTree(cur->left, order, out);
		cur->item.print(out);//print to file/ screen
		printTree(cur->right, order, out);
	}
	else if (order == 2)//descending
	{
		printTree(cur->right, order, out);
		cur->item.print(out);//print to file/ screen
		printTree(cur->left, order, out);
	}

}

// Display the contents of the BST in descending or ascending order to the screen or to file based on user's selection
bool BST::display(int order, int source) {//  order: 1-ascending/ 2-descending     source: 1-screen/ 2-file
	if (empty()) // empty tree
		return false;


	if (source == 2) {//file
		ofstream out;
		out.open("student-info.txt");
		if (out.fail()) {
			cout << "Unable to open file" << endl;
			return false;

		}
		else {
			cout << "The information has been successfully printed to [student-info.txt] " << endl;
			printTree(root, order, out);

		}
		out.close();
	}
	else
	{
		printTree(root, order, cout);//screen
	}
	return true;
}

//This function is use to clone the subtree of the item
void BST::CloneSubChild(BTNode* ptr) {
	if (ptr == NULL)//base case
		return;
	else {//recursive case
		insert(ptr->item);
		CloneSubChild(ptr->left);
		CloneSubChild(ptr->right);
	}
}

//This function use to find the student id
BTNode* BST::finditem(BTNode* curitem, type item) {
	if (curitem == NULL) {//return the curitem pointer if item(studentID) cannot be found after traverse the tree
		return curitem;
	}

	if (item.id == curitem->item.id) {//if student id is found
		return curitem;
	}
	else if (curitem->item.id > item.id) {//if the current pointer studentID is more than the search student ID
		return finditem(curitem->left, item);
	}
	else {
		return finditem(curitem->right, item);
	}
}


bool BST::CloneSubtree(BST t1, type item) {
	BTNode* curitem = finditem(t1.root, item);
	if (t1.root == NULL) {
		cout << "t1 is empty!\n";
		return false;
	}
	else if (curitem == NULL) {
		cout << "Student ID cannot be found!\n";
		return false;
	}
	else {
		//clone the subtree of the item
		CloneSubChild(curitem);
		//display t1 and t2
		cout << string(80, '=') << endl;
		cout << "Display PreOrderPrint t1: \n";
		t1.preOrderPrint();
		cout << "\n";
		cout << string(80, '=') << endl;
		cout << "\nDisplay PreOrderPrint t2: \n";
		preOrderPrint();
		return true;

	}
}

//Print out the nodes level by level
bool BST::printLevelNodes() {
	if (root == NULL) {
		return false;
	}

	Queue q;
	q.enqueue(root);

	int level = 1;

	while (!q.empty()) {
		int nodesInLevel = q.size();
		cout << "Level " << level << " nodes:";

		for (int i = 0; i < nodesInLevel; i++) {
			BTNode* cur;
			q.dequeue(cur);

			Student student = cur->item;  // Assuming cur->item is a Student object
			cout << " " << student.id;

			if (cur->left != NULL)
				q.enqueue(cur->left);
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}

		cout << endl;
		level++;
	}

	return true;
}

bool BST::printPath() {
	if (root == NULL) {
		cout << "Error!! Tree is empty. Please read the file first!" << endl;
		return false;
	}

	// Call function to print the paths starting from the root
	printExternalPaths(root, "");

	return true;
}

void BST::printExternalPaths(BTNode* cur, string path) {
	if (cur == NULL) {
		return;
	}

	// Append the current student ID to the path
	path += to_string(cur->item.id) + " ";

	// If it is a leaf node (external path), print the path
	if (cur->left == NULL && cur->right == NULL) {
		cout << path << endl;
	}

	// Recursively call for left and right subtrees
	printExternalPaths(cur->left, path);
	printExternalPaths(cur->right, path);
}

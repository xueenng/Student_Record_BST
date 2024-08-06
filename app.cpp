
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<iomanip>		
#include	"BST.h"
#include    "Student.h"

using namespace std;


/* Assignment functions */
bool readFile(const char*, BST*);
int menu();
bool CheckFile(string);			// To check file if it is empty or exist
int getIntegerInput();

//function to validate integer input 
int getIntegerInput() {

	int input;

	while (true) {

		cin >> input;

		if (cin.fail()) { // Check if input is not integer

			cin.clear(); // Clear error flags 

			cin.ignore(10000, '\n'); // Ignore invalid input 

			cout << "Invalid input.\n\nPlease enter an integer:"; //prompt user to enter integer input

		}

		else {

			cin.ignore(10000, '\n'); // Ignore any extra characters 

			return input;

		}

	}

}


/* Main Function */
int main() {

	// Variable declaration
	BST t1;
	type stu;
	bool next = true;
	char fileName[100];


	// Main function
	do {

		system("cls");

		switch (menu())
		{
		case 1:

			system("cls");

			cout << "\nREAD DATA TO BST\n";
			cout << "=====================================================\n";
			cout << "Enter student record file to be read: ";
			cin >> fileName;

			system("cls");
			cout << "\nREAD DATA FROM: " << fileName;
			cout << "\n=====================================================\n";

			if (readFile(fileName, &t1)) {
				cout << "Successfully read the file into BST!\n\n";
			}
			else cout << "\nThe file cannot be read!\n\n";

			system("pause");
			break;

		case 2:

			system("cls");

			cout << "PRINT DEEPEST NODES" << endl;

			if (t1.deepestNodes()) {
				cout << "\n=====================================================\n"
					<< "All the deepest nodes have been successfully printed!\n\n";
			}
			else cout << "Error! The tree is empty!" << endl << endl;
			system("pause");

			break;


		case 3:

			system("cls");
			{
				system("CLS");
				cout << "\nDisplay student\n";
				cout << string(80, '=') << endl;
				cout << "Note: Remember to read student record before continue\n" << endl;
				int source = 0, order = 0;

				do {
					cout << "What order will you want to view the information [1-ascending]/[2-descending] ?: ";
					order = getIntegerInput();
				} while (order != 1 && order != 2);

				do {
					cout << "Where you want to view the information [1-screen]/[2-File] ? : ";
					source = getIntegerInput();
				} while (source != 1 && source != 2);

				if (!t1.display(order, source))
					cout << "Unable to display any information" << endl;

				system("pause");
				break;
			}

		case 4:
		{
			system("cls");
			BST t2;
			int stuID;
			cout << "Clone Subtree\n";
			cout << string(80, '=') << endl;
			cout << "Note: Remember to read student record before continue\n" << endl;


			cout << "Please key in the Student ID that you wish to clone as the root of the subtree: ";
			stuID = getIntegerInput();



			Student searchstu;
			searchstu.id = stuID;
			if (!t2.CloneSubtree(t1, searchstu)) {
				cout << "\nCannot clone subtree.\n";
			}

			system("pause");
			break;

		}

		case 5:
		{
			char confirmation;
			system("cls");
			cout << "Level of Nodes" << endl;
			cout << string(80, '=') << endl;
			cout << "Note: Remember to read student record before continue\n" << endl;

			do {
				cout << "Are you sure you want to display out the level of nodes? (Y-Yes/N-No):";
				cin >> confirmation;
				if (toupper(confirmation) == 'Y') {
					if (!t1.printLevelNodes()) {
						cout << "Error! The tree is empty. Please read the file first." << endl;
					}
					break;
				}
				else if (toupper(confirmation) == 'N') {
					break;
				}
				else {
					cout << "Invalid confirmation. Please enter again!" << endl;
				}

			} while (confirmation != 'Y' && confirmation != 'N');

			system("pause");
			break;

		}
		case 6:
			system("cls");
			cout << "Print Path" << endl;
			cout << string(80, '=') << endl;
			cout << "Note: Remember to read student record before continue\n" << endl;
			cout << "Below are all the external paths for the tree:\n" << endl;
			if (!t1.printPath())
				cout << "Unable to print" << endl;
			
			system("pause");
			break;

		case 7:

			cout << endl << "You are quitting...\n";
			system("Pause");

			next = false;	// Set the flag to exit the while loop, thus exit the program

			break;
		}
	} while (next); // Continue to iterate (display the menu) when case 7 is not selected

	system("cls");
	cout << "\n\n\tThank you for using the program.\n\t\tHave a nice day!\n\n";

	system("pause");
	return 0;
}


/* Function(a) */


// To read student records from a text file and store them into a BST
bool readFile(const char* filename, BST* t1) {

	// Variable declaration
	int stuCount = 0;
	char discard[30];
	Student stu;
	ifstream inFile(filename);

	// Check if the file exist or is empty
	if (!CheckFile(filename))
		return false;

	// Read value from student.txt and store in list1
	while (inFile >> discard >> discard >> discard >> stu.id)
	{
		inFile >> discard >> discard;
		inFile.ignore();
		inFile.getline(stu.name, 256);
		inFile >> discard >> discard;
		inFile.ignore();
		inFile.getline(stu.address, 256);
		inFile >> discard >> discard >> stu.DOB;
		inFile >> discard >> discard >> discard >> stu.phone_no;
		inFile >> discard >> discard >> stu.course;
		inFile >> discard >> discard >> stu.cgpa;

		t1->insert(stu);
		stuCount++;
	}


	cout << "\n" << stuCount << " student record(s) have been successfully read.\n\n";

	return true;
}


/* Menu */


int menu() {

	// Variable declaration
	int choice;

	// Display menu to user

	cout << "\t\t\tMENU\n"
		<< "=====================================================\n"
		<< "\t(1) Read data to BST\n"
		<< "\t(2) Print deepest nodes\n"
		<< "\t(3) Display student\n"
		<< "\t(4) Clone Subtree\n"
		<< "\t(5) Print Level Nodes\n"
		<< "\t(6) Print Path\n"
		<< "\t(7) Exit\n"
		<< "=====================================================\n";


	// Input Validation
	while (true)
	{
		cout << "Enter your choice: ";
		cin >> choice;

		// Input validation for incompatible data type & out of range
		if (cin.fail() || choice < 1 || choice > 7)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please enter between 1 - 7.\n\n";
			continue;
		}
		return choice;
	}
}


/* Check file */

bool CheckFile(string filename) {

	// Varaible declaration
	ifstream inFile(filename);
	string line;

	// Case 1: File does not exist
	if (!inFile) {
		cout << "Error! \"" << filename << "\" does not exist ...\n";
		return false;
	}

	// Move the get pointer to the end of the file (position 0 for empty file)
	inFile.seekg(0, ios::end);

	// The get pointer is at position 0 if the file is empty
	// Case 2: File exists but not empty
	if (inFile.tellg() != 0) {
		return true;
	}

	// Case 3: File exists but empty
	else {
		cout << "Error! \"" << filename << "\" is an empty file ...\n";
		return false;
	}
}


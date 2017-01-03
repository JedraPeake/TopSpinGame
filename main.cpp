#include <iostream>
#include "Topspin.h"
#include "CircularDoublyLinkedList.h"
using namespace std;

int main()
{
	int objectSize = 0, spinSize = 0, shifting = 0;
	cout << "Please enter the object size of your board: ";
	cin >> objectSize;

	cout << "Please enter the spinSize: ";
	cin >> spinSize;

	TopSpin CCDL(objectSize, spinSize);			//constructor call, creates topspin object
	cout << CCDL;

	cout << "How many times would you like to randomly shift: ";
	cin >> shifting;
	CCDL.RandomShifter(shifting);
	cout << CCDL;
	//dowhile loop will only be exited when is solved is true
	do
	{
		int choice = 0;
		cout << "Please choose from the following options enter your choice by entering the corresponding number : " << endl << "1. Shift" << endl << "2. Spin" << endl << "3. Quit" << endl;
		cin >> choice;

		if (choice == 1)
		{
			int leftOrRight;
			cout << "Press 0 to shift left" << endl << "1 to shift right: ";
			cin >> leftOrRight;	//assumes user only enters 0 or 1, no validation check?
			if (leftOrRight == 0)
			{
				CCDL.shiftLeft();
				cout << CCDL;
			}
			else
			{
				CCDL.shiftRight();
				cout << CCDL;
			}
		}

		else if (choice == 2)
		{
			CCDL.spin();
			cout << CCDL;
		}
		else if (choice == 3)
		{
			cout << "Game Exited!" << endl;
			exit(0);
		}
		else {}//incase an invalid input is used, just used instead of a check
	} while (CCDL.isSolved() == false);

	cout << "CONGRATULATIONS!"<<endl;


	return 0;
}
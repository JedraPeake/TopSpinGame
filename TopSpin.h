#pragma once
#include <stdio.h>
#include "CircularDoublyLinkedList.h"
#include <ctime>
#include <iostream>
using namespace std;

class TopSpinADT {
public:
	// shifts the pieces 1 to the left
	virtual void shiftLeft() = 0;
	//shifts the pieces 1 to the right
	virtual void shiftRight() = 0;
	//reverses the pieces in the spin mechanism, IE if the 4 in the mechanism are
	// 1,4,3,6 we will have 6,3,4,1
	virtual void spin() = 0;
	//checks to see if the puzzle is solved that is to say the pieces are in numerical order 1 - 20
	virtual bool isSolved() = 0;
};

class TopSpin : public TopSpinADT
{
private:
	int m_size;
	int m_spin;
public:
	TopSpin(unsigned int boardSize, unsigned int spinSize);

	CircularDoublyLinkedList<int> board;
	void RandomShifter(int shift);
	void shiftLeft();
	void shiftRight();
	void spin();
	bool isSolved();
	int getBoardSize() const;
	int getSpinSize() const;

	~TopSpin();
};

inline std::ostream& operator<< (std::ostream& os, const TopSpin& ts)
{
	//os/ostream=outputstream, basically the same as cout.
	cout << "-------------------------------------------------------------------" << endl;

	cout << "|";
	for (int i = 1; i <= ts.getSpinSize(); i++)
		cout << " " << ts.board.retrieve(i);

	cout << " |";
	for (int i = ts.getSpinSize() + 1; i <= ts.getBoardSize(); i++)
		cout << " " << ts.board.retrieve(i);

	cout << endl;
	cout << "-------------------------------------------------------------------" << endl;
	return os;
}



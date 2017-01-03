#include <iostream>
#include "Topspin.h"

TopSpin::TopSpin(unsigned int boardSize, unsigned int spinSize) //destructor
{
	m_size = boardSize;		//sets size of board
	m_spin = spinSize;		//sets spin size of board

	if (boardSize < 1)  // size must be at least 1, if fails the constructor should use the default value
	{
		boardSize = 20;
		m_size = boardSize;
	}

	if (spinSize > boardSize)	//spinSize must be equal or less than size, if it fails the constructor should use the default value
	{
		spinSize = 4;
		m_spin = spinSize;
	}

	for (int i = 1; i <= boardSize; i++)
	{
		board.addTail(i);
	}

}

void TopSpin::RandomShifter(int shiftAmount)
{
	srand(time(NULL));		//to keep values random, include<ctime>
	int randPiece;
	for (int x = 1; x <= shiftAmount; x++)
	{
		randPiece = rand() % m_size;		//defines a random leftShift amount
		for (int i = 1; i <= randPiece; i++)
		{
			shiftLeft();		//calls shiftLeft
		}
		spin();			//calls Spin
	}
}

void TopSpin::shiftRight()
{
	board.m_head = board.m_head->prev;		//m_head points to the prev in the CDLL
	board.m_tail = board.m_tail->prev;		//m_tail points to the prev in the CDLL
}

void TopSpin::shiftLeft()
{
	board.m_head = board.m_head->next;		//m_head points to the next in the CDLL
	board.m_tail = board.m_tail->next;		//m_tail points to the next in the CDLL
}

void TopSpin::spin()
{
	CircularDoublyLinkedList<int>::Iterator nodeOne(board.getHead());  //points to the first node to be swapped
	CircularDoublyLinkedList<int>::Iterator nodeTwo(board.getHead());	 //points to the last node to be swapped
	for (int i = 1; i < m_spin; i++)
	{
		++nodeOne;
	}
	for (int i = 0; i < m_spin / 2; i++)				//divided by 2, as you do 2 at a time ie 16 25 34 so 3 not 6!
	{
		int temp2 = nodeTwo.getValue();		//gete the value of the Node, and stores it in temp
		int temp = nodeOne.getValue();

		nodeOne.setValue(temp2);				//sets node to the opposite value.
		nodeTwo.setValue(temp);
		//multiple cases, if spinsize is greater then 2
		++nodeTwo;					//moves node forward 
		--nodeOne;					//moves node back
	}
}

bool TopSpin::isSolved()		
{
	int isSolvedCounter = 0;			//counter
	int minimumValue = board.retrieve(1);		//min value in list
	int minIndex = 1;								//min index

	for (int i = 1; i < m_size; i++)		//loop to find the minIndex in the list
	{
		if (board.retrieve(i) < minimumValue)		
		{
			minimumValue = board.retrieve(i);		//reset minvalue and Index when 1 is found in the loop
			minIndex = i;
		}
	}

	for (int s = minIndex; s < m_size; s++)			//starting at index check the loop from index to the m_tail(index to the right of the list)
	{
		if (board.retrieve(s) < board.retrieve(s + 1))
		{
			isSolvedCounter ++;		//counter increment
		}
	}

	for (int f = 1; f < minIndex; f++)			//starting at 1 check the loop to the index(start of list to the index)
	{
		if (board.retrieve(f) < board.retrieve(f + 1))	
		{
			isSolvedCounter ++;		//counter increment
		}
	}

	if (board.retrieve(m_size) < board.retrieve(1))		//check the last element of loop against the first
	{
		isSolvedCounter ++;			//counter increment
	}

	if (isSolvedCounter == m_size - 1)		//m_size-1, as counting from 1 to 20 = 19, if m_size is 20
	{
		return true;
	}
		return false;
}



int TopSpin::getBoardSize() const    //has to be const for operater
{
	return board.size();			//getter
}

int TopSpin::getSpinSize() const	//has to be const for operater
{
	return m_spin;					//getter
}

TopSpin::~TopSpin() {} //topspin destructor
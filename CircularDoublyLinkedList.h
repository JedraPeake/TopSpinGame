#pragma once
#include <iostream>
#include <assert.h>
#include "Topspin.h"

template <class T>
class CircularDoublyLinkedList
{
public:
	class Node
	{
	public:
		Node(T val, Node * nx = nullptr) : value(val), next(nx) { }
		T  value;
		Node * next;
		Node *prev;		/*extra node required to point backwards*/
	};

public:
	Node * m_head;				//Node is used for declarations within the scope of the class CDLL
	Node * m_tail;				//m_tail/m_haed refrence point to the front and back of the CCDL
	unsigned int m_size;		//number of nodes

public:
	CircularDoublyLinkedList(); // construct an empty linked list
	CircularDoublyLinkedList(const CircularDoublyLinkedList &other);//copy constructor
	~CircularDoublyLinkedList();     // destroy a linked list
	unsigned int size() const;  // return number of items in the list
	bool isEmpty() const; // true if list is empty, false otherwise
	void addHead(T item);  // adds item to front of list	//ads node at front of the list!
	inline Node* getHead() const { return m_head; }
	void addTail(T item); // add item to end of list
	void add(unsigned int n, T item); // Add a new node containing an item in position n on the list
									  // PRECONDITION: n must be a valid list position (1<=n<=(size+1))
	T retrieve(unsigned int n) const; // Return the item value from the node in position n; 
									  // PRECONDITION: n must be a valid list position (1<=n<=size)
	T retrieveTail() const; // return data T in last node; 
							// PRECONDITION: list must not be empty already
	T retrieveHead() const; // returns the data T in front node; 
							// PRECONDITION: list must not be empty already
	T replace(unsigned int n, T item); // Replace the data stored in position n of the list with
									   // item, and return the replaced item; 
									   // PRECONDITION: n must be a valid list position (1<=n<=size)  
	T removeHead();  // remove front node, and return the data T found in it;
					 // PRECONDITION: list must not be empty already

	T removeTail(); // remove last node, and return the data T found in it;
					// PRECONDITION: list must not be empty already
	T remove(unsigned int n); // Remove the node at position n from the list, and return the
							  // item it contained; PRECONDITION: n must be a valid list position (1<=n<=size)
	
	void print()			//for testing CDLL seperately only
	{
		auto print = getHead();
		for (unsigned i = 0; i < m_size; i++)
		{
			cout << print->value;
			print = print->next;
		}
	}
		 
public:
	class Iterator
	{// iterators are used for efficient traversal of linked lists
	private:
		Node* m_ptr;    // an iterator hides a pointer to node
	public:
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator++ () { m_ptr = m_ptr->next; } // for forward traversing, e,g, Iterator i=begin(); ... ++i;
		void operator--() { m_ptr = m_ptr->prev; }	// with a DLL you can traverse backwords due to the pre pointers
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		T operator *() { return m_ptr->value; }
		T getValue() { return m_ptr->value; }
		void setValue(T val) { m_ptr->value = val; }
	};

	// linked list objects create forward-traversal iterators using the two functions below
	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(nullptr); }
};
// An implementation of templated class "CDLL"

template <class T>
unsigned int CircularDoublyLinkedList<T> ::size() const
{
	return m_size;
}

template <class T>
bool CircularDoublyLinkedList<T> ::isEmpty() const
{
	return (m_size == 0);
} 

template <class T>
CircularDoublyLinkedList<T> ::CircularDoublyLinkedList()
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{}

template <class T>
void CircularDoublyLinkedList<T> ::addHead(T item)
{
	auto headNode = new Node(item);	//creates new node
	if (isEmpty())	//empty check
	{
		m_head = headNode; //head points to the new node. 
		m_tail = m_head;   //tail points to the head since there is only 1 node in the list. 
	}

	else
	{
		headNode->next = m_head;	//new head points to old head
		m_head->prev = headNode;	//old head points to new head
		
		headNode->prev = m_tail;	///circular part, head points to tail
		m_tail->next = headNode;	 //tail points to head
		m_head = headNode;

	}
	m_size++;//Increment size 
}

//for addtail swap all m_head to m_tail, and redefine node name
template <class T>
void CircularDoublyLinkedList<T> ::addTail(T item)
{
	if (isEmpty()) //empty check
	{
		addHead(item);  //calls adhead if empty
	}
	else
	{
		auto tailNode = new Node(item);//create a new node
		
		tailNode->prev = m_tail;	  //new tail points to old tail
		m_tail->next = tailNode;	//old tail points to new tail
		
		tailNode->next = m_head;	//circular part, tail points to head
		m_head->prev = tailNode;    //head point to tail
		m_tail = tailNode;

		m_size++;//Increment size  
	}
}

template <class T> //Copy Constructor
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList<T> &other) {

	if (other.m_size == 0) {
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
	else {
		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr);
		if (other.m_tail == nullptr) {
			m_tail = m_head;
		}
		else {
			Node * copyFrom = other.m_head->next;
			Node *nextNode = m_head;

			while (copyFrom != nullptr) {
				nextNode->next = new Node(copyFrom->value);
				copyFrom = copyFrom->next;
				nextNode = nextNode->next;
			}
			m_tail = nextNode;
		}

	}
}

template <class T>
void CircularDoublyLinkedList<T> ::add(unsigned int n, T item)
{
	// PRECONDITION: n should be a valid position in the list
	assert(((n >= 1) && (n <= size() + 1) && "LinkedList index is out of bounds (in add)"));		//validation

	if (n == 1)				//add node to first place
	{
		addHead(item);
	}

	else if (n == (size() + 1))		//add node to the end
	{
		addTail(item);
	}
	else
	{
		Node * here = m_head;		//sets m_head as here
		for (unsigned int k = 1; k < n - 1; k++)		//shifts here the required amount so that it points node before the add spot not the m_head
		{
			here = here->next;							//next just points to the next node in the list
		}

		//here->next = new Node(item, here->next);		//creates newnode, also creates a pointer from the previos to the next node
		auto newNode = new Node(item);
		here->next = newNode;	//old node points to new node
		newNode->prev = here;	//new node points to preveious node

		newNode->next = Node*nextNode;
		nextNode->prev = newNode;

		m_size++;
	}
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieve(unsigned int n) const
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in retrieve)"));		//empty check
	
	if (n == 1) return retrieveHead();							//retrieve m_head
	if (n == size()) return retrieveTail();						//retrieve m_tail
	
	Node * here = m_head;										//node pointer points to the first node 
	for (unsigned int k = 1; k < n; k++)
	{
		here = here->next;					//traverse the list for the needed node
	}
	return here->value;						//return the node
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieveTail() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveTail)"));
	return m_tail->value;
}

template <class T>
T CircularDoublyLinkedList<T>::retrieveHead() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveHead)"));
	return m_head->value;
}

template <class T>
T CircularDoublyLinkedList<T> ::replace(unsigned int n, T item)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in replace)"));		//empty check

	T returnValue;				//
	Node * here = m_head;

	for (unsigned int k = 1; k < n; k++)
	{
		here = here->next;				//traversing the list
	}
	returnValue = here->value;
	here->value = item;				//sets new value
	return returnValue;
}

template <class T>
T CircularDoublyLinkedList<T> ::removeHead()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeHead)"));		//empty check

	Node * tempNode = m_head;					//points at m_head

	T returnVal = m_head->value;				//returns value at m_head
	m_head = m_head->next;						//sets m_head to next node in the list

	tempNode->next = nullptr			//sets link between old front node and new front node to 0
		m_head->prev = nullptr			//

		m_head->next = m_tail;						//makes code circular prev points to m_tail
	m_tail->prev = m_head;						//m_tail next points to m_head

	m_size--;			//size decrement

	delete tempNode;
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T> ::removeTail()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeTail)"));		//empty check

	T returnVal = m_tail->value;					//stores the value. 

	Node * oldTail = m_tail;						//oldnode points at m_tail			 

	m_tail = m_tail->prev;							//reset m_tail
													//make it DLL
	oldTail->prev = nullptr;						//deletes links between oldtail and new tail
	m_tail->next = nullptr;							//

	m_tail->prev = m_head;							//makes circular new m_tail points at m_head
	m_head->next = m_tail;							//m_head points at m_tail



	delete oldTail;					//deletes old node
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T> ::remove(unsigned int n)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in remove)"));		//empty check

	if (n == 1) return removeHead();			//calls removehead if the first node
	if (n == size()) return removeTail();		//calls remove tail if last node

	Node * here = m_head;						//sets m_head node as here

	for (unsigned int k = 1; k < n - 1; k++)
	{
		here = here->next;						//traversee the list to find the required node before the one to remove
	}

	Node * kill = here->next;					//sets next node as kill, to be deleted
	T returnVal = kill->value;					//get the kill value

	here->next = kill->next;					//changes old link to point at node after kill

	Node afrterkill = kill->next;				//points at node after kill 
	afrterkill->prev = here						//afterkill prev points at node before kill node

		delete kill;								//delete node
	m_size--;									//size decrement
	return returnVal;
}

template <class T>
CircularDoublyLinkedList<T> :: ~CircularDoublyLinkedList()
{
	Node * here = m_head, *nextNode;	//here points at m_head
										//nextNode used to traverse the list
	while (m_size != 0)
	{
		nextNode = here->next;			// points to thhe nextnode in the list
		delete here;					//deletes preveious node
		here = nextNode;				//here = nextnode
		m_size--;						//size decrement
										//cout << "destructor"  << endl;	//for testing purposes
	}
}
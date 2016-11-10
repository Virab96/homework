#pragma once

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <queue>
using namespace std;

#include "Node.h"

template <typename T>
class List //linked list of Node objects
{
public:
	List();
	List(T);
	~List();

	void insert(T);					// general instert function
	void remove(T key);				// remove element
	bool find(T);					//searches for a value
	int get_height();				//finds height of the List


	void preOrderTraverse();
	void inOrderTraverse();
	void postOrderTraverse();


private:
	T data;
	Node<T> *startPtr;		//stores the pointer of first object in the linked list

	void preOrderTraverseUtility(Node<T>*);
	void inOrderTraverseUtility(Node<T>*);
	void postOrderTraverseUtility(Node<T>*);
};

/* Constructor, Destructor */

template <typename T>
List<T>::List() //creates list with start and end as NULL
{
	data = NULL;
	startPtr = nullptr;
}

template <typename T>
List<T>::List(T dataIn) //creates list with start and end as NULL
{
	data = dataIn;
	startPtr = nullptr;
}

template <typename T>
List<T>::~List()
{
	queue<Node<T>*> Q;
	Q.push(startPtr);

	while (!Q.empty()) // List is not empty
	{
		Node<T> *currentPtr = Q.front();
		Q.pop();

		if (currentPtr != nullptr)
		{
			Q.push(currentPtr->leftPtr);
			Q.push(currentPtr->rightPtr);
		}
		delete currentPtr;
	}
}

template <typename T>
void List<T>::insert(T dataIn)
{
	if (startPtr == nullptr)
	{
		startPtr = new Node<T>(dataIn);
		return;
	}

	Node<T>* currentPtr = startPtr;
	Node<T>* prevPtr = nullptr;
	int direction = 0; // direction == -1 --> arrived from left, direction == 1 --> arrived from right

	while (true) //while correct place not found
	{
		if (currentPtr == nullptr)
		{
			currentPtr = new Node<T>(dataIn);
			if (prevPtr != nullptr)
			{
				if (direction == -1)
					prevPtr->leftPtr = currentPtr;
				else
					prevPtr->rightPtr = currentPtr;
			}
			break;
		}
		else
		{
			if (dataIn < currentPtr->data)
			{
				prevPtr = currentPtr;
				direction = -1;
				currentPtr = currentPtr->leftPtr;
			}
			else
			{
				prevPtr = currentPtr;
				direction = 1;
				currentPtr = currentPtr->rightPtr;
			}
		}
	}
}

template <typename T>
bool List<T>::find(T key)
{
	Node<T>* currentPtr = startPtr;

	while (true)
	{
		if (currentPtr == nullptr)
			return false;
		if (currentPtr->data == key)
			return true;
		if (currentPtr->data > key)
		{
			currentPtr = currentPtr->leftPtr;
			continue;
		}
		else
		{
			currentPtr = currentPtr->rightPtr;
			continue;
		}
	}
	return false;
}

template <typename T>
void List<T>::remove(T key)
{
	Node<T> *currentPtr = startPtr;
	Node<T> *prevPtr = nullptr;
	int direction = 0; // direction == -1 --> arrived from left, direction == 1 --> arrived from right


	while (true) //place not found
	{
		if (currentPtr == nullptr) // not found
			break;

		if (currentPtr->data == key)
		{
			if (currentPtr->leftPtr == nullptr && currentPtr->rightPtr == nullptr)
			{
				delete currentPtr;
				currentPtr = nullptr;
			}
			if (currentPtr->rightPtr)
			{
				//leftmost in right subtree
				Node<T> *leafPtr = currentPtr->rightPtr;
				Node<T> *leafParentPtr = currentPtr;
				while (leafPtr->leftPtr)
				{
					leafParentPtr = leafPtr;
					leafPtr = leafPtr->leftPtr;
				}

				leafParentPtr->leftPtr = nullptr;
				currentPtr = leafPtr;
				delete leafPtr;
				break;
			}
			else
			{
				//rightmost in left subtree
				Node<T> *leafPtr = currentPtr->leftPtr;
				Node<T> *leafParentPtr = currentPtr;
				while (leafPtr->rightPtr)
				{
					leafParentPtr = leafPtr;
					leafPtr = leafPtr->rightPtr;
				}

				leafParentPtr->rightPtr = nullptr;
				currentPtr = leafPtr;
				delete leafPtr;
				break;
			}
		}
		else
		{
			if (currentPtr->data > key)
				currentPtr = currentPtr->leftPtr;
			else
				currentPtr = currentPtr->rightPtr;
		}
	}

	return;
}


template <typename T>
int List<T>::get_height()
{
	int height = 0;
	queue<pair<Node<T>*, int> > Q;
	Q.push(make_pair(startPtr, 0));

	while (!Q.empty()) // List is not empty
	{
		Node<T> *currentPtr = Q.front().first;
		int cur_height = Q.front().second;
		Q.pop();

		if (cur_height > height)
			height = cur_height;

		if (currentPtr != nullptr)
		{
			Q.push(make_pair(currentPtr->leftPtr, cur_height + 1));
			Q.push(make_pair(currentPtr->rightPtr, cur_height + 1));
		}
	}
	return height;
}

/* Traversals */

template <typename T>
void List<T>::preOrderTraverse()
{
	preOrderPrintUtility(rootPtr);
}

template <typename T>
void List<T>::preOrderTraverseUtility(Node<T>* temp)
{
	if (temp != nullptr)
	{
		cout << temp->data << ' '; //process node
		preOrderTraverseUtility(temp->leftPtr); //to left subList
		preOrderTraverseUtility(temp->rightPtr); //to right subList
	}
}


template <typename T>
void List<T>::inOrderTraverse()
{
	inOrderTraverseUtility(rootPtr);
}

template <typename T>
void List<T>::inOrderTraverseUtility(Node<T>* temp)
{
	if (temp != nullptr)
	{
		inOrderPrintUtility(temp->leftPtr); //to left subList
		cout << temp->data << ' '; //process node
		inOrderPrintUtility(temp->rightPtr); //to right subList
	}
}


template <typename T>
void List<T>::postOrderTraverse()
{
	postOrderTraverseUtility(rootPtr);
}

template <typename T>
void List<T>::postOrderTraverseUtility(Node<T>* temp)
{
	if (temp != nullptr)
	{
		postOrderTraverseUtility(temp->leftPtr); //to left subList
		postOrderTraverseUtility(temp->rightPtr); //to right subList
		cout << temp->data << ' '; //process node
	}
}

#endif // LIST_H
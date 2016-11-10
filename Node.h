#pragma once

#ifndef Node_H
#define Node_H

template <typename T>
class List;

template <typename T>
class Node //Node
{
	friend class List<T>;

public:
	Node(T);
	T getData();

private:
	T data;				// actual data in the current Node
	Node* leftPtr;		//pointer to the next Node in list
	Node* rightPtr;		//pointer to the next Node in list
};

template <typename T>
Node<T>::Node(T dataIn)
{
	data = dataIn;		//data in Node
	leftPtr = nullptr;  //initialize pointer to next Node
	rightPtr = nullptr; //initialize pointer to next Node
}

template <typename T>
T Node<T>::getData() //returns the data stored in Node
{
	return data;
}

#endif // Node_H

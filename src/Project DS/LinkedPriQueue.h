#ifndef LINKED_Pri_QUEUE_
#define LINKED_Pri_QUEUE_

#include "PriQueueADT.h"
#include "NodePri.h"

template < typename T>
class LinkedPriQueue : public PriQueueADT<T>
{
	NodePri<T>* backPtr;
	NodePri<T>* frontPtr;
	int Count;

public:
	LinkedPriQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueueAsc(const T& newEntry, int priority);
	bool enqueueDesc(const T& newEntry, int priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int size();
	~LinkedPriQueue();

	LinkedPriQueue(const LinkedPriQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/* Queue() */

template <typename T>
LinkedPriQueue<T>::LinkedPriQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	Count = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////

/* is Empty */
template <typename T>
bool LinkedPriQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/* enqueue by Asc */

template <typename T>
bool LinkedPriQueue<T>::enqueueAsc(const T& newEntry, int priority)
{
	NodePri<T>* tmp, * q;
	tmp = new NodePri<T>;
	tmp->setItem(newEntry);
	tmp->setPriority(priority);
	if (frontPtr == nullptr || priority < frontPtr->getPriority())
	{
		tmp->setNext(frontPtr);
		frontPtr = tmp;
	}
	else
	{
		q = frontPtr;
		while (q->getNext() != nullptr && q->getNext()->getPriority() <= priority)
			q = q->getNext();
		tmp->setNext(q->getNext());
		q->setNext(tmp);
	}
	Count++;
	return true;
} 

/* enqueue by Desc*/

template <typename T>
bool LinkedPriQueue<T>::enqueueDesc(const T& newEntry, int priority)
{
	NodePri<T>* tmp, * q;
	tmp = new NodePri<T>;
	tmp->setItem(newEntry);
	tmp->setPriority(priority);
	if (frontPtr == nullptr || priority > frontPtr->getPriority())
	{
		tmp->setNext(frontPtr);
		frontPtr = tmp;
	}
	else
	{
		q = frontPtr;
		while (q->getNext() != nullptr && q->getNext()->getPriority() >= priority)
			q = q->getNext();
		tmp->setNext(q->getNext());
		q->setNext(tmp);
	}
	Count++;
	return true;
} 

/////////////////////////////////////////////////////////////////////////////////////////

/* enqueue : Adds newEntry at the back of this queue. */

template <typename T>
bool LinkedPriQueue<T>::enqueue(const T& newEntry)
{
	NodePri<T>* newNodePtr = new NodePri<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now

	Count++;
	return true;
} 


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/* dequeue */
template <typename T>
bool LinkedPriQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodePri<T>* NodePriToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (NodePriToDeletePtr == backPtr)	
		backPtr = nullptr;

	delete NodePriToDeletePtr;

	Count--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/* peek */
template <typename T>
bool LinkedPriQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

///////////////////////////////////////////////////////////////////////////////////
/*
Function: size
return size
*/
template <typename T>
int LinkedPriQueue<T>::size()
{
	LinkedPriQueue<T> X;
	int c = 0;
	T ITEM;
	if (isEmpty())
		return 0;

	while (dequeue(ITEM))
	{
		X.enqueue(ITEM);
		c++;
	}
	while (X.dequeue(ITEM))
		enqueue(ITEM);

	return c;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedPriQueue<T>::~LinkedPriQueue()
{
	T temp;

	//Free (Dequeue) all NodePris in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedPriQueue<T>::LinkedPriQueue(const LinkedPriQueue<T>& LQ)
{
	NodePri<T>* NodePriPtr = LQ.frontPtr;
	if (!NodePriPtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first NodePri
	NodePri<T>* ptr = new NodePri<T>(NodePriPtr->getItem());
	frontPtr = backPtr = ptr;
	NodePriPtr = NodePriPtr->getNext();

	//insert remaining NodePris
	while (NodePriPtr)
	{
		NodePri<T>* ptr = new NodePri<T>(NodePriPtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePriPtr = NodePriPtr->getNext();
	}
}

#endif
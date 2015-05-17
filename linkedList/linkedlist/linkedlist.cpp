// linkedlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "linkedList.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

//constructor
template <typename type>
linkedList<type>::linkedList(){
	count = 0;
}


template <typename type>
bool linkedList<type>::addHead(type &e){

	return insert(0, e);
	//let's let insert handle all the insert logic
	/*
	if (!root){
		Node node;
		node.data = e;
		root = &node;
		count++;
		return true;
	}

	Node node;
	node.data = e;
	node.next = root;
	root->prev = &node;
	root = &node;
	count++;
	return true;
	*/
}

template <typename type> 
bool linkedList<type>::addTail(type &e){

	return insert(count - 1, e);
	//Same  as addHead(), let insert() handle insert
	/*
	if (!root){
		addHead(e);
		count++;
		return true;
	}
	else if (!leaf)
	{
		Node node;
		node.data = e;
		node.prev = root;
		leaf = &node;
		root->next = leaf;
		count++;
		return true;
	}
	Node node;
	node.data = e;
	node.prev = leaf;
	leaf->next = &node;
	leaf = &node;
	count++;
	return true;
	*/
}

//same as addTail()
template <typename type>
bool linkedList<type> ::add(type &e)
{
	return insert(count - 1, e);
}

template<typename type>
type & linkedList<type>::getHead()
{
	if (!(size() > 0))
	{
		return NULL;
	}
	if (!root)
	{
		//look if there is a tail
		if (!tail)
		{
			//if nothing is found, return NULL
			return NULL;
		}
		return tail->&data;
	}
	return root->&data;
}

template<typename type>
type & linkedList<type>::getTail()
{
	if (!(size() > 0))
	{
		return NULL;
	}
	if (!tail)
	{
		//look for head
		if (!head){
			return NULL;
		}
		return head->&data;
	}
	return tail->&data;
}

template<typename type>
int linkedList<type>::size()
{
	return count;
}

template<typename type>
type & linkedList<type>::removeAt(int index)
{

	//out of bounds
	if (index >= count || index<0)
	{
		return NULL;
	}

	//If I want to delete the head
	if (!index)
	{
		if (!root)
			return NULL;

		iterator = root;

		//if root has no next, then set it to NULL
		if (!iterator->next)
		{
			root = NULL;
		}
		else
		{
			root = iterator->next;
			root->prev = NULL; // the previous root no longer exists, set the new root prev to NULL		
		}

		//deconstruct the node
		type *typePtr = iterator->data;
		delete iterator->data;
		delete iterator->next;
		delete iterator->prev;
		count--;
		return typePtr;
	}

	//If i want to delete the tail
	if (!(size() - 1 - index))
	{
		if (!tail)
			return NULL;

		iterator = leaf;

		//if tail has no previous, then set it to NULL - this should never happen!
		if (!iterator->prev)
		{
			leaf = NULL;
		}
		else 
		{
			leaf = iterator->prev;
			leaf.next = NULL;
		}

		//deconstruct the node
		type *typePtr = iterator->data;
		delete iterator->data;
		delete iterator->next;
		delete iterator->prev;
		count--;
		return typePtr;
	}

	int offset;
	bool closerToHead = (size() / 2 > index);
	//find out if it's closer to the tail or head
	if (closerToHead) //closer to the head
	{
		iterator = getHead();
		offset = index;
	}
	else
	{
		iterator = getTail();
		offset = size() - 1 - index;
	}

	for (int i = 0; i < offset; ++i)
	{
		iterator = (closerToHead) ? iterator->next : iterator->prev;
	}

	//Update prev and next pointers for neigboring nodes of the removed node
	iterator->next->prev = iterator->prev;
	iterator->prev->next = iterator->next;

	//deconstruct the node
	type *typePtr = iterator->data;
	delete iterator->data;
	delete iterator->next;
	delete iterator->prev;

	count--;
	return typePtr;
}


template <typename type>
bool linkedList<type>::insert(int index, type &e)
{
	Node node;
	int offset;

	//find out if closer to the head or tail
	bool closerToHead = (index < count / 2);
	if (closerToHead)
	{
		if (!root){
			node.data = e;
			root = &node;
			count++;
			return true;
		}
		iterator = root;
		offset = index;
	}
	else
	{
		if (!tail)
		{
			if (!root)
			{
				node.data = e;
				root = &node;
				count++;
				return true;
			}
			node.data = e;
			leaf = &node;
			count++;
			return true;
		}
		iterator = leaf;
		offset = count - 1 - index;
	}

	for (int i = 0; i < offset; ++i)
	{
		iterator = (closerToHead) ? iterator->next : iterator->prev;
	}

	//Inserts a new node

	node.data = e;
	node.prev = iterator->prev;
	node.next = iterator;
	iterator->prev->next = &node;
	iterator->prev = &node;

	return true;
}


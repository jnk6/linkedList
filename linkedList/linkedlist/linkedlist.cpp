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
bool linkedList<type>::addHead(type e){
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
}

template <typename type> 
bool linkedList<type>::addTail(type e){
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
}

template<typename type>
type * linkedList<type>::getHead()
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
type * linkedList<type>::getTail()
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
type * linkedList<type>::removeAt(int index)
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
		root = iterator->next;
		root->prev = NULL;

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
		leaf = iterator->prev;
		leaf.next = NULL;

		//deconstruct the node
		type *typePtr = iterator->data;
		delete iterator->data;
		delete iterator->next;
		delete iterator->prev;
		count--;
		return typePtr;
	}

	int offset;
	//find out if it's closer to the tail or head
	if (count / 2 > index) //closer to the head
	{
		iterator = getHead();
		offset = index;
	}
	else
	{
		iterator = getTail();
		offset = count - index;
	}

	for (int i = 0; i < offset; ++i)
	{
		iterator = (count / 2 > index) ? iterator->next : iterator->prev;
	}

	//deconstruct the node
	type *typePtr = iterator->data;
	delete iterator->data;
	delete iterator->next;
	delete iterator->prev;

	count--;
	return typePtr;
}
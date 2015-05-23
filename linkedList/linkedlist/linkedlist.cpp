// linkedlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "linkedList.h"
#include <stdexcept>

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> lList;

	for (int i = 0; i < 10; ++i)
	{
		int & x = i;
		lList.add(x);
	}
	
	lList.getAt(2);
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
		throw std::runtime_error("empty list");
	}
	if (!root)
	{
		//look if there is a tail
		if (!tail)
		{
			//if nothing is found, return NULL
			throw std::runtime_error("empty list");
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
		throw std::runtime_error("empty list");
	}
	if (!tail)
	{
		//look for head
		if (!head){
			throw std::runtime_error("element not found");
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
		throw "out of bounds!";
	}

	//If I want to delete the head
	if (!index)
	{
		if (!root)
			throw "root does not exist!";

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
		deleteNode(iterator, 1);
		return typePtr;
	}

	//If i want to delete the tail
	if (!(size() - 1 - index))
	{
		if (!leaf)
			throw "tail does not exist!";

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
		deleteNode(iterator, 1);
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

	//deconstruct the node
	type *typePtr = iterator->data;
	deleteNode(iterator, 1);

	return typePtr;
}


template <typename type>
bool linkedList<type>::insert(int index, type &e)
{
	//Node node;
	int offset;

	//find out if closer to the head or tail
	bool closerToHead = (index < count / 2);
	if (closerToHead)
	{
		if (!root){
			root = createNode(e, NULL, NULL, 1);			
			return true;
		}
		iterator = root;
		offset = index;
	}
	else
	{
		if (!leaf)
		{
			if (!root)
			{
				root = createNode(e, NULL, NULL, 1);
				return true;
			}
			leaf = createNode(e, NULL, NULL, 1);
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

	createNode(e, iterator->prev, iterator, 1)
	return true;
}

template <typename type> 
type & linkedList<type>::getAt(int index)
{

	bool closerToHead = true;
	int offset = index;
	iterator = root;

	//out of bounds
	if (index <0 || index >(size() - 1))
	{
		throw "out of bounds!";
	}
	
	//closer to tail
	if (!(index < ((size() - 1) / 2)))
	{
		closerToHead = false;
		offset = size() - 1 - index;
		iterator = leaf;
	}


	for (int i = 0; i < offset; ++i)
	{
		iterator = (closerToHead) ? iterator->next : iterator->prev;
	}

	return *(iterator->data);
}

template <typename type>
Node * linkedList<type>::createNode(type &e, Node *p, Node *n, int increment)
{
	Node node;
	node.data = &e;
	node.prev = p;
	node.next = n;
	count += increment;
	updateNodeLinks(node, "create");
	
	return &node;
}

template <typename type>
void linkedList<type>::deleteNode(Node *node, int decrement)
{
	delete node;
	updateNodeLinks(node, "delete");
	count -= decrement;
}

//takes care of linking when inserting or removing nodes
template<typename type>
void linkedList<type>::updateNodeLinks(Node *node, const char *str)
{
	if (!strcmp(str, "create"))
	{
		if (node->prev)
		{
			node->prev->next = node;
		}
		
		if (node->next)
		{
			node->next->prev = node;
		}
	}

	if (!strcmp(str, "delete"))
	{
		if (node->prev && node->next)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}

	}
}
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#pragma once

#include "Common.h"
#include "Node.h"

class LinkedList
{
public:
	int m_nCountElements;
	Node* m_pHead, * m_pTail;
	LinkedList(void);
	void insert(void* new_data); // them vao cuoi list
	void* pop(); // lay phan tu dau
	void removeNode(Node *node); // xoa mot node;
	void clearList(); // delete all node in list
};

#endif
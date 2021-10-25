#ifndef NODE_H
#define NODE_H
#pragma once
#include "Common.h"

class Node
{
public:
	void* data;
	Node *next, *prev;
	Node();
};

#endif
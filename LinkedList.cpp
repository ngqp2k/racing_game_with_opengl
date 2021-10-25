#include "LinkedList.h"

LinkedList::LinkedList(void)
{
	m_nCountElements = 0;
	m_pHead = m_pTail = NULL;
}

void LinkedList::clearList() {
	while (m_pHead != NULL) {
		void* p = pop();
	}
}

void LinkedList::insert(void* new_data) {
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = NULL;
	if (m_nCountElements == 0) {
		new_node->prev = NULL;
		m_pHead = m_pTail = new_node;
	}
	else {
		new_node->prev = m_pTail;
		m_pTail->next = new_node;
		m_pTail = new_node;
	}
	m_nCountElements++;
}

void* LinkedList::pop() {
	if (m_nCountElements == 0) {
			printf("Danh sach rong!!!\n");
			return NULL;
	}
	else if (m_nCountElements == 1) {
		void* res = (void*)m_pHead->data;
		delete m_pHead;
		m_pHead = m_pTail = NULL;
		m_nCountElements = 0;
		return res;
	}
	void* res = (void*)m_pHead->data;
	m_pHead = m_pHead->next;
	delete m_pHead->prev;
	m_pHead->prev = NULL;
	m_nCountElements--;
	return res;
}

void LinkedList::removeNode(Node* node) {
	if (m_nCountElements == 0) {
			std::cout << "List is empty!\n";
			return;
		}
	if (m_nCountElements == 1)
		void* p = pop();
	else if (node == m_pHead)
		void* p = pop();
	else if (node == m_pTail) {
		m_pTail = m_pTail->prev;
		delete m_pTail->next;
		m_pTail->next = NULL;
		m_nCountElements--;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		m_nCountElements--;
	}
}
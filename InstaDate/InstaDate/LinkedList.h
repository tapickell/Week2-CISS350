#include "node.h"

#pragma once
class LinkedList
{
public:
	LinkedList(void);
	~LinkedList(void);

	int add(Client);
    void removeAt(int);
    int count();
    Client getAt(int);
    void clear();
    Client operator [] (int);
	int operator += (Client);

private:
    int _count;
    void inRange(int);
	void goToNode(int);
  
    node *head;
    node *tempPtr;
    node *visitPtr;
};


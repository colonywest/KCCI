/* LinkedList.h - Defines the LinkedList and Node classes for use in
 *                the library
 *
 * Copyright (C) 2003 by Kenneth Ballard. All rights reserved.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node
{
public:
    virtual ~Node() { }

    Node * nextNode;
    Node * prevNode;
};

class LinkedList
{
public:
    LinkedList();
    LinkedList(Node *);

    ~LinkedList();

    void removeElement(int);
    void addElement(Node *);
    short addElement(Node *, int );
    Node * elementAt(int );

    int size();
    void reset();

    const char * getVersion();

private:
    Node * firstnode;
    Node * lastnode;
    int numelements;
};

#endif

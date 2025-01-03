/* LinkedList.cpp - Implementation of the LinkedList class
 * Copyright (C) 2001 by Kenneth Ballard. All rights reserved.
 */

#include "LinkedList.h"

/* Constructor for the linked list that sets it to a 0 element list */

LinkedList::LinkedList()
{
    firstnode = lastnode = 0;
    lastnode = firstnode;
    numelements = 0;
}

/* Allows the program to provide the first element of the list */

LinkedList::LinkedList(Node * p)
{
    firstnode = lastnode = p;
    firstnode->nextNode = 0;
    firstnode->prevNode = 0;
    numelements = 1;
}

/* Destructor - Must delete all nodes before killing the instance */

LinkedList::~LinkedList()
{
    reset();
}

/* Adds an element to the tail end of the linked list */

void LinkedList::addElement(Node * p)
{
    /* If a NULL pointer is attempting to be added, return */

    if(p == 0) return;

    /* Adding data to a linked list is not that hard.  First, we must
     * create the new node.  Null out the two node pointers inside it.
     */

    Node * u = p;
    u->prevNode = 0;
    u->nextNode = 0;

    /* Since this one goes at the end, we just set the last node's
     * nextNode pointer as the current node.  This node's prevNode
     * pointer also is set as the current last node, then the last
     * node is set as this node.
     */

    if(numelements == 0)
    {
        firstnode = u;
        firstnode->nextNode = 0;
        firstnode->prevNode = 0;
        lastnode = firstnode;
    }
    else
    {
        lastnode->nextNode = u;
        u->prevNode = lastnode;
        lastnode = u;
    }
    numelements ++;
}

/* Adds an element at the specified position.  If the position is not valid,
 * it returns a -1 value and does not add the node to the list.
 */

short LinkedList::addElement(Node * p, int pos)
{
    /* First, check to see if the position requested is larger than
     * the size of the list or less than 0.  If the pointer is NULL,
     * return.
     */

    if(pos < 0 || pos >= numelements) return -1;
    if(p == 0) return -1;

    /* Now, since the position is valid, this round we create three
     * Node pointers.  One holds the new node, the next the prevNode, and
     * the last the nextNode.  A fourth pointer will be created as well
     * for traversing the list.
     */

    Node * u, * i;

    u = p;

    /* Now, traverse the linked list for the new position */

    i = firstnode;              /* Position 0, count starting with 1 */
    for(int x = 0; x < pos; x++)
        i = i->nextNode;

    /* Now, the current node's attributes are copied to the pointers */

    u->prevNode = i->prevNode;
    u->nextNode = i;
    i->prevNode = u;
    u->prevNode->nextNode = u;

    numelements ++;
    return 0;
}

/* This retrieves an element and returns a pointer to the element
 * at the specified position.  If the position is not valid, it will
 * return a NULL pointer.
 */

Node * LinkedList::elementAt(int pos)
{
    /* Looking for an invalid element, return a NULL pointer */

    if(pos >= numelements || pos < 0) return 0;

    /* Looking for the first or last node, return it instead of
     * traversing looking for it.
     */

    if(pos == 0) return firstnode;
    if(pos == numelements - 1) return lastnode;

    /* Traverse the list looking for the node */

    Node * u = firstnode;
    for(int x = 0; x < pos; x++)
        u = u->nextNode;

    /* Return the node object */

    return u;
}

/* Removes an element from the list, deleting the contents of the node in
 * the process.  If the position specified is invalid, no node is removed.
 */

void LinkedList::removeElement(int pos)
{
    Node * u, * v, * w;
    int x;

    /* First check to see if the position requested is valid.  If not,
     * just simply return.
     */

    if(pos < 0 || pos >= numelements) return;

    /* With removing an element, we must first casually remove it from
     * the list.  We start by finding it.
     */

    u = firstnode;              /* Set the pointer at the first node */

    for(x = 0; x < pos; x++)    /* Find the node to remove */
        u = u->nextNode;

    v = u->prevNode;            /* Copy the pointers to temporary */
    w = u->nextNode;            /* variables */

    if(v != 0)
        v->nextNode = w;        /* Set the previous node's nextNode */
    if(w != 0)
        w->prevNode = v;        /* Set the next node's prevNode */

    delete u;                   /* Free the memory used by the item */
    numelements --;             /* Decrement the size counter */

    if(v == 0)
        firstnode = w;          /* First node deleted */
    if(w == 0)
        lastnode = v;           /* Last node deleted */
}

/* Returns the number of elements in the linked list */

int LinkedList::size()
{
    return numelements;
}

/* Kills all of the nodes in the list, resetting it back to a 0-element
 * list.
 */

void LinkedList::reset()
{
    /* To delete a linked list, we must first kill all of the pointers
     * inside it using delete.
     */

   if(numelements == 0) return;

   Node * p = lastnode;
   Node * q = p->prevNode;

   while(p != 0)
   {
       delete p;
       p = q;
       if(p != 0) q = p->prevNode;
   }

   numelements = 0;
}

const char * LinkedList::getVersion()
{
    return "LinkedList C++ Library - Version 1.1\n";
}

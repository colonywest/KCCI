#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

class StringNode : public Node
{
public:
    StringNode(const char *);
    ~StringNode();

    char * str;
};

void main()
{
    char *i = new char[35];
    strcpy(i, "Welcome to Hopeville, Iowa");
    StringNode * r = new StringNode(i);
    LinkedList * y = new LinkedList();
    y->addElement(r);

    i = new char[35];
    strcpy(i, "Don't blink or you'll miss it.");
    r = new StringNode(i);
    y->addElement(r);

    i = new char[35];
    strcpy(i, "SWCC is cool!!!");
    r = new StringNode(i);
    y->addElement(r);

    y->removeElement(1);

    r = (StringNode *)y->elementAt(1);
    printf("%s\n", r->str);
    delete y;
}

StringNode::StringNode(const char * p)
{
    str = new char[strlen(p)];
    strcpy(str, p);
}

StringNode::~StringNode()
{
    printf("Calling destructor...\n");
    delete str;
    str = NULL;
}

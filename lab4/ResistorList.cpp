

#include <iostream>
#include <string>
#include "ResistorList.h"
using namespace std;


ResistorList::ResistorList()
{

    head=NULL;
}

ResistorList::~ResistorList()
{
 Resistor* currNode=head;
 Resistor* prevNode=NULL;

   while (currNode != NULL) {
      prevNode = currNode;
      currNode = currNode->getNext ();
      delete prevNode;
   }
   head = NULL;
}

void ResistorList::insertResistor(string name, double resistance, int node1, int node2)
{
    Resistor *p=head;
    Resistor *prev=NULL;
    Resistor *new_=new Resistor(name,resistance,node1,node2);

    while(p!=NULL)
    {
        prev=p;
        p=p->getNext();
    }
    new_->setNext(p);
    if(prev==NULL)//insert if resistor list is empty
        head=new_;
    else prev->setNext(new_);//insert in the end
}
Resistor* ResistorList::searchResistor(string name)
{
    Resistor* p=head;
    while(p!=NULL)
    {
        if(p->getName()==name)
        {
            return p;
        }
        p=p->getNext();
    }
    return NULL;
}
bool ResistorList::deleteResistor(string name)
{
    Resistor *p=head;
    Resistor *prev=NULL;

    while(p!=NULL && p->getName()!=name)
    {
        prev=p;
        p=p->getNext();
    }//no resistor to delete
    if(p==NULL || p->getName()!=name)
    {
        return false;
    }

    if(prev==NULL)// deleting first resistor
    {
        head=p->getNext();
    }
    else
        prev->setNext(p->getNext());
    delete p;
    return true;
}
Resistor* ResistorList::getHead()
{
    return head;
}
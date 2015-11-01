#define MIN_ITERATION_CHANGE 0.0001
#include <iostream>
#include <cmath>
#include "NodeList.h"

using namespace std;

NodeList::NodeList()
{
    head=NULL;
}
NodeList::~NodeList()
{

  Node *prevNode=NULL;
  Node *currNode = head;
   while (currNode != NULL) {
      prevNode = currNode;
      currNode = currNode->getNext ();
      delete prevNode;
   }
   head = NULL;
}
bool NodeList::nodeExists(int noden)
{
    Node *p=head;
    while(p!=NULL)
    {
        if(p->getNode()==noden)
            {
                return true;
            }
        p=p->getNext();
    }
    return false;
}
Node* NodeList::gethead()
{
    return head;
}

 void NodeList::sethead(Node *head_)
 {
     head=head_;
 }

Node* NodeList::searchNode(int noden)
{
    Node *p=head;
    while(p!=NULL)
    {
        if(p->getNode()==noden)
            {return p;}
        p=p->getNext();
    }
    return NULL;
}

void NodeList::insertNode (int noden)
{
    Node *p=head;
    Node *prev=NULL;
    Node *n=new Node(noden);
    while (p!=NULL && p->getNode()<noden)
    {
        prev=p;
        p=p->getNext();
    }
      n->setNext(p);
    if(prev==NULL)//insert at the end of list
      {
        head=n;
      }
    else
        prev->setNext(n);
}

bool NodeList::resistorExists(string Rname)
{
    Node *p=head;
    while(p!=NULL)
    {
        if(p->getRlist()->searchResistor(Rname)!=NULL)
            {
                return true;
            }
        p=p->getNext();
    }
    return false;
}

Resistor* NodeList::findresistor(string Rname)
{
    Node *p=head;

    while(p!=NULL)
    {
        Resistor *resistora=p->getRlist()->searchResistor(Rname);
        if(resistora!=NULL && resistora->getName()==Rname)
            {
                return resistora;
            }
        p=p->getNext();
    }
    return NULL;
}

double NodeList::changeResistance(string Rname, double &Rresistance)
{
    double tempres;
    Node *p=head;
    while(p!=NULL)
    {   //check all the nodes and resistor lists to find the resistor name
        Resistor *resP=p->getRlist()->searchResistor(Rname);
        if(resP!=NULL && resP->getName()==Rname)
            {
                tempres=p->getRlist()->searchResistor(Rname)->getResistance();
                p->getRlist()->searchResistor(Rname)->setResistance(Rresistance);
            }
        p=p->getNext();
    }
    return tempres;
}

void NodeList::deleteRes(string Rname)
{
    Node *p=head;
    while(p!=NULL)
    {   //check all nodes and resistor lists to find the resistor name
        Resistor *resP=p->getRlist()->searchResistor(Rname);
        if(resP!=NULL && resP->getName()==Rname)
        {
           if(p->getRlist()->deleteResistor(Rname)==true)
           {p->setNumRes(p->getNumRes()-1);}
        }
        p=p->getNext();
    }
    cout<<"Deleted: resistor "<<Rname<<endl;
}

bool NodeList::AreNodesSet()
{
    Node *p=head;
    while(p!=NULL)
    {
        if(p->getState()=="set")
        {
            return true;
        }
        p=p->getNext();
    }
    return false;
}
void NodeList::changetozero()
{
    double zero=0;
    Node *p=head;
    while(p!=NULL)
    {
        if(p->getState()=="unset")
        {
            p->setVoltage(zero);
            p->calculate(zero);
        }
        p=p->getNext();
    }
}
bool NodeList::ifVoltageChanged()
{
    Node *p=head;
    int flag=0;
    while(p!=NULL)
    {
        double currentV=p->getVoltage();
        double calcV=p->getcalcV();
        if(fabs(currentV-calcV)> MIN_ITERATION_CHANGE|| fabs(calcV-currentV)> MIN_ITERATION_CHANGE)
        {
            flag=1;//when voltage changed, flag raises and loop repeats and returns false
        }
        p->setVoltage(p->getcalcV());
        p=p->getNext();
    }
    if(flag==1)
        return false;
    else return true;
}

void NodeList::SolveVoltage(NodeList &nlist)
{
    do{

    Node *p=head;
    while(p!=NULL)
    {
         double denosum=0;//numerator of the KCL
         double numersum=0;//denominator of the KCL

        if(p->getState()=="unset")
        {
            Resistor *Rptr=p->getRlist()->getHead();
            while(Rptr!=NULL)
            {
                Node *temp=NULL;//temp node is the node that will get the voltage of the node with the resistor
                if(Rptr->getNode1()!=p->getNode())
                {//if endpoint1 is not equal to the nodeid then temp will point to the voltage of the endpoint1
                    temp=nlist.searchNode(Rptr->getNode1());
                }
                else
                {//if endpoint1 is equal to nodeid, temp will point to the other voltage node
                    temp=nlist.searchNode(Rptr->getNode2());
                }
                double tempVolt=(temp->getVoltage());
                double tempRes=(Rptr->getResistance());
                numersum=numersum+(tempVolt/tempRes);//summing the equation
                denosum=denosum+(1/tempRes);
                Rptr=Rptr->getNext();
            }
            p->calculate(numersum/denosum);//sets the calculated voltage
        }
        p=p->getNext();
    }

    }while(nlist.ifVoltageChanged()==false);
}
void NodeList::SolvePrint()
    {
        Node *p=head;
        while(p!=NULL)
        {
            p->printVoltage();
            p=p->getNext();
        }
    }



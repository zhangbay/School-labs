#include <iomanip>
#include <iostream>
#include "Node.h"

using namespace std;

Node::Node()
{
    voltage=0;
    nodeid=0;
    next=NULL;
    calcV=0;
    rlist=new ResistorList();
    numres=0;
    state="unset";
}

Node::~Node()
{
    delete rlist;
}

Node::Node(int nodeid_)
{
    voltage=0;
    nodeid=nodeid_;
    rlist=new ResistorList();
    next=NULL;
    numres=0;
    state="unset";
    calcV=0;
}
Node::Node(int nodeid_, Node *n)
{
    voltage=0;
    numres=0;
    nodeid=nodeid_;
    rlist=new ResistorList();
    next=n;
    state="unset";
    calcV=0;
}

int Node::getNode()
{
    return nodeid;
}

void Node::setNode(int nodeid_)
{
    nodeid=nodeid_;
}
void Node::setNumRes(int number)
{
    numres=number;
}

void Node::setNext(Node *m)
{
    next=m;
}
Node* Node::getNext()
{
    return next;
}

ResistorList* Node::getRlist()
{
    return rlist;
}
double Node::getVoltage()
{
    return voltage;
}
void Node::setVoltage(double volt)
{
    voltage=volt;
}

int Node::getNumRes()
{
    return numres;
}

void Node::setState(string newstate)
{
    state=newstate;
}
string Node::getState()
{
    return state;
}
double Node::getcalcV()
{
    return calcV;
}

void Node::calculate(double volt)
{
    calcV=volt;
}

void Node::printVoltage()
{
cout << fixed << setprecision(2);
cout<<"  Node "<<nodeid<<": "<<voltage<<" V"<<endl;
}

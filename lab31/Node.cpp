#include"Node.h"
#include <iostream>

using namespace std;

Node::Node()
{
    numRes=0;
    for(int i=0; i<MAX_RESISTORS_PER_NODE; i++)
        {   resIDArray[i]=' ';
        }
}
Node::~Node()
{

}
bool Node::addResistor(int rIndex)
{

     for(int i=numRes; i<MAX_RESISTORS_PER_NODE; i++)
        {
            if (resIDArray[i]==' ')
            {
                resIDArray[i]=rIndex;
                numRes++;
                return true;
            }
        }

    return false;
}

void Node::print(int nodeIndex)
{
    extern int maxRes;
    extern Resistor *resarray;
    cout<<"Connections at node "<<nodeIndex<<": "<<numRes<<" resistor(s)"<<endl;
    for(int i=0; i<=maxRes; i++)
    {
        if(resarray[i].getNode1()!=' ')
        {
            cout<<resarray[i].getName()<<"connected at"<<resarray[i].getNode1()<<endl;
        }
       
    }
}

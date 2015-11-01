#include"Node.h"
#include <iostream>
#include <iomanip>

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
    
    for(int i=0; i<maxRes; i++)
    {
        if(resarray[i].getNode1()==nodeIndex)
        {
            cout.width(20);cout<<left<<resarray[i].getName()<<" "; 
            cout.width(8); cout<<right<<setprecision(2)<<resarray[i].getResistance()<<" "; 
            cout<<" Ohms "<<resarray[i].getNode1()<<" -> "<<resarray[i].getNode2()<<endl;
        }
        else if(resarray[i].getNode2()==nodeIndex)
        {
            cout.width(20);cout<<left<<resarray[i].getName()<<" "; 
            cout.width(8); cout<<right<<setprecision(2)<<resarray[i].getResistance()<<" "; 
            cout<<" Ohms "<<resarray[i].getNode1()<<" -> "<<resarray[i].getNode2()<<endl;
        }
       
    }
}

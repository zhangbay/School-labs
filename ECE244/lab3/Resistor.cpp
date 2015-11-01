#include <string>
#include <iostream>
#include "Resistor.h"
#include <iomanip>
Resistor::Resistor()
{
    resistance=0;
    name=" ";
    endpointNodeIDs[0]=' ';
    endpointNodeIDs[1]=' ';
}
Resistor::~Resistor()
{
}
Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2])
{
    name=name_;
    resistance=resistance_;
    endpointNodeIDs[1]=endpoints_[1];
    endpointNodeIDs[2]=endpoints_[2];

}

double Resistor::getResistance() const
{
    return resistance;
}

string Resistor::getName()const
 {
    return name;
 }

int Resistor::getNode1()const
{
    return endpointNodeIDs[0];
}

int Resistor::getNode2()const
{
    return endpointNodeIDs[1];
}

void Resistor::setResistance (double resistance_)
 {
    resistance=resistance_;
 }
void Resistor::setName (string name1)
{
    name=name1;
}
void Resistor::setEndpoint1 (int node)
{
    endpointNodeIDs[0]=node;
}
void Resistor::setEndpoint2 (int node_)
{
    endpointNodeIDs[1]=node_;
}


void Resistor::print()
{
    cout.width(20); cout<<left<<name<<" "; 
    cout.width(8); cout<<right<<setprecision(2)<<resistance<<" "; 
    cout<<"Ohms "<<endpointNodeIDs[0]<<" -> "<<endpointNodeIDs[1]<<endl;
}

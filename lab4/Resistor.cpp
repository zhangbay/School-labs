
#include <string>
#include <iostream>
#include "Resistor.h"
#include <iomanip>

using namespace std;

Resistor::Resistor()
{
    resistance=0;
    name=" ";
    endpoints[0]=' ';
    endpoints[1]=' ';
    next=NULL;
}

Resistor::~Resistor()
{
}

Resistor::Resistor(string name_,double resistance_,int node1, int node2)
{
    name=name_;
    resistance=resistance_;
    endpoints[0]=node1;
    endpoints[1]=node2;
    next=NULL;
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
    return endpoints[0];
}

int Resistor::getNode2()const
{
    return endpoints[1];
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
    endpoints[0]=node;
}
void Resistor::setEndpoint2 (int node_)
{
    endpoints[1]=node_;
}


void Resistor::print()
{
    cout <<setw(20)<<left<<name<<setprecision(2)<<fixed<<setw(8)<<right<<resistance<<" Ohms "<<endpoints[0]<<" -> "<<endpoints[1]<<endl;
   // cout<<setw(20)<<left<<name<<resistance<<" Ohms "<<endpoints[0]<<"->"<<endpoints[1]<<endl;
}

void Resistor::setNext(Resistor* r)
{
    next=r;
}



#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Rparser.h"
#include "NodeList.h"


void Rparser_insertR(stringstream &linestream, string &name, double &resistance, int &node1, int &node2)
{//get the values
    linestream>>name;
    linestream>>resistance;
    linestream>> node1;
    linestream>> node2;
    cout << fixed << setprecision(2);
    cout<<"Inserted: resistor "<<name<<" "<<resistance<<" Ohms "<<node1<<" -> "<<node2<<endl;
}

bool Rparser_modifyR(stringstream &linestream, string &name, double &resistance, NodeList &nList)
{
    linestream>>name;
    if(nList.resistorExists(name)==false)
        return false;
    linestream>>resistance;
    return true;
}
bool Rparser_printR(stringstream &linestream, string &name, NodeList &nList)
{
    linestream>>name;
    if(nList.resistorExists(name)==false)
        {cout<<"Error: resistor "<<name<<" not found"<<endl;
        return false;}
    else
        {//variables for insert
            string resistorname;
            resistorname=nList.findresistor(name)->getName();
            double resist;
            resist=nList.findresistor(name)->getResistance();
            int n1,n2;
            n1=nList.findresistor(name)->getNode1();
            n2=nList.findresistor(name)->getNode2();
            cout<<"Print: "<<endl;
            cout.width(20); cout<<left<<resistorname<<" ";
            cout.width(8);  cout<<right<<setprecision(2)<<resist<<" ";
            cout<<"Ohms "<<n1<<" -> "<<n2<<endl;
            //cout<<setw(20)<<left<<resistorname<<resist<<" Ohms "<<n1<<"->"<<n2<<endl;
            return true;
        }
}
void Rparser_printNode(stringstream &linestream, int node,NodeList &nList)
{
    string nodeall;
    linestream>> nodeall;
    stringstream varstream(nodeall);
    if (nodeall=="all")
        {
            cout<<"Print: "<<endl;

            for(Node *nptr=nList.gethead();nptr!=NULL;nptr=nptr->getNext())
            {   if(nptr->getNumRes()==0)
                {}//number of resistors is 0 then the connections will not be printed
                else if(nList.gethead()->getRlist()->getHead()!=NULL)
                {
                cout<<"Connections at node "<<nptr->getNode()<<": "<<nList.searchNode(nptr->getNode())->getNumRes()<<" resistor(s)"<<endl;
                Resistor * p=nList.searchNode(nptr->getNode())->getRlist()->getHead();
                while(p!=NULL)
                    {
                        p->print();
                        p=p->getNext();
                    }
                }
            }
        return;
        }
    else
        {

            varstream>>node;
            cout<<"Print: "<<endl;
            if(nList.searchNode(node)!=NULL && nList.searchNode(node)->getRlist()->getHead()!=NULL)
            {
            cout<<"Connections at node "<<node<<": "<<nList.searchNode(node)->getNumRes()<<" resistor(s)"<<endl;
            Resistor * p=nList.searchNode(node)->getRlist()->getHead();
            while(p!=NULL)
            {
                p->print();
                p=p->getNext();
            }
            }
            else return;
        }

}
string Rparser_deleteR(stringstream &linestream, string &name)
{
    linestream>>name;
    return name;
}
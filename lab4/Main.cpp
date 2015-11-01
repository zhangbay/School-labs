/*
 * File:   Main.cpp
 * Author: zhangf30
 *
 * Created on November 6, 2013, 4:09 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Rparser.h"
#include "NodeList.h"
#include "ResistorList.h"
using namespace std;

#define MIN_ITERATION_CHANGE 0.0001
/*
 *
 */
int main(int argc, char** argv) {

    string command, name;
    double resistance, volts;
    int node1,node2;
    string Set="set";
    string Unset="unset";

    NodeList circuit;
    string input;
    cout <<"> ";
    cout.flush();
    getline(cin, input);


    while(!cin.eof())
    {
        stringstream line(input);
        line>>command;
        if (command=="insertR")
        {
            Rparser_insertR(line,name,resistance, node1, node2);
           if(circuit.nodeExists(node1)==false)
            {
                circuit.insertNode(node1);
            }
            if (circuit.nodeExists(node2)==false)
            {   //nodeid is not created, create a new node
                circuit.insertNode(node2);
            }
            ResistorList *first=circuit.searchNode(node1)->getRlist();
            ResistorList *second=circuit.searchNode(node2)->getRlist();
            first->insertResistor(name, resistance, node1, node2);
            second->insertResistor(name, resistance, node1, node2);

            circuit.searchNode(node1)->setNumRes(circuit.searchNode(node1)->getNumRes()+1);
            circuit.searchNode(node2)->setNumRes(circuit.searchNode(node2)->getNumRes()+1);
            //setting the number of resistors per node once inserted
        }
        else if(command=="modifyR")
        {
            if(Rparser_modifyR(line,name,resistance,circuit)==false)
                cout<<"Error: resistor "<<name<<" not found"<<endl;
            else{   //old resistance value returned; resistance variable has new resistance
                    double oldres;
                    oldres=circuit.changeResistance(name, resistance);
                    cout << fixed << setprecision(2);
                    cout<<"Modified: resistor "<<name<<" from "<<oldres<<" Ohms to "<<resistance<<" Ohms"<<endl;

                }

        }
        else if(command=="printR")
        {
            Rparser_printR(line,name,circuit);
        }
        else if(command=="printNode")
        {
            Rparser_printNode(line, node1,circuit);
        }
        else if(command=="deleteR")
        {   //call to check if the command is all or a resistor name
            string call=Rparser_deleteR(line,name);
            if(call=="all")
            {

                 Node *currNode;
                 Node *prevNode=NULL;
                 currNode = circuit.gethead();
                 while (currNode != NULL) {
                        prevNode = currNode;
                        currNode = currNode->getNext ();
                        delete prevNode;
                    }
                   circuit.sethead(NULL);//set the head to null
                cout<<"Deleted: all resistors"<<endl;

            }
            else
            {
                if(circuit.resistorExists(call)==false)
                {
                    cout<<"Error: resistor "<<call<<" not found"<<endl;
                }
                else
                {

                    circuit.deleteRes(call);
                }
            }
        }
        else if(command=="setV")
        {
            line>>node1;
            line>>volts;
            // set both voltages to the volts var
            if(circuit.gethead()==NULL ||circuit.nodeExists(node1)==false)//if there is no nodes
            {
                circuit.insertNode(node1);
            }
            circuit.searchNode(node1)->setVoltage(volts);
            circuit.searchNode(node1)->calculate(volts);
            circuit.searchNode(node1)->setState(Set);
            
            cout << fixed << setprecision(2);
            cout<<"Set: node "<<node1<<" to "<<volts<<" Volts"<<endl;
           
        }
        else if(command=="unsetV")
        {
            line>>node1;
            if(circuit.gethead()==NULL||circuit.nodeExists(node1)==false)//if there is no nodes
            {
                circuit.insertNode(node1);
            }
            circuit.searchNode(node1)->setState(Unset);
            
            cout<<"Unset: the solver will determine the voltage of node "<<node1<<endl;


        }
        else if(command=="solve")
        {
            if(circuit.AreNodesSet()==false)
            {
                cout<<"Error: no nodes have their voltage set"<<endl;
            }
            else
                {
                    circuit.changetozero();
                    circuit.SolveVoltage(circuit);

                    cout<<"Solve:"<<endl;
                    circuit.SolvePrint();
                }
        }
        cout <<"> ";
        cout.flush();
        getline(cin, input);
    }
    Node *currNode;
    Node *prevNode=NULL;
    currNode = circuit.gethead();
    while (currNode != NULL) 
    {
      prevNode = currNode;
      currNode = currNode->getNext ();
      delete prevNode;
    }
     
    circuit.sethead(NULL);
    return 0;
}
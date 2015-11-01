/*
 * File:   NodeList.h
 * Author: zhangf30
 *
 * Created on October 29, 2013, 2:38 PM
 */
#ifndef NODELIST_H
#define	NODELIST_H


#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "Resistor.h"

using namespace std;



class NodeList
{
    private:
    Node *head;
    public:
    NodeList();
    ~NodeList();

   // functions for Nodes
    bool nodeExists(int noden);//checks if the node is already created if so, add resistors to the node else, insert node
    Node* searchNode (int noden);
    void insertNode (int noden);
    Node* gethead();
    void sethead(Node* head_);

    //Functions for resistors
    bool resistorExists(string Rname);
    //deletes the resistor in the node list
    void deleteRes(string Rname);
    //find if resistor with the name exist
    Resistor* findresistor(string Rname);

    double changeResistance(string Rname, double &Rresistance);//change the resistances of the resistor

    //Functions for voltages
    bool AreNodesSet();//check if any of the node has a set voltage
    void changetozero();//change the unset nodes to 0
    bool ifVoltageChanged();//check if any voltage is changed by minimum iteration

    void SolveVoltage(NodeList & nlist);//solve the volts for each node
    void SolvePrint();//once solved, print out the nodes

};




#endif	/* NODELIST_H */

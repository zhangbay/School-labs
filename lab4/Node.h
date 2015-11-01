   /*
 * File:   Node.h
 * Author: zhangf30
 *
 * Created on October 29, 2013, 2:37 PM
 */

#ifndef NODE_H
#define	NODE_H
#include <iostream>
#include "ResistorList.h"

class Node
{
private:
    int nodeid;
    double voltage;
    double calcV;
    Node *next;
    ResistorList *rlist;
    int numres;
    string state;
public:

    Node();
    ~Node();
    Node(int nodeid_);
    Node(int nodeid_, Node *n);

    //access functions
    int getNode();//gets the nodeid
    void setNode(int nodeid_) ;
    Node* getNext();
    void setNext(Node *m);
    void setNumRes(int number);
    ResistorList* getRlist();

    double getVoltage();
    void setVoltage(double volt);
    //set or unset
    void setState(string newstate);
    string getState();
    //access for calculated voltages
    double getcalcV();
    void calculate(double volt);

    void printVoltage();

    int getNumRes();
};


#endif	/* NODE_H */

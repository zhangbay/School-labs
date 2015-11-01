/*
 * File:   Resistor.h
 * Author: zhangf30
 *
 * Created on October 29, 2013, 2:37 PM
 */

#ifndef RESISTOR_H
#define	RESISTOR_H

#include <iostream>
#include <string>

using namespace std;

class Resistor
{
    private:
    string name;
    double resistance;
    int endpoints[2];
    Resistor *next;

    public:

    Resistor();
    ~Resistor();
    Resistor(string name_,double resistance_,int node1,int node2);

    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    int getNode1() const;
    int getNode2() const;
    Resistor *getNext(){return next;};

    void setResistance (double resistance_);
    void setName (string name1);
    void setEndpoint1 (int node);
    void setEndpoint2 (int node_);
    void setNext(Resistor *r);

    void print ();
};

#endif	/* RESISTOR_H */

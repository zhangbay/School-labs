/*
 * File:   ResistorList.h
 * Author: zhangf30
 *
 * Created on October 29, 2013, 2:38 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H
#include <iostream>
#include <string>
#include "Resistor.h"
using namespace std;

class ResistorList
{
    private:
        Resistor *head;

    public:
        ResistorList();
        ~ResistorList();

        void insertResistor(string name, double resistance, int node1, int node2);
        Resistor* searchResistor(string name);
        bool deleteResistor(string name);
        Resistor* getHead();

};


#endif	/* RESISTORLIST_H */

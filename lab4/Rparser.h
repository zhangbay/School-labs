/*
 * File:   Rparser.h
 * Author: zhangf30
 *
 * Created on October 29, 2013, 2:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "NodeList.h"

//using namespace std;

#ifndef RPARSER_h
#define	RPARSER_h


void Rparser_insertR(stringstream &linestream, string &name, double &resistance, int &node1, int &node2);
bool Rparser_modifyR(stringstream &linestream, string &name, double &resistance, NodeList & nList);
bool Rparser_printR(stringstream &linestream, string &name, NodeList &nList);
void Rparser_printNode(stringstream &linestream, int node,NodeList &nList);
string Rparser_deleteR(stringstream &linestream, string &name);





#endif	/* RPARSER_H */

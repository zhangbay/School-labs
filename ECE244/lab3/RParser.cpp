#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "RParser.h"


#define MIN_NUMBER 0


using namespace std;

void RParser(string line)
{
    string command, name;
    double resistance;
    extern int maxRes;
    int maxNode,node1,node2,rIndex;
    extern Resistor *resarray;
    resarray=NULL;

    Node *nodearray=NULL;

    while(!cin.eof())
    {
        stringstream ls(line);
        ls>>command;
        if (command=="maxVal")
        {   ls>>maxNode;
            if(maxNode<=0)
            {
                cout<<"Error: maxVal arguments must be greater than 0"<<endl;
            }
            else
                {   ls>>maxRes;
                    if(maxRes<=0)
                    {
                        cout<<"Error: maxVal arguments must be greater than 0"<<endl;
                    }
                    else
                        {
                            if(resarray!=NULL && nodearray!=NULL)
                            {
                                //delete the arrays that are set and reset it to NULL
                                delete []resarray;
                                resarray=NULL;
                                delete []nodearray;
                                nodearray=NULL;
                            }
                           
                            cout<<"New network: max node number is "<<maxNode<<"; max resistors is "<<maxRes<<endl;
                            resarray=new Resistor[maxRes];
                            nodearray=new Node[maxNode+1];
                            rIndex=0;
                        }
                }
        }
        else if (command=="insertR")
        {
            ls >>name;
            ls>>resistance;
            ls>> node1;
            if(node1<0 || node1>maxNode)
            {
                cout<< "Error: node "<<node1<<" is out of permitted range 0-"<<maxNode<<endl;

            }
            else
            {
                ls>>node2;
                if(node2<0 || node2>maxNode)
                {

                    cout<< "Error: node "<<node2<<" is out of permitted range 0-"<<maxNode<<endl;
                }
                else
                {
                        if(rIndex<maxRes)
                        {
                            if(nodearray[node1].Node::addResistor(rIndex)==true && nodearray[node2].Node::addResistor(rIndex)==true)
                            {
                                resarray[rIndex].setResistance(resistance);
                                resarray[rIndex].setName(name);
                                resarray[rIndex].setEndpoint1(node1);
                                resarray[rIndex].setEndpoint2(node2);
                                 cout << fixed << setprecision(2);
                                cout<<"Inserted: resistor "<<name<<" "<<resistance<<" Ohms "<<node1<<" -> "<<node2<<endl;
                                rIndex++;
                            }
                            else if(nodearray[node1].Node::addResistor(rIndex)!=true || nodearray[node2].Node::addResistor(rIndex)!=true)
                            {
                                cout<<"Error: node is full"<<endl;
                            }
                        }
                        else if(rIndex>=maxRes) 
                                {
                                         cout<<"Error: resistor array is full"<<endl;
                                }
                }
            }
        }
        else if(command=="modifyR")
          {
            bool is_there_res=false;
              ls>> name;
              ls>>resistance;
              for(int i=0; i<maxRes; i++)
              {
                 
                    if(name==resarray[i].getName())
                        {   double oldres=resarray[i].getResistance();
                            resarray[i].setResistance(resistance);
                            cout<<"Modified: resistor "<<resarray[i].getName()<<" from "<<oldres<<" Ohms to "<<resarray[i].getResistance()<<" Ohms"<<endl;
                            is_there_res=true;
                    }
              }
              if(is_there_res==false)
              {
                  cout<<"Error: resistor "<<name<<" not found"<<endl;
              }

          }
        else if(command=="printNode")
        {
             string nodeall;
             ls>> nodeall;
             stringstream varstream(nodeall);// dummy string stream to sort out the string input and a int input
             

                if (nodeall=="all")
                    {   cout<<"Print: "<<endl;
                    if(nodearray!=NULL){
                        for(int i=0;i<=maxNode;i++)
                        {
                            nodearray[i].print(i);
                        }
                    }  
                    }
                else{   cout<<"Print: "<<endl;
                        varstream>>node1;
                        if(nodearray!=NULL){
                        nodearray[node1].print(node1);
                        }
                }
        }
        else if(command== "deleteR")
        {
            ls>>name;
            if(name=="all")
            {
                delete []resarray;
                //resarray=NULL;
                resarray=new Resistor[maxRes];
                rIndex=0;
                delete []nodearray;
               // nodearray=NULL;
                nodearray=new Node[maxNode+1];
                cout<<"Deleted: all resistors"<<endl;
            }

        }
        else if (command=="printR")
        {
            ls>>name;

            if(name=="all")
            {  cout<<"Print: "<<endl;
               if(resarray!=NULL)
                {
 
                for(int i=0; i < maxRes; i++)
                    {
                        if(resarray[i].getName()!=" ")
                        {   // is the order the inserted?
                            resarray[i].print();
                            continue;
                        }
                    }
                }
            }
            else
            {
                bool is_there_res=false;
                if(resarray!=NULL){
                 cout<<"Print: "<<endl;
                    for(int i=0; i < maxRes; i++)
                    {
                        if(name==resarray[i].getName())
                        {
                            resarray[i].print();
                            is_there_res=true;
                            continue;
                        }
                    }
                }
                if(is_there_res==false)
                {
                     cout<<"Error: resistor "<<name<<" not found"<<endl;
                }
            }
        }


            cout <<"> ";
            cout.flush();
        getline(cin, line);
}
    delete []resarray;
    resarray=NULL;
    delete []nodearray;
    nodearray=NULL;
}


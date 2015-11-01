/*
 * File:   main.cpp
 * Author: zhangf30
 *
 * Created on November 12, 2013, 2:26 PM
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "DBentry.h"
#include "TreeDB.h"

using namespace std;

/*
 *
 *
 */
ostream& operator<< (ostream& out,const TreeDB& rhs)
{
    rhs.printall(rhs.root);
    return out;
}

ostream& operator<<(ostream& out, const DBentry & rhs)
{
    string stat;
    if(rhs.active==false)
    {
        stat = "inactive";
    }
    else
    {
        stat="active";
    }

    out << rhs.name <<" : "<< rhs.IPaddress << " : "<< stat<<endl;
    return out;
}


int main(int argc, char** argv) {

    string command, name, status;
    unsigned int IPaddress;

    string input;
    TreeDB treepointer;
    cout <<"> ";
    cout.flush();
    getline(cin, input);


    while(!cin.eof())
    {
        stringstream ls(input);
        ls>>command;
        if(command=="insert")
        {
            ls>>name;
            if(treepointer.find(name)!=NULL)
            {
                cout<<"Error: entry already exists"<<endl;
            }
            else{
                    ls>>IPaddress;
                    ls>>status;

                    bool istrue;
                    if(status=="active")
                        {
                            istrue=true;
                        }
                    else istrue=false;

                    DBentry *entry=new DBentry(name, IPaddress, istrue);
                    treepointer.insert(entry);
                    cout<<"Success"<<endl;

            }
        }
        else if(command=="find")
        {
            ls>>name;
            if(treepointer.find(name)==NULL)
            {
                cout<<"Error: entry does not exist"<<endl;
            }
            else
            {
                string status;
                if(treepointer.find(name)->getActive()==true)
                {
                    status="active";
                }
                else status="inactive";

                cout<<treepointer.find(name)->getName()<<" : "<<treepointer.find(name)->getIPaddress()<<" : "<<status<<endl;
            }
        }
        else if(command=="remove")
        {
            ls>>name;
            if(treepointer.remove(name)==true)
            {
                cout<<"Success"<<endl;
            }
            else
            {
                cout<<"Error: entry does not exist"<<endl;
            }
        }
        else if(command=="printall")
        {
            cout<<treepointer;
        }
        else if(command=="printprobes")
        {
            ls>> name;
            if(treepointer.find(name)==NULL)
            {
                cout<<"Error: entry does not exist"<<endl;
            }
            else
            {
                treepointer.find(name);
                treepointer.printProbes();
            }
        }
        else if(command=="removeall")
        {
            treepointer.clear();
            cout<<"Success"<<endl;

        }
        else if(command=="countactive")
        {
            treepointer.countActive();
        }
        else if(command== "updatestatus")
        {
            ls>>name;
            if(treepointer.find(name)==NULL)
            {
                cout<<"Error: entry does not exist"<<endl;
            }
            else{
                ls>>status;
                if(status=="active")
                {
                    treepointer.find(name)->setActive(true);
                    cout<<"Success"<<endl;
                }
                else
                {
                    treepointer.find(name)->setActive(false);
                    cout<<"Success"<<endl;
                }
            }
        }
        cout <<"> ";
        cout.flush();
        getline(cin, input);
    }



    return 0;
}


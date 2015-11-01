/*
 * File:   main.cpp
 * Author: zhangf30
 *
 * Created on September 24, 2013, 2:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#define MAX_NUMBER 5000
#define MIN_NUMBER 0


using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

    string line, command, name;
    double resistance;
    int node1, node2;

    cout <<"> ";
    cout.flush();

    getline(cin, line);

    while(!cin.eof())
    {
        stringstream ls(line);

        ls>>command;
        if (ls.fail())
        {
            cout<<"Error: invalid command"<<endl;
            ls.clear();
        }

        else if (command=="insertR")
        {
            ls >>name;
            if (ls.fail())
            {   cout<<"Error: too few arguments"<<endl;
                ls.clear();
            }
            else if (name!="all")
            {
                ls>>resistance;
                if (ls.fail())
                {
                    if (ls.eof())
                    {

                    cout<<"Error: too few arguments"<<endl;
                    }
                    else cout<<"Error: invalid argument"<<endl;
                    ls.clear();
                }
                else if (resistance<0)
                        {
                                cout<<"Error: negative resistance"<<endl;
                        }
                else
                        {
                                string fake;
                                ls>> node1;
                                fake=ls.peek();
                                if (ls.fail())
                                {
                                    if (ls.eof())
                                        {
                                            if(node1<MIN_NUMBER || node1>MAX_NUMBER)
                                            {
                                                cout<<"Error: node "<<node1<<" is out of permitted range "<<MIN_NUMBER<<"-"<<MAX_NUMBER<<endl;
                                            }
                                         else cout<<"Error: too few arguments"<<endl;
                                        }

                                    else
                                      {
                                          cout<<"Error: invalid argument"<<endl;
                                      }
                                    ls.clear();
                                }

                                else if (fake!=" ")
                                   {
                                        cout<<"Error: invalid argument"<<endl;
                                   }
                                else if(node1<MIN_NUMBER || node1>MAX_NUMBER)
                                {
                                    cout<<"Error: node "<<node1<<" is out of permitted range "<<MIN_NUMBER<<"-"<<MAX_NUMBER<<endl;
                                }
                                else {
                                  string fnode2;
                                  string junk;
                                  ls>> node2;
                                   fnode2=ls.peek();
                                    if (fnode2 !=" " && !ls.eof()){
                                         cout<<"Error: invalid argument"<<endl;
                                        }
                                   else if (node1==node2)
                                        {
                                        cout <<"Error: both terminals of resistor connect to node "<<node1<<endl;
                                        }
                                   else if(node2<MIN_NUMBER || node2>MAX_NUMBER)
                                        {
                                            cout<<"Error: node "<<node2<<" is out of permitted range "<<MIN_NUMBER<<"-"<<MAX_NUMBER<<endl;
                                        }
                                   else {
                                       ls>>junk;

                                       if (!ls.fail())
                                       {
                                           cout<< "Error: too many arguments"<<endl;
                                       }
                                       else {

                                                cout << fixed << setprecision(2);
                                                cout<<"Inserted: resistor "<<name<<" "<<resistance<<" Ohms "<<node1<<" -> "<<node2;
                                                break;
                                             }
                                   }
                                   //else if (ls.fail())
                                    //{
                                       //cout <<"Error: too few arguments"<< endl;
                                    //    ls.clear();                                    //}
                            }}
            }
            else
                {
                   cout<<"Error: resistor name cannot be the keyword "<<"\"all\""<<endl;
            }
    }

          else if (command=="modifyR")
          {
              ls>> name;
              if (ls.fail())
                 {
                  cout<<"Error: too few arguments"<<endl;
                  ls.clear();
                 }
            else if (name!="all")
            {
                string checkchar;
                ls>>resistance;

                 // if (checkchar !=" " && !ls.eof())
                     //  {
                      //   cout<<"Error: invalid argument"<<endl;
                      // }
                   if (ls.fail())
                    {  // checkchar=ls.peek();
                        if(ls.eof())
                        {
                            cout<<"Error: too few arguments"<<endl;
                        }
                        else {cout<<"Error: invalid argument"<<endl;}

                    }
                 else {

                        checkchar=ls.peek();
                        if (checkchar !=" " && !ls.eof())
                        {
                            cout<<"Error: invalid argument"<<endl;
                        }
                        else{
                                     string junk2;
                                          ls>> junk2;

                        if (!ls.fail())
                        {
                                 if (resistance<0)
                                    {
                                cout<<"Error: negative resistance"<<endl;
                                    }
                                else cout<<"Error: too many arguments"<<endl;
                        }
                        else if (resistance<0)
                            {
                                cout<<"Error: negative resistance"<<endl;
                            }

                        else{
                        cout << fixed << setprecision(2);
                        cout<<"ModifyR: resistor "<<name<<" to "<<resistance<<" Ohms "<<endl;
                        break;
                        }}
                 }

            }
            else
            {
                cout<<"Error: resistor name cannot be the keyword "<<"\"all\""<<endl;

            }

          }
        else if (command=="printR")
        {ls>> name;
        if (ls.fail())
                 {
                  cout<<"Error: too few arguments"<<endl;
                  ls.clear();
                 }
        else if (name=="all")
                {
                    string junk3name;
                    ls>> junk3name;
                    if (!ls.fail())
                    {
                        cout<<"Error: too many arguments"<<endl;
                        ls.clear();
                    }
               else {cout<<"Print: all resistors"<< endl;
                break;}
                }
        else {
             string junk3;
             ls>> junk3;

             if (!ls.fail())
                {
                  cout<<"Error: too many arguments"<<endl;
                }
             else{

                 cout<<"PrintR: resistor "<<name<<endl;
                 break;
             }
        }

        }
        else if (command=="printNode")
        {
            string nodeall;
            ls>> nodeall;
        if (ls.fail())
               {

                if(ls.eof())
                   {
                         cout<<"Error: too few arguments"<<endl;
                   }
                ls.clear();
                }
        else
        {
                            stringstream varstream(nodeall);

                if (nodeall=="all")
                {
                    string junk4name;
                    ls>> junk4name;
                    if (!ls.fail())
                    {
                        cout<<"Error: too many arguments"<<endl;
                        ls.clear();

                    }
                     else    {cout<<"Print: all nodes"<<endl;
                         break;}
                }
                else{
                varstream>>node1;
               if (varstream.fail() && nodeall!="all")
                 {
                    cout<<"Error: invalid argument"<<endl;
                    varstream.clear();
                 }
                else if(node1<MIN_NUMBER || node1>MAX_NUMBER)
                {
                         cout<<"Error: node "<< node1<< " is out of permitted range 0-5000"<<endl;
                }
                else {
                    string endchar;
                    endchar=varstream.peek();
                    if (endchar !=" " && !varstream.eof())
                        {
                            cout<<"Error: invalid argument"<<endl;
                        }
                    else{
                        string garbage;
                        ls>>garbage;
                        if (!ls.fail())
                        {
                            cout<<"Error: too many arguments"<<endl;
                        }
                        else{
                            cout<<"Print: node "<< node1<<endl;
                            break;
                        }

                }
                }
        }
        }

    }

        else if (command=="deleteR")
        {
            ls>>name;
            if (ls.fail())
            {
                if (ls.eof())
                {
                    cout<<"Error: too few arguments"<<endl;
                }
                ls.clear();
            }
            else if(name=="all")
            {
                string junk5name;
                    ls>> junk5name;
                    if (!ls.fail())
                    {
                        cout<<"Error: too many arguments"<<endl;
                        ls.clear();
                    }
                    else {cout<<"Deleted: all resistors"<<endl;
                    break;
                    }
            }
            else
                {
                    string trash;
                    ls>>trash;
                    if(!ls.fail())
                    {
                        cout<<"Error: too many arguments"<<endl;
                    }
                    else
                    {
                     cout<<"Deleted: resistor "<<name<<endl;
                        break;
                    }

                }
        }
        else //if(command!="deleteR" & command!="printNode" & command!="printR" & command!="modifyR" & command!="insertR" & command!=" ")
                {
                        cout <<"Error: invalid command"<<endl;
                }
                cout <<"> ";
                cout.flush();
        getline(cin, line);
    }


    return 0;
        }

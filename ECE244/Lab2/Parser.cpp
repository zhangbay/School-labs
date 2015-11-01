/*edited:04/10/2013 -final
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
void print_invalid_command()//prints out invalid command
{
    cout<<"Error: invalid command"<<endl;
}
void print_out_range(int node)//prints nodes out of range
{
  cout<<"Error: node "<<node<<" is out of permitted range "<<MIN_NUMBER<<"-"<<MAX_NUMBER<<endl;
}
void print_few_arg()//prints few arguments
{
    cout<<"Error: too few arguments"<<endl;
}
void print_many_arg()//prints many arguments
{
    cout<<"Error: too many arguments"<<endl;
}
void print_invalid_argument()//prints invalid argument
{
   cout<<"Error: invalid argument"<<endl;
}

bool is_too_many_arg(string input)//checks for too many arguments
{
    string junk;
    stringstream check(input);
    check>>junk;
    if(!check.fail())
    {check.clear();
     return true;}
    else return false;
}

int main(int argc, char** argv) {

    string line, command, name;
    double resistance;
    long int node1, node2;

    cout <<"> ";
    cout.flush();

    getline(cin, line);

    while(!cin.eof())
    {
        stringstream ls(line);

        ls>>command;
        if (ls.fail())
        {
            print_invalid_command();//if command has no input

            ls.clear();
        }

        else if (command=="insertR")
        {
            ls >>name;
            if (ls.fail())//no input
            {   print_few_arg();
                ls.clear();
            }
            else if (name!="all")
            {
                string wrongresist;
                ls>>resistance;
                wrongresist=ls.peek();//check for invalid resistance
                if (ls.fail())//no input
                {
                    if (ls.eof() && resistance >0)
                    {print_few_arg();}
                    else if (resistance<0)
                            {cout<<"Error: negative resistance"<<endl;}
                    else print_invalid_argument();//print non-double resistance error
                    ls.clear();
                }
                else  if (wrongresist!=" ")
                    {print_invalid_argument();}
                else if (resistance<0)
                        {
                            cout<<"Error: negative resistance"<<endl;}
                else
                        {
                                string fake;
                                ls>> node1;
                                fake=ls.peek();//dummy variable for invalid node input
                                if (ls.fail())
                                {
                                    if (ls.eof())
                                        {
                                            if(node1<MIN_NUMBER || node1>MAX_NUMBER)//check for error proiority
                                            {
                                                 print_out_range(node1);
                                            }
                                            else  print_few_arg();
                                        }
                                    else
                                      {
                                          print_invalid_argument();
                                      }
                                    ls.clear();
                                }

                                else if (fake!=" ")//check for invalid arg
                                   {
                                        print_invalid_argument();
                                   }
                                else if(node1<MIN_NUMBER || node1>MAX_NUMBER)
                                {
                                     print_out_range(node1);
                                }
                                else {
                                    string fnode2;
                                    string junk;//dummy variable for too many arguments
                                    ls>> node2;
                                    fnode2=ls.peek();//check if the node2 input is valid
                                    if (fnode2 !=" " && !ls.eof()){
                                        print_invalid_argument();}

                                    else if (node1==node2)

                                        cout <<"Error: both terminals of resistor connect to node "<<node1<<endl;

                                    else if(node2<MIN_NUMBER || node2>MAX_NUMBER)
                                             print_out_range(node2);
                                    else {
                                            ls>>junk;
                                            if (is_too_many_arg(junk)==false)
                                                {cout << fixed << setprecision(2);
                                                cout<<"Inserted: resistor "<<name<<" "<<resistance<<" Ohms "<<node1<<" -> "<<node2<<endl;}
                                            else {print_many_arg();}
                                        }

                            }
                    }
            }
            else cout<<"Error: resistor name cannot be the keyword "<<"\"all\""<<endl;
    }

          else if (command=="modifyR")
          {
              ls>> name;
              if (ls.fail())
                {
                  print_few_arg();
                  ls.clear();
                }
              else if (name!="all")
                {
                    string checkchar;//check for end character
                    string wrongsymbol;//check if resistance is just +,-,.
                    ls>>wrongsymbol;
                    stringstream dummystream(wrongsymbol);
                    if(wrongsymbol=="+" ||wrongsymbol=="-"||wrongsymbol==".")
                    {
                        print_invalid_argument();
                    }
                    else{
                            dummystream>>resistance;

                   if (dummystream.fail())
                    {
                        if(dummystream.eof())
                           print_few_arg();

                        else {print_invalid_argument();}

                    }
                    else {

                            checkchar=dummystream.peek();
                            if (checkchar !=" " && !dummystream.eof())//if end character of resist exist
                            {
                                print_invalid_argument();
                            }
                            else{           
                                     string discard;//check for extra input and too many arg
                                     ls>> discard;
                                     if (is_too_many_arg(discard)==true && resistance <0)
                                            cout<<"Error: negative resistance"<<endl;
                                     else if (is_too_many_arg(discard)==true && resistance >0)
                                            print_many_arg();

                                     else if (is_too_many_arg(discard)==false && resistance<0)
                                            cout<<"Error: negative resistance"<<endl;

                                     else{
                                            cout << fixed << setprecision(2);                                        
                                            cout<<"Modified: resistor "<<name<<" to "<<resistance<<" Ohms"<<endl;
                                         }
                                }
                        }
                    }
                }
                else cout<<"Error: resistor name cannot be the keyword "<<"\"all\""<<endl;
          }
        else if (command=="printR")
        {   ls>> name;
            if (ls.fail())
                 {
                   print_few_arg();
                  ls.clear();
                 }
            else if (name=="all")
                {
                    string leftovers;
                    ls>> leftovers;//check for too many args in all
                    if (is_too_many_arg(leftovers)==false)
                     {cout<<"Print: all resistors"<< endl;}
                    else { print_many_arg();}

                }
            else {
                    string extra;
                    ls>> extra;
                    if (is_too_many_arg(extra)==false)
                        {cout<<"Print: resistor "<<name<<endl;}
                    else {print_many_arg();}

             }
        }


        else if (command=="printNode")
        {
                string nodeall;
                ls>> nodeall;
            if (ls.fail())
                {

                    if(ls.eof())
                          {print_few_arg();}
                    ls.clear();
                }
            else
            {
                stringstream varstream(nodeall);// dummy string stream to sort out the string input and a int input

                if (nodeall=="all")
                    {
                        string useless;
                        ls>> useless;
                        if (is_too_many_arg(useless)==false)//check for too many arg
                            {cout<<"Print: all nodes"<<endl;}
                        else{print_many_arg();}
                    }
                else{
                    varstream>>node1;
                    if (varstream.fail() && nodeall!="all")//if node input is an invalid argument
                        {
                            print_invalid_argument();
                            varstream.clear();
                        }

                    else {
                            string endchar;
                            endchar=varstream.peek();//check if node input has extra chars
                            if (endchar !=" " && !varstream.eof())
                                {
                                    print_invalid_argument();
                                }
                            else if(node1<MIN_NUMBER || node1>MAX_NUMBER)
                                    {
                                        print_out_range(node1);
                                    }
                    else{
                            string garbage;
                            ls>>garbage;
                            is_too_many_arg(garbage);
                            if(is_too_many_arg(garbage)==false)
                                {
                                    cout<<"Print: node "<< node1<<endl;
                                }
                            else
                                {
                                    print_many_arg();
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
                     print_few_arg();
                ls.clear();
            }
            else if(name=="all")
            {
                    string toomany;
                    ls>> toomany;
                    if(is_too_many_arg(toomany)==false)
                        {
                        cout<<"Deleted: all resistors"<<endl;
                        }
                    else {print_many_arg();}
            }
            else
                {
                    string temp;
                    ls>>temp;
                    if(is_too_many_arg(temp)==false)
                        {
                            cout<<"Deleted: resistor "<<name<<endl;
                        }
                    else
                        {
                            print_many_arg();
                        }

                }
        }
        else{print_invalid_command();}
                cout <<"> ";
                cout.flush();
        getline(cin, line);
    }
    return 0;
        }

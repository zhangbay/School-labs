#include "RParser.h"
#include "Node.h"
#include "Resistor.h"
#include <iostream>
#include <sstream>

using namespace std;

Resistor *resarray;
int maxRes;
int main()
{
    string input;
    cout <<"> ";
    cout.flush();
    getline(cin, input);

    RParser(input);


    return 0;
}

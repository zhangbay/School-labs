#include "DBentry.h"
#include <iostream>

using namespace std;

DBentry::DBentry()
{
    name=" ";
    IPaddress=' ';
    active=false;
    
}
        
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active)
{
    name=_name;
    IPaddress=_IPaddress;
    active=_active;
}

DBentry::~DBentry()
{
    
}

void DBentry::setName(string _name)
{
    name=_name;
}

void DBentry::setIPaddress(unsigned int _IPaddress)
{
    IPaddress=_IPaddress;
}
    
        // sets whether or not this entry is active.
void DBentry::setActive (bool _active)
{
    active=_active;
}

        // returns the name.
string DBentry::getName() const
{
    return name;
}

	// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const
{
    return IPaddress;
}

        // returns whether or not this entry is active.
bool DBentry::getActive() const
{
    return active;
}


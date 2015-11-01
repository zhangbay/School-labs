#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"

Circle::Circle(string _name, string _colour, float _xcen, float _ycen, float _radius): Shape (_name, _colour, _xcen, _ycen)
{
    radius=_radius;
}

Circle::~Circle()
{
    
}
void Circle::print () const
{
     Shape::print();
     cout<<"circle ";
     cout<<"radius: "<<radius<<endl;
}
void Circle::scale (float scaleFac)
{
    radius*=scaleFac;
}
float Circle::computeArea () const
{
    float area;
    area= PI*radius*radius;
    return area;
}
float Circle::computePerimeter () const
{
    float perim;
    perim=2*PI*radius;
    return perim;
}
void Circle::draw (easygl* window) const
{
    window->gl_setcolor(getColour());
    window->gl_fillarc(getXcen(), getYcen(), radius, 0, 360);
}
bool Circle::pointInside (float x, float y) const
{
    float xdiff;
    float ydiff;
    xdiff=x-getXcen();
    ydiff=y-getYcen();
    float total= xdiff*xdiff+ydiff*ydiff;
    if(sqrt(total)>radius)//|Z-Z0|=R
        return false;
    else return true;
}

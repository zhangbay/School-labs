#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height): Shape (_name, _colour, _xcen, _ycen)
{
    width=_width;
    height=_height;
}

Rectangle::~Rectangle()
{
    
}


void Rectangle::print () const 
{
      Shape::print();
      cout<<"rectangle ";
      cout<<"width: "<<width<<" height: "<<height<<endl; 
}


void Rectangle::scale (float scaleFac) 
{
    width*=scaleFac;
    height*=scaleFac; 
}

float Rectangle::computeArea () const
{
    float area;
    area= width *height;
    return area;
}

float Rectangle::computePerimeter () const
{
    float perimeter;
    perimeter= 2*width +2*height;
    return perimeter;
}
void Rectangle::draw (easygl* window) const
{
    float xleft, ybottom, xright, ytop;
    //relative
    xleft=getXcen()-width/2;
    ybottom=getYcen()-height/2;
    xright=getXcen()+width/2;
    ytop=getYcen()+height/2;
    
    
    window->gl_setcolor(getColour());
    window->gl_fillrect(xleft,ybottom,xright, ytop);
}
bool Rectangle::pointInside (float x, float y) const
{//checks all sides up, down, left, right
    if((x<(getXcen()-width/2) && y>(getYcen()+height/2)) || (y<(getYcen()-height/2) && x>(getXcen()+width/2) )|| ( y>(getYcen()-height/2) && x>(getXcen()+width/2) )|| ( y<(getYcen()-height/2) && x<(getXcen()+width/2) )|| (x<(getXcen()-width/2) && y<(getYcen()+height/2)) ||( x>(getXcen()-width/2) && y>(getYcen()+height/2)))
        return false;
    else
        return true; 
}
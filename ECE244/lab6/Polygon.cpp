#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Polygon.h"

using namespace std;

Polygon::Polygon(string _name, string _colour, float _xcen, float _ycen, int _vertices, t_point *_relVertex): Shape (_name, _colour, _xcen, _ycen)
{
    vertices=_vertices;
    relVertex=_relVertex;
 
    //copies the array into the relVertex
    for(int i=0; i<vertices; i++)
    {
        relVertex[i].x=_relVertex[i].x;
        relVertex[i].y=_relVertex[i].y;
    }
}

Polygon::~Polygon()
{
    delete [] relVertex;
    relVertex=NULL;
}

void Polygon::print () const
{
    Shape::print();
    cout<<"polygon ";
    for(int i=0; i< vertices; i++)
    {
        cout<<"("<<getXcen()+relVertex[i].x<<","<<getYcen()+relVertex[i].y<<") " ;
    }
    cout<<endl;
}


void Polygon::scale (float scaleFac)
{
    for (int i = 0; i < vertices; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
float Polygon::computeArea () const{
    
   float area;
   area=0;
   int j=vertices-1;
   
   for(int i=0; i<vertices; i++)
   {// calculates the area
       area=area+(relVertex[j].x+relVertex[i].x) *(relVertex[j].y-relVertex[i].y);
       j=i;
   }
   return area/2;
  
}
float Polygon::computePerimeter () const
{
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   //adds up all the sides and their lengths
   for (int i = 0; i < vertices; i++) {
      endIndex = (i + 1) % vertices;
      dist = VecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}
void Polygon::draw (easygl* window) const
{
   t_point coords[vertices];
  
   //change to relative vertex
   for (int i = 0; i < vertices; i++) 
   {
      coords[i].x = relVertex[i].x+getXcen();
      coords[i].y = relVertex[i].y+getYcen();  
   }
    window->gl_setcolor(getColour());
    window->gl_fillpoly(coords,vertices);
}
bool Polygon::pointInside (float x, float y) const
{
   t_point click;//makes clicking point
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < vertices; istart++) {//for all points
      endIndex = (istart + 1) % vertices; // Next vertex after istart all points in the polygon
      vecOfSide = VecBetweenPoints (relVertex[istart], relVertex[endIndex]);
      yDistance = (click.y - relVertex[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
     
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = relVertex[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   return (sidesToLeft == 1);
}

// Return the (x,y) vector between start and end points for Polygon.
// Polygon needs to get vector to get the point inside or do the perimeter
t_point Polygon::VecBetweenPoints (t_point start, t_point end) const {
   t_point vector;
   vector.x = end.x - start.x;
   vector.y = end.y - start.y;
   return (vector);
}

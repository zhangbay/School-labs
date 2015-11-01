/* 
 * File:   Polygon.h
 * Author: zhangf30
 *
 * Created on November 26, 2013, 3:23 PM
 */

#ifndef POLYGON_H
#define	POLYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon: public Shape 
{
   private:
     //a soon to be array of x,y points
   t_point *relVertex;   
   // number of points
   int vertices;

   t_point VecBetweenPoints (t_point start, t_point end) const;
   
   public: 
        Polygon (string _name, string _colour, float _xcen, float _ycen, int _vertices, t_point *_relVertex);
        
        virtual ~Polygon();
        virtual void print () const;
        virtual void scale (float scaleFac);
        virtual float computeArea () const;
        virtual float computePerimeter () const;
        virtual void draw (easygl* window) const;
        virtual bool pointInside (float x, float y) const;
     
};

#endif	/* POLYGON_H */


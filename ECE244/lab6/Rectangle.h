/* 
 * File:   Rectangle.h
 * Author: zhangf30
 *
 * Created on November 26, 2013, 1:15 PM
 */

#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

class Rectangle: public Shape 
{
    
    private:
        float width;
        float height;
    public:
        Rectangle (string _name, string _colour, float _xcen, float _ycen, float _width, float _height);
        
        virtual ~Rectangle();
        virtual void print () const;
        virtual void scale (float scaleFac);
        virtual float computeArea () const;
        virtual float computePerimeter () const;
        virtual void draw (easygl* window) const;
        virtual bool pointInside (float x, float y) const;
};


#endif	/* RECTANGLE_H */


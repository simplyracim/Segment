#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"

class Circle : public Shape {

public :
    Point center;
    double rayon;
    
    // from Point.h
    virtual void dessiner() = 0;
    virtual void perimetre() = 0;
    virtual void aire() = 0;
};

#endif // CIRCLE_H
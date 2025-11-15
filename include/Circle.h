#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"

class Circle : public Shape {

public :
    Point center;
    double rayon;
    
    // from Point.h
    void dessiner() override;
    void perimetre() override;
    void aire() override;
};

#endif // CIRCLE_H
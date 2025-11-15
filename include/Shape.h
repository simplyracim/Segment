#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public :
        virtual void dessiner() = 0;
        virtual void perimetre() = 0;
        virtual void aire() = 0;
};

#endif // SHAPE_H
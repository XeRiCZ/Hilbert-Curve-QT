#include <math.h>
#ifndef VECTOR2_H
#define VECTOR2_H

// Třída reprezentující dvou dimenzionální bod na plátně
// (x,y)

class Vector2
{
public:
    float x,y;
    Vector2(){ x = 0; y = 0;}
    Vector2 (float _x,float _y)  : x(_x),y(_y) {}
    Vector2 normalize(Vector2 input);

    // Operátory pro aritmetické operace mezi 2D vektory
    Vector2 operator-(Vector2 input);
    Vector2 operator*(float input);
    Vector2 operator+(Vector2 input);
    Vector2 operator/(float input);
};


#endif // VECTOR2_H

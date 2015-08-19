#include "Vector2.h"
#include <QDebug>
/*
Vector2::Vector2(float _x,float _y) : x(_x),y(_y)
{

}*/

Vector2 Vector2::normalize(Vector2 input){
    // Normalizace dvojdimenzionalniho vektoru
    // Potřebné pro určení směru k dalšímu vektoru
  //  qDebug() << "normalizating : (" << input.x << ";" << input.y << ")";
     float magnitude =abs(sqrt((input.x * input.x) + (input.y * input.y)));


     return Vector2 (input.x / magnitude,input.y / magnitude);
}

Vector2 Vector2::operator+(Vector2 input)
{
    // Součet vektorů
    Vector2 output = Vector2(x,y);
    output.x += input.x;
    output.y += input.y;
    return output;
}

Vector2 Vector2::operator-(Vector2 input)
{
    // Rozdíl vektorů
    Vector2 output = Vector2(x,y);
    output.x -= input.x;
    output.y -= input.y;
    return output;
}

Vector2 Vector2::operator*(float input)
{
    // Násobení vektoru skalarem
    Vector2 output = Vector2(x,y);
    output.x *= input * 1.0;
    output.y *= input * 1.0;;
    return output;
}

Vector2 Vector2::operator/(float input)
{
    // Dělení vektoru skalarem
    Vector2 output = Vector2(x,y);
    output.x /= input * 1.0;;
    output.y /= input * 1.0;;
    return output;
}

#include "Vec2.h"

//return angle of x,y 
double Vec2::getAngle(double x, double y)
{
    double ret = atan2(y, x);
    ret = ToDegrees(ret);
    return ret;
}

//return x,y between 0 and 1 with determined angle
void Vec2::forward(float angle)
{
    angle = ToRadians(angle);
    this->x = cos(angle);
    this->y = sin(angle);
}

//https://www.youtube.com/watch?v=_vQxRRqbUHY
Vec2 Vec2::rotate(Vec2 &origin, Vec2& pos,float angle)
{
    angle = ToRadians(angle);
    Vec2 rotated;
    Vec2 delta = pos - origin;

    rotated.x = delta.x * cos(angle) - delta.y * sin(angle);
    rotated.y = delta.x * sin(angle) + delta.y * cos(angle); 
    rotated += origin;
    return rotated;
}

//return  vector with lenght(hypotenuse) to 1
//normaly called unit vector
void Vec2::normalize()
{
    float lenght = this->lenght();
    x /= lenght;
    y /= lenght;
}

//cross product
float Vec2::cross(Vec2 arg)
{
    return x * arg.y - y * arg.x;
}

//dot product
float Vec2::dot(Vec2 arg)
{
    return x * arg.x + y * arg.y;
}

//Calculate hypotenuse of a triangle
float Vec2::lenght()
{
    return sqrtf(x * x + y * y);
}

float Vec2::distance(Vec2 a, Vec2 b)//Distancia fica no DeltaZ
{
    Vec2 Delta = a - b;
    return  Delta.lenght();
}
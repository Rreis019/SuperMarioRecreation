#pragma once
#include <math.h>

#define PI 3.14159265
#define ToRadians(angle) angle * PI / 180
#define ToDegrees(angle) angle * 180 / PI

class Vec2
{
public:
	float x, y;
	Vec2() : x(-1), y(-1) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2 operator+(Vec2 arg) { Vec2 result; result.x = x + arg.x; result.y = y + arg.y; return result; }
	Vec2& operator+= (Vec2 arg) { x += arg.x; y += arg.y; return *this; }
	Vec2 operator-(Vec2 arg) { Vec2 result; result.x = x - arg.x; result.y = y - arg.y; return result; }
	Vec2& operator-=(Vec2 arg) { x -= arg.x; y -= arg.y; return *this; }
	Vec2 operator*(int arg) { Vec2 result; result.x = x * arg; result.y = y * arg; return result; }
	Vec2 operator*(float arg) { Vec2 result; result.x = x * arg; result.y = y * arg; return result; }
	Vec2 operator/(float arg) { Vec2 result; result.x = x / arg; result.y = y / arg; return result; }
	Vec2& operator*=(int arg) { x *= arg; y *= arg; return *this; }
    static double getAngle(double x, double y);
    void forward(float angle);
	static Vec2 rotate(Vec2 &origin, Vec2& pos,float angle);
	void normalize();
	float cross(Vec2 arg);
	float dot(Vec2 arg);
	float lenght();
	static float distance(Vec2 a, Vec2 b);
};
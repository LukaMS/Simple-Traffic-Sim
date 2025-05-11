#ifndef POINT_H
#define POINT_H

struct Point
{
    double x, y;

    Point() : x(0), y(0) {}
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}
};

#endif
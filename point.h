#ifndef POINT_H
#define POINT_H

#include <iostream>

template <class T>
class Point
{
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    Point(const Point &point) : x(point.x), y(point.y) {}

public:
    // turn vector on 90 degrees
    void turnOn90deg()
    {
        T item = this->x;
        this->x = this->y;
        this->y = -item;
    }
    //

    // override operators
    bool operator!=(const Point &point) const
    {
        if (this->x != point.x || this->y != point.y)
            return true;
        return false;
    }
    bool operator==(const Point &point) const
    {
        if (this->x == point.x && this->y == point.y)
            return true;
        return false;
    }

    Point operator+(const Point &point) const
    {
        return Point(this->x + point.x, this->y + point.y);
    }
    Point &operator+=(const Point &point)
    {
        this->x += point.x;
        this->y += point.y;
        return *this;
    }

    Point operator-(const Point &point) const
    {
        return Point(this->x - point.x, this->y - point.y);
    }
    Point &operator-=(const Point &point)
    {
        this->x -= point.x;
        this->y -= point.y;
        return *this;
    }
    //

    // only for debug
    void print()
    {
        std::cout << "x: " << this->x << " y: " << this->y << std::endl;
    }
    //

public:
    T x;
    T y;
};

#endif // POINT_H

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "size.h"
#include "point.h"

class Rectangle {
public:
	Rectangle(Point p = Point::zero(), Size s = Size::zero()) : point(p), size(s) {};
	~Rectangle() = default;

	Point point;
	Size size;
};

#endif

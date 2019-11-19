#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "size.h"
#include "point.h"

class Rectangle {
public:
	Rectangle();
	~Rectangle();
	
	Size size;
	Point point;
};

#endif

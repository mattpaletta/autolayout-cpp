#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
	Point(double _x, double _y) : x(_x), y(_y) {};

	static Point zero() {
		return Point(0, 0);
	};
	double x;
	double y;
};

#endif

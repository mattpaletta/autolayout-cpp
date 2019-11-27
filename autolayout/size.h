#ifndef SIZE_HPP
#define SIZE_HPP
class Size {
public:
	Size(double w, double h) : width(w), height(h) {};
	static Size zero() {
		return Size(0, 0);
	}
	double width;
	double height;
};
#endif

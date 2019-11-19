#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "point.h"

class View;

class Constraint {
public:
	Constraint();

	View* view;
	double constant;
private:
	enum ConstraintType {
		widthAnchor,
		heightAnchor,
		leadingAnchor,
		trailingAnchor,
		bottomAnchor,
		topAnchor,
		centerXAnchor,
		centerYAnchor
	};

	ConstraintType type;
};

#endif

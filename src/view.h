#ifndef VIEW_HPP
#define VIEW_HPP

#include <list>

#include "rectangle.h"
#include "constraint.h"

class View {
public:
	View(Rectangle frame);
	void add_subview(View* view);
	void add_constraint(const Constraint&& constraint);
	void add_constraints(std::list<Constraint>& constraint);
	void layout_subviews();

	Rectangle frame;
private:
	std::list<View*> subviews;
	std::list<Constraint> constraints;
};

#endif

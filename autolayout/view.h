#ifndef VIEW_HPP
#define VIEW_HPP

#include <list>

#include "rectangle.h"
#include "constraint.h"

class View {
public:
	View(Rectangle frame);

	// A view is not copyable or movable.
	View(const View&) = delete;
	View& operator=(const View&) = delete;
	View(View&&) = delete;
	View& operator=(View&&) = delete;

	void add_subview(View* view);
	void add_constraint(const Constraint&& constraint);
	void add_constraints(const std::list<Constraint>&& constraint);
	void layout_subviews();

	Rectangle frame;
private:
	View* super = nullptr;
	std::list<View*> subviews;
	std::list<Constraint> constraints;

	Constraint determine_constraint(const Constraint::ConstraintType& type);
	void layout_constraint(const Constraint& constraint);
};

#endif

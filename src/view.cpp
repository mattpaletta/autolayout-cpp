#include "view.h"
#include <list>

View::View(Rectangle frame) : subviews() {
	this->frame = frame;
}

void View::add_subview(View* view) {
	this->subviews.push_front(view);
	this->layout_subviews();
}

void View::add_constraint(const Constraint&& constraint) {
	this->constraints.push_front(constraint);
}

void View::add_constraints(std::list<Constraint>& constraint) {
	for (auto constr : constraint) {
		this->add_constraint(std::move(constr));
	}
}

void View::layout_subviews() {

}

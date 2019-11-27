#include "view.h"
#include <list>
#include <string>
#include <iostream>

View::View(Rectangle frame) : subviews() {
	this->frame = frame;
}

void View::add_subview(View* view) {
	view->super = this;
	this->subviews.push_front(view);
	this->layout_subviews();
}

void View::add_constraint(const Constraint&& constraint) {
	this->constraints.emplace_front(std::move(constraint));
}

void View::add_constraints(const std::list<Constraint>&& constraint) {
	for (const auto& constr : constraint) {
		this->add_constraint(std::move(constr));
	}
}

Constraint View::determine_constraint(const Constraint::ConstraintType& constraint) {
	std::list<const Constraint*> constr_type;
	for (const auto& constr : this->constraints) {
		if (constr.type == constraint) {
			constr_type.push_front(&constr);
		}
	}

	if (constr_type.size() == 0) {
		return Constraint::undetermined();
	}

	if (constr_type.size() > 1) {
		return Constraint::undetermined();
	} else {
		const Constraint* c = constr_type.front();
		this->layout_constraint(*c);
		return std::move(*c);
	}
}

void View::layout_constraint(const Constraint& constraint) {
	if (constraint.is_constant()) {
		if (constraint.type == Constraint::ConstraintType::widthAnchor) {
			this->frame.size.width = constraint.constant;
		} else if (constraint.type == Constraint::ConstraintType::heightAnchor) {
			this->frame.size.height = constraint.constant;
		} else if (constraint.type == Constraint::ConstraintType::leadingAnchor) {
			this->frame.point.x = constraint.constant + this->super->frame.point.x;
		} else if (constraint.type == Constraint::ConstraintType::topAnchor) {
			this->frame.point.y = constraint.constant + this->super->frame.point.y;
		} else if (constraint.type == Constraint::ConstraintType::bottomAnchor) {
			this->frame.size.height = constraint.constant + this->super->frame.size.height;
		} else if (constraint.type == Constraint::ConstraintType::trailingAnchor) {
			this->frame.size.height = constraint.constant + this->super->frame.size.width;
		}
	} else {
		Constraint c = constraint.view->determine_constraint(constraint.type);

		if (c.type == Constraint::ConstraintType::widthAnchor) {
			this->frame.size.width = c.constant;
		} else if (c.type == Constraint::ConstraintType::heightAnchor) {
			this->frame.size.height = c.constant;
		} else if (constraint.type == Constraint::ConstraintType::leadingAnchor) {
			this->frame.point.x = constraint.constant + constraint.view->frame.point.x;
		} else if (constraint.type == Constraint::ConstraintType::topAnchor) {
			this->frame.point.y = constraint.constant + constraint.view->frame.point.y;
		} else if (constraint.type == Constraint::ConstraintType::bottomAnchor) {
			this->frame.size.height = constraint.constant + constraint.view->frame.size.height;
		} else if (constraint.type == Constraint::ConstraintType::trailingAnchor) {
			this->frame.size.width = constraint.constant + constraint.view->frame.size.width;
		}
	}
}

void View::layout_subviews() {
	for (const auto& constr : this->constraints) {
		this->layout_constraint(constr);
	}

	for (const auto& v : this->subviews) {
		v->layout_subviews();
	}
}

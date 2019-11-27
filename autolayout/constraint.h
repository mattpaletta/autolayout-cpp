#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "point.h"

class View;

class Constraint {
public:
	enum ConstraintType {
		widthAnchor,
		heightAnchor,
		leadingAnchor,
		trailingAnchor,
		bottomAnchor,
		topAnchor,
		centerXAnchor,
		centerYAnchor,
		undeterminedAnchor
	};

	Constraint();

	// A constraint is not copyable.
	Constraint(const Constraint&) = delete;
	Constraint& operator=(const Constraint&) = delete;

	Constraint(const Constraint&& other) : type(other.type), constant(other.constant) {
		this->view = std::move(other.view);
		/// this->constant = std::move(other.constant);
	}

	Constraint& operator=(Constraint&&) = delete;

	static Constraint undetermined() {
		return Constraint(ConstraintType::undeterminedAnchor, nullptr, 0);
	}

	static Constraint width(double constant) {
		return Constraint(ConstraintType::widthAnchor, nullptr, constant);
	}

	static Constraint width(View* view, double constant = 0) {
		return Constraint(ConstraintType::widthAnchor, view, constant);
	}

	static Constraint height(double constant) {
		return Constraint(ConstraintType::heightAnchor, nullptr, constant);
	}

	static Constraint height(View* view, double constant = 0) {
		return Constraint(ConstraintType::heightAnchor, view, constant);
	}

	static Constraint top(double constant) {
		return Constraint(ConstraintType::topAnchor, nullptr, constant);
	}

	static Constraint top(View* view, double constant = 0) {
		return Constraint(ConstraintType::topAnchor, view, constant);
	}

	static Constraint bottom(double constant) {
		return Constraint(ConstraintType::bottomAnchor, nullptr, constant);
	}

	static Constraint bottom(View* view, double constant = 0) {
		return Constraint(ConstraintType::bottomAnchor, view, constant);
	}

	static Constraint trailing(double constant) {
		return Constraint(ConstraintType::trailingAnchor, nullptr, constant);
	}

	static Constraint trailing(View* view, double constant = 0) {
		return Constraint(ConstraintType::trailingAnchor, view, constant);
	}

	static Constraint leading(double constant) {
		return Constraint(ConstraintType::leadingAnchor, nullptr, constant);
	}

	static Constraint leading(View* view, double constant = 0) {
		return Constraint(ConstraintType::leadingAnchor, view, constant);
	}

	bool is_constant() const {
		return this->view == nullptr;
	}

	const ConstraintType type;
	View* view;
	const double constant;

private:
	Constraint(ConstraintType _type, View* _view, double _constant) : type(_type), view(_view), constant(_constant) {};

};

#endif

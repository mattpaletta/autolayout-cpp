#include <cassert>
#include <complex>
#include <string>
#include <iostream>
#include <chrono>
#include <future>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../autolayout/view.h"
#include "../autolayout/rectangle.h"
#include "../autolayout/point.h"
#include "../autolayout/size.h"

TEST_CASE("store", "autolayout") {
	const Rectangle rect(Point::zero(), Size(100, 200));
	const View v(rect);
	CHECK(v.frame.point.x == 0);
	CHECK(v.frame.point.y == 0);
	CHECK(v.frame.size.width == 100);
	CHECK(v.frame.size.height == 200);
}

TEST_CASE("constants_single", "autolayout") {
	// Every constraint is a constant
	View v(Rectangle(Point::zero(), Size(50, 50)));
	v.add_constraint(Constraint::width(100));
	v.add_constraint(Constraint::height(200));
	v.layout_subviews();
	CHECK(v.frame.point.x == 0);
	CHECK(v.frame.point.y == 0);
	CHECK(v.frame.size.width == 100);
	CHECK(v.frame.size.height == 200);
}

TEST_CASE("constants_children", "autolayout") {
	// Every constraint is a constant
	View a(Rectangle(Point::zero(), Size(50, 50)));
	View b(Rectangle(Point::zero(), Size(50, 50)));

	a.add_constraint(Constraint::width(100));
	a.add_constraint(Constraint::height(200));

	a.add_subview(&b);

	b.add_constraint(Constraint::width(80));
	b.add_constraint(Constraint::height(75));

	a.layout_subviews();

	CHECK(a.frame.point.x == 0);
	CHECK(a.frame.point.y == 0);
	CHECK(a.frame.size.width == 100);
	CHECK(a.frame.size.height == 200);

	CHECK(b.frame.point.x == 0);
	CHECK(b.frame.point.y == 0);
	CHECK(b.frame.size.width == 80);
	CHECK(b.frame.size.height == 75);
}

/*
TEST_CASE("conflicting_constants", "autolayout") {
	// Every constraint is a constant
	View v(Rectangle(Point::zero(), Size(50, 50)));
	v.add_constraint(Constraint::width(100));
	v.add_constraint(Constraint::width(200));
	v.add_constraint(Constraint::height(200));
	// TODO: This should throw an exception
	v.layout_subviews();
	CHECK(v.frame.point.x == 0);
	CHECK(v.frame.point.y == 0);
	CHECK(v.frame.size.height == 200);
}
*/

TEST_CASE("resize_to_match_parent", "autolayout") {
	// Child gets bigger to match parent
	View a(Rectangle(Point::zero(), Size(50, 50)));
	View b(Rectangle(Point::zero(), Size(50, 50)));

	a.add_constraint(Constraint::width(100));
	a.add_constraint(Constraint::height(200));

	a.add_subview(&b);

	b.add_constraint(Constraint::width(&a));
	b.add_constraint(Constraint::height(&a));

	a.layout_subviews();

	CHECK(a.frame.point.x == 0);
	CHECK(a.frame.point.y == 0);
	CHECK(a.frame.size.width == 100);
	CHECK(a.frame.size.height == 200);

	CHECK(b.frame.point.x == 0);
	CHECK(b.frame.point.y == 0);
	CHECK(b.frame.size.width == 100);
	CHECK(b.frame.size.height == 200);
}

TEST_CASE("resize_from_child", "autolayout") {
	// The parent resizes based on the size of the child
	View a(Rectangle(Point::zero(), Size(50, 50)));
	View b(Rectangle(Point::zero(), Size(50, 50)));

	a.add_constraint(Constraint::width(&b));
	a.add_constraint(Constraint::height(&b));

	a.add_subview(&b);

	b.add_constraint(Constraint::width(100));
	b.add_constraint(Constraint::height(200));

	a.layout_subviews();

	CHECK(a.frame.point.x == 0);
	CHECK(a.frame.point.y == 0);
	CHECK(a.frame.size.width == 100);
	CHECK(a.frame.size.height == 200);

	CHECK(b.frame.point.x == 0);
	CHECK(b.frame.point.y == 0);
	CHECK(b.frame.size.width == 100);
	CHECK(b.frame.size.height == 200);
}

/*
TEST_CASE("child_with_offset", "autolayout") {
	View a(Rectangle(Point::zero(), Size(50, 50)));

	View b(Rectangle(Point::zero(), Size(10, 10)));
	View c(Rectangle(Point::zero(), Size(10, 10)));

	a.add_constraint(Constraint::width(100));
	a.add_constraint(Constraint::height(230));

	a.add_subview(&b);
	a.add_subview(&c);

	b.add_constraint(Constraint::width(&a));
	b.add_constraint(Constraint::height(100));
	b.add_constraint(Constraint::top(&a, 10));

	c.add_constraint(Constraint::width(&a));
	c.add_constraint(Constraint::height(&b));
	c.add_constraint(Constraint::top(&b));
	c.add_constraint(Constraint::bottom(&b, 10));

	a.layout_subviews();

	CHECK(a.frame.point.x == 0);
	CHECK(a.frame.point.y == 0);
	CHECK(a.frame.size.width == 100);
	CHECK(a.frame.size.height == 230);


	CHECK(b.frame.point.x == 0);
	CHECK(b.frame.point.y == 10);
	CHECK(b.frame.size.width == 100);
	CHECK(b.frame.size.height == 100);

	CHECK(c.frame.point.x == 0);
	CHECK(c.frame.point.y == 10 + 100 + 10);
	CHECK(c.frame.size.width == 100);
	CHECK(c.frame.size.height == 100);
}

TEST_CASE("multiple_children", "autolayout") {
	// Children have the same height and width, resize the parent to match.
}
*/

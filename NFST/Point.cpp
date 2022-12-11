
#include "Point.h"
#include <iostream>


Point::Point()
{
}

Point::Point(double x, double y) : d_x{x},d_y{y}
{
}


Point::~Point()
{
}

double Point::x() const
{
	return d_x;
}

double Point::y() const
{
	return d_y;
}

void Point::afficher() const
{
	std::cout << '(' << d_x << ',' << d_y <<')'<<std::endl;
}

Point & Point::operator=(const Point & P)
{
	d_x = P.d_x;
	d_y = P.d_y;
	return *this;
}

Point operator+(const Point & P1, const Point & P2)
{
	return Point(P1.d_x+P2.d_x, P1.d_y + P2.d_y);
}

Point operator/(const Point & P1, int k)
{
	return Point(P1.d_x/k,P1.d_y/k);
}

Point operator*(const Point & P1, int k)
{
	return Point(P1.d_x * k, P1.d_y * k);
}



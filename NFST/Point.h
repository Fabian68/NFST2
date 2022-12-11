#pragma once
class Point
{
	friend Point operator+(const Point & P1, const Point & P2);
	friend Point operator/(const Point & P1, int k);
	friend Point operator*(const Point & P1, int k);
public:
	Point();
	Point(double x, double y);
	~Point();
	double x()const;
	double y()const;
	void afficher()const;
	Point &operator=(const Point & P);


private:
	double d_x, d_y;

};



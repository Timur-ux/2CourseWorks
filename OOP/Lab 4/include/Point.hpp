#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using decart = std::pair<double, double>;
const double EPS = 0.001;

class Point {
private:
	double x;
	double y;
public:
	Point() : x(0), y(0) {};
	Point(double _x, double _y) : x(_x), y(_y) {};
	Point(const decart cordinate);
	Point(const Point & other);
	Point(Point && other) noexcept;

	~Point() = default;

	decart getDecart() const;
	double getX() const;
	double getY() const;
	double getDistance(const Point & other) const;

	Point operator+(const Point & rhs) const;
	Point operator-(const Point & rhs) const;

	Point & operator=(const Point & rhs);
	Point & operator=(Point && rhs);

	bool operator==(const Point & rhs) const;

	friend Point operator*(int k, const Point & point);
	friend Point operator*(const Point & point, int k);
	friend Point operator/(const Point & point, int k);
	friend Point abs(const Point & point);

	friend std::istream & operator>>(std::istream & is, Point & point);
};

bool cmpX(const Point & lhs, const Point & rhs);
bool cmpY(const Point & lhs, const Point & rhs);

Point operator*(int k, const Point & point);
Point operator*(const Point & point, int k);
Point operator/(const Point & point, int k);
Point abs(const Point & point);

std::ostream & operator<<(std::ostream & os, const Point & point);
std::istream & operator>>(std::istream & is, Point & point);

std::vector<Point> unificatePoints(std::vector<Point> points);



#pragma once
#include <iostream>

struct Point {
	double x;
	double y;
	Point(double x1, double y1) : x(x1), y(y1) {}
	Point() : x(0.0), y(0.0) {}
};

bool operator<(Point a, Point b) {
	double det = a.x * b.y - b.x * a.y;
	return (det > 0 || ((det == 0) && ((a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y))));
}

bool operator<=(Point a, Point b) {
	double det = a.x * b.y - b.x * a.y;
	return (det > 0 || ((det == 0) && ((a.x * a.x + a.y * a.y) <= (b.x * b.x + b.y * b.y))));
}

bool operator==(Point a, Point b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(Point a, Point b) {
	return !(a == b);
}

bool operator>(Point a, Point b) {
	return !(a <= b);
}

ostream& operator<<(ostream& os, Point a) {
	os << a.x << ' ' << a.y << ' ';
	return os;
}

Point operator-(Point a, Point b) {
	return Point{ a.x - b.x, a.y - b.y };
}

Point operator+(Point a, Point b) {
	return Point{ a.x + b.x, a.y + b.y };
}

int det(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}
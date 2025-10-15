#pragma once
#include <cmath>

struct Vector {
	double x, y;

	Vector() {
		x = 0;
		y = 0;
	}
	Vector(double X, double Y) {
		x = X;
		y = Y;
	}

	double mag() {
		return sqrt(x * x + y * y);
	}
	Vector getUnit() {
		return (*this) * (1 / this->mag());
	}

	Vector operator*(double scalar);
	Vector operator+(Vector v2);
	Vector operator-(Vector v2);

	void operator+=(Vector v2);
};

Vector Vector::operator*(double scalar) {

	return Vector(x * scalar, y * scalar);

}
Vector Vector::operator+(Vector v2) {

	return Vector(x + v2.x, y + v2.y);

}
Vector Vector::operator-(Vector v2) {

	return Vector(x - v2.x, y - v2.y);

}

void Vector::operator+=(Vector v2) {

	x += v2.x;
	y += v2.y;

}
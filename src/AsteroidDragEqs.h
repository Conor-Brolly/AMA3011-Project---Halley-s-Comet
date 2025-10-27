#pragma once
#include "Vectors.h"

#define G 6.6743e-11
//Mass of the sun
#define M 1.989e30

#define minAstRadius 4.0e11
#define maxAstRadius 6.0e11
#define dragC 4.0e-14

//Equation of motion: (d/dt)^2 of x = -GMr / |r|^3 + drag term
//Conditional Drag term: -kv*|v|

namespace AsteroidDrag {

	Vector dxdt(Vector x, Vector v) {

		return v;

	}
	Vector dvdt(Vector x, Vector v) {

		Vector dvdt = x * (-G * M / pow(x.mag(), 3));


		if (minAstRadius < x.mag() && maxAstRadius > x.mag()) {
			//Adds a drag term if the comet is inside the asteroid belt
			dvdt += v * (-v.mag() * dragC);
		}
		return dvdt;

	}

}
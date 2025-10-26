#pragma once
#include "Vectors.h"

#define G 6.6743e-11
//Mass of the sun
#define M 1.989e30

//Equation of motion: (d/dt)^2 of x = -GMr / |r|^3

namespace CentralField {

	Vector dxdt(Vector x, Vector v) {

		return v;

	}
	Vector dvdt(Vector x, Vector v) {

		Vector dvdt = x * (-G * M / pow(x.mag(), 3));

		return dvdt;

	}

}
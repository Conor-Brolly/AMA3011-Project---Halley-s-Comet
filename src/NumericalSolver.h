#pragma once
#include "Vectors.h"

#define G 6.6e-11
#define DRAG_COEFF 4.0e-14

struct Particle {
	Vector pos;
	Vector vel;
};

//Solver for this project considers the interaction between two particles
class Solver {
public:
	//Given two first order differential equations for position and velocity with
	// respect to time, along with a timestep, a position and a velocity
	virtual void update(double dt, Particle* Comet,
						Vector (*dxdt)(Vector x, Vector v),
						Vector(*dvdt)(Vector x, Vector v)) {};
};
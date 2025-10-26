#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

class EulerSolver : public Solver {
public:

	EulerSolver() {};

	void update(double dt, Particle* Comet,
				Vector(*dxdt)(Vector x, Vector v),
				Vector(*dvdt)(Vector x, Vector v)) override {
		

		//Euler integrating differential equations
		Comet->pos += dxdt(Comet->pos, Comet->vel) * dt;
		Comet->vel += dvdt(Comet->pos, Comet->vel) * dt;
	}

};


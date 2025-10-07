#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

#define G 6.6e-11

class EulerSolver : public Solver {
public:

	EulerSolver() {};

	void update(Particle* Sun, Particle*Comet, double dt) override {
		
		//Vector between particles (from comet to sun)
		double xDist = Sun->x - Comet->x;
		double yDist = Sun->y - Comet->y;

		double r = sqrt(pow(xDist, 2) + pow(yDist, 2));

		//Acceleration magnitude + components
		double Acc = G * Sun->mass / (r * r);

		double xAcc = Acc * xDist / r;
		double yAcc = Acc * yDist / r;

		//Applying force
		Comet->Vx += dt * xAcc;
		Comet->Vy += dt * yAcc;

		//Updating position
		Comet->x += Comet->Vx * dt;
		Comet->y += Comet->Vy * dt;
	}
};


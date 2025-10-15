#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

#define G 6.6e-11

class EulerSolver : public Solver {
public:

	EulerSolver() {};

	void update(Particle* Sun, Particle*Comet, double dt) override {
		
		Vector acc = getAcceleration(Sun, Comet);

		//Applying force
		Comet->vel += acc * dt;
		//Updating position
		Comet->pos += Comet->vel * dt;
	}

	void updateAsteroid(Particle* Sun, Particle* Comet, double minR, double maxR, double dt) override {

		Vector acc = getAccelerationAsteroidField(Sun, Comet, minR, maxR);

		//Applying force
		Comet->vel += acc * dt;
		//Updating position
		Comet->pos += Comet->vel * dt;
	}
};


#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

#define G 1

class EulerSolver : public Solver {
public:

	EulerSolver() {};

	void update(Particle* p1, Particle*p2, double dt) override {
		
		//Vector between particles (from p2 to p1)
		double xDist = p1->x - p2->x;
		double yDist = p1->y - p2->y;

		double r = pow(xDist, 2) + pow(yDist, 2);
		double theta = atan2(yDist, xDist);

		//Force magnitude + components
		double Force = (G * p1->mass * p2->mass) / (r * r);

		double xForce = Force * cos(theta);
		double yForce = Force * sin(theta);

		//Applying forces
		//p1
		if (!p1->fixed) {
			p1->Vx += -dt * xForce / p1->mass;
			p1->Vy += -dt * yForce / p1->mass;
		}

		//p2
		if (!p2->fixed) {
			p2->Vx += dt * xForce / p2->mass;
			p2->Vy += dt * yForce / p2->mass;
		}

		//Updating positions
		p1->x += p1->Vx * dt;
		p1->y += p1->Vy * dt;

		p2->x += p2->Vx * dt;
		p2->y += p2->Vy * dt;

	}
};


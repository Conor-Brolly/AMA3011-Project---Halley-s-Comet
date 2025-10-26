#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

class RKSolver : public Solver {
public:

	RKSolver() {};

	void update(double dt, Particle* Comet,
				Vector(*dxdt)(Vector x, Vector v),
				Vector(*dvdt)(Vector x, Vector v)) override {

		//RUNGE KUTTA METHODS

		//First term (k1)
		Vector kx1 = dxdt(Comet->pos, Comet->vel);
		Vector kv1 = dvdt(Comet->pos, Comet->vel);

		//Second term (k2)
		Vector kx2 = dxdt(Comet->pos + kx1 * (dt/2), Comet->vel + kv1 * (dt/2));
		Vector kv2 = dvdt(Comet->pos + kx1 * (dt / 2), Comet->vel + kv1 * (dt / 2));

		//Third term (k3)
		Vector kx3 = dxdt(Comet->pos + kx2 * (dt / 2), Comet->vel + kv2 * (dt / 2));
		Vector kv3 = dvdt(Comet->pos + kx2 * (dt / 2), Comet->vel + kv2 * (dt / 2));

		//Fourth term (k4)
		Vector kx4 = dxdt(Comet->pos + kx3 * dt, Comet->vel + kv3 * dt);
		Vector kv4 = dvdt(Comet->pos + kx3 * dt, Comet->vel + kv3 * dt);


		//Integrating differential equations
		Comet->pos += (kx1 + kx2 * 2 + kx3 * 2 + kx4) * (dt / 6);
		Comet->vel += (kv1 + kv2 * 2 + kv3 * 2 + kv4) * (dt / 6);

	}
};
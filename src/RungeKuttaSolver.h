#pragma once
#include <cmath>
#include "NumericalSolver.h"
#include <iostream>

class RKSolver : public Solver {
public:

	RKSolver() {};

	void update(Particle* Sun, Particle* Comet, double dt) override {
		//Work out 4 forces (4th order)

		//==================================Force k1 (using acc, as masses cancel)==========
		Vector rk1Acc = getAcceleration(Sun, Comet);
		
		//=====================================Force k2===================================
		//Calculates position based on k1
		//Applying force
		Particle RKComet = *Comet;
		
		RKComet.vel += rk1Acc * dt * 0.5;
		//Updating position
		RKComet.pos += RKComet.vel * dt * 0.5;

		Vector rk2Acc = getAcceleration(Sun, &RKComet);
		
		//====================================Force k3======================================
		//Recalculates position given the k2 acceleration
		RKComet = *Comet;

		//Applying force
		RKComet.vel += rk2Acc * dt * 0.5;
		//Updating position
		RKComet.pos += RKComet.vel * dt * 0.5;
		
		Vector rk3Acc = getAcceleration(Sun, &RKComet);

		//=====================================Force k4======================================
		//Recalculates position given the k3 acceleration
		RKComet = *Comet;
		//Applying force
		RKComet.vel += rk3Acc * dt;
		//Updating position
		RKComet.pos += RKComet.vel * dt;

		Vector rk4Acc = getAcceleration(Sun, &RKComet);

		//==============================Applying Acceleration============================
		//Applying force
		Comet->vel += (rk1Acc + rk2Acc * 2 + rk3Acc * 2 + rk4Acc) * (dt / 6.0);
		//Updating position
		Comet->pos += Comet->vel * dt;
	}

	void updateAsteroid(Particle* Sun, Particle* Comet, double minR, double maxR, double dt) override {
		//Work out 4 forces (4th order)

		//==================================Force k1 (using acc, as masses cancel)==========
		Vector rk1Acc = getAccelerationAsteroidField(Sun, Comet, minR, maxR);

		//=====================================Force k2===================================
		//Calculates position based on k1
		//Applying force
		Particle RKComet = *Comet;

		RKComet.vel += rk1Acc * dt * 0.5;
		//Updating position
		RKComet.pos += RKComet.vel * dt * 0.5;

		Vector rk2Acc = getAccelerationAsteroidField(Sun, &RKComet, minR, maxR);

		//====================================Force k3======================================
		//Recalculates position given the k2 acceleration
		RKComet = *Comet;

		//Applying force
		RKComet.vel += rk2Acc * dt * 0.5;
		//Updating position
		RKComet.pos += RKComet.vel * dt * 0.5;

		Vector rk3Acc = getAccelerationAsteroidField(Sun, &RKComet, minR, maxR);

		//=====================================Force k4======================================
		//Recalculates position given the k3 acceleration
		RKComet = *Comet;
		//Applying force
		RKComet.vel += rk3Acc * dt;
		//Updating position
		RKComet.pos += RKComet.vel * dt;

		Vector rk4Acc = getAccelerationAsteroidField(Sun, &RKComet, minR, maxR);

		//==============================Applying Acceleration============================
		//Applying force
		Comet->vel += (rk1Acc + rk2Acc * 2 + rk3Acc * 2 + rk4Acc) * (dt / 6.0);
		//Updating position
		Comet->pos += Comet->vel * dt;
	}
};









//Go through every variable between rk2 and rk3 to find the issue. 
// rk2acc and rk3acc are the same, which shouldnt be the case. THis is a possible cause of error.
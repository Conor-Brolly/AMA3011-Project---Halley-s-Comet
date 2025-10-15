#pragma once
#include "Vectors.h"

#define G 6.6e-11
#define DRAG_COEFF 4.0e-14

struct Particle {
	double mass;
	Vector pos;
	Vector vel;
};

//Solver for this project considers the interaction between two particles
class Solver {
public:
	virtual void update(Particle* Sun, Particle* Comet, double dt) {};
	virtual void updateAsteroid(Particle* Sun, Particle* Comet, double minR, double maxR, double dt) {};
};

//Returns acceleration by gravity of comet given by its position
Vector getAcceleration(Particle* Sun, Particle* Comet) {

	Vector r = Sun->pos - Comet->pos;

	//Acceleration magnitude + components
	double AccMag = G * Sun->mass / (r.mag() * r.mag());

	Vector Acc = r.getUnit() * AccMag;

	return Acc;
}

Vector getAccelerationAsteroidField(Particle* Sun, Particle* Comet, double minR, double maxR) {

	Vector r = Sun->pos - Comet->pos;

	//Acceleration from gravity
	double AccMag = G * Sun->mass / (r.mag() * r.mag());
	Vector Acc = r.getUnit() * AccMag;

	//Acceleration (drag) from the asteroid field
	if (r.mag() > minR && r.mag() < maxR) {
		//Proportional to V squared
		Vector drag = Comet->vel * Comet->vel.mag() * (-DRAG_COEFF);
		Acc += drag;
	}

	return Acc;
}
#pragma once

struct Particle {
	double mass;
	double x, y;
	double Vx, Vy;
};

//Solver for this project considers the interaction between two particles
class Solver {
public:
	virtual void update(Particle* Sun, Particle* Comet, double dt) {};
};
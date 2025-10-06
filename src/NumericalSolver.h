#pragma once

struct Particle {
	bool fixed;
	double mass;
	double x, y;
	double Vx, Vy;
};

//Solver for this project considers the interaction between two particles
class Solver {
public:
	virtual void update(Particle* p1, Particle* p2, double dt) {};
};
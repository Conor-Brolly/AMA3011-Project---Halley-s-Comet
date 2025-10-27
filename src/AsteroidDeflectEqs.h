#pragma once
#include "Vectors.h"

#include <iostream>

#define G 6.6743e-11
//Mass of the sun
#define M 1.989e30

#define minAstRadius 4.0e11
#define maxAstRadius 6.0e11
//Arbitrary, chosen for a desired deflection
#define Masteroid 8.0e12

//Equation of motion: (d/dt)^2 of x = -GMr / |r|^3 + G Masteroid r / |r|^3
 
namespace AsteroidDeflect {

	Vector dxdt(Vector x, Vector v) {

		return v;

	}
	Vector dvdt(Vector x, Vector v) {

		//Tracks whether the asteroid was in the field previously
		static bool inFieldPreviously = false;
		//Stores randomly chosen displacement for each time
		static double displacement = 1.0;

		//Checks whether the asteroid is within the field
		bool inField = (minAstRadius < x.mag() && maxAstRadius > x.mag());
		
		//If the asteroid has just entered the field, generate a new displacement
		if (inField && (!inFieldPreviously)) {
			//Generates a random number between -1 and 1
			double randX = ((double)(rand() % 1000) / 500.0) - 1.0;
			
			//Excludes values close to zero - most variation of deflection will come from direction
			if (randX > -0.4 && randX <= 0.0) randX = -0.4;
			if (randX < 0.4 && randX > 0.0) randX = 0.4;
			displacement = randX * (maxAstRadius * 1.0e-8);
			std::cout << displacement << "\n";
		}
		inFieldPreviously = inField;

		
		//Apply Gravity from sun
		Vector dvdt = x * (-G * M / pow(x.mag(), 3));

		//Apply perpendicular force from asteroid
		if (inField) {
			//Perpendicular vector
			Vector displacementV = Vector(v.getUnit().y, -v.getUnit().x);
			displacementV = displacementV * displacement;

			//Force magnitude
			Vector acc = displacementV * (G * Masteroid / abs(pow(displacement, 3)));
			dvdt += acc;
			
		}
		return dvdt;

	}

}
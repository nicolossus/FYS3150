//=================================
// Include guard
#ifndef SOLVER_H
#define SOLVER_H

//=================================
// Included dependencies
#include <iostream>
#include <armadillo>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "planet.h"
using namespace std;
using namespace arma;

// Begin class
//=============================================================================
class Solver
//----------------------------------------------------------------------------
// Solve the motion of the solar system using Euler's and Verlet's method.
// Energies and angular momentum is also calculated.
//----------------------------------------------------------------------------
{
private:
	// Declaration of private variables
	//===========================================================================
	mat pos;                   // Position matrix
	mat vel;                   // Velocity matrix
	vector<Planet> planets;    // Vector of planet properties
	int numPlanets;            // Number of planets
	double G;                  // Gravitational constant
	double dt;                 // time step
	mat totalAcc;              // Total acceleration matrix
	mat prevAcc;               // Previous acceleration matrix
	mat prevVel;               // Previous velocity matrix

	// Private methods
	//===========================================================================
	// Calculate the total acceleration from the force between bodies
	void totalAcceleration(mat & totalAcc, vec acc(vec, vec));
	// Write coordinates to file
	void coordinatesToFile(ofstream &myfile);
	// Euler's method
	void euler(vec acc(vec,vec));
	// Verlet's method
	void verlet(vec acc(vec,vec));

	// Activators
	//===========================================================================
	// Method solve() called is true
	bool solved = false;
	// Method solvedEnergy() is true
	bool solvedEnergy = false;
	// Static sun is true
	bool staticSun = true;

public:
	// Declare public variables
	//===========================================================================
	mat kineticEnergy;
	mat potentialEnergy;
	vec energyAllPlanets;
	vec angularMomentum;

	// Constructor
	//===========================================================================
	Solver(vector<Planet> p, double G, bool staticSun);

	// Public methods
	//===========================================================================
	// Solve the system using either Euler's or Verlet's method
	void solve(int method, vec acc(vec, vec), double T, int N, int sampleN);

	// Calculate energy and angular momentum
	void sampleEnergyAndAngular(mat &kinetic, mat &potential, vec &angular,
	                            vec &energyAllPlanets, int i);
	// Find fluctuation of the kinetic energy of planet x
	double kineticFluctuation(int i);
	// Find fluctuation of the potential energy of planet x
	double potentialFluctuation(int i);
	// Find fluctuation of the total energy of planet x
	double totalEnergyFluctuation();
	// Find fluctuation of the angular momentum of planet x
	double angularFluctuation();
};
// End class

#endif // __SOLVER_H_INCLUDED__

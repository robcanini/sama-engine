#include "cyclone/particle.h"
#include <assert.h>

using namespace cyclone;

void Particle::integrate(real duration)
{
	assert(duration > 0);

	// Update linear position.
	position.addScaledVector(velocity, duration);

	// Work out the acceleratino from the force.
	Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);

	// Update lienar velocity from the acceleration.
	velocity.addScaledVector(resultingAcc, duration);

	// Impose drag.
	velocity *= real_pow(damping, duration);

	// Clear the forces.
	clearAccumulator();
}

void Particle::clearAccumulator()
{
	forceAccum.clear();
}

void Particle::addForce(const Vector3& force)
{
	forceAccum += force;
}

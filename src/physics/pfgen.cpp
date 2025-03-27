#include "physics/core.h"
#include "physics/pfgen.h"

namespace physics {

	void ParticleGravity::updateForce(Particle* particle, real duration)
	{
		// Check that we do not have infinite mass.
		if (!particle->hasFiniteMass()) return;

		// Apply the mass-scaled force to the particle.
		particle->addForce(gravity * particle->getMass());
	}

	void ParticleDrag::updateForce(Particle* particle, real duration)
	{
		/*
			fdrag = −̂ ˙p(k1|̂ ˙p| + k2|̂ ˙p|2)
		*/

		Vector3 force;
		particle->getVelocity(force);

		// Calculate the total drag coefficient.
		real dragCoeff = force.magnitude();
		dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

		// Calculate the final force and apply it.
		force.normalize();
		force *= -dragCoeff;
		particle->addForce(force);
	}
}
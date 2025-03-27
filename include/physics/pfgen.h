#pragma once

#include "physics/core.h"
#include "physics/particle.h"

namespace physics {

	/**
	 * A force generator can be asked to add a force to one or more
	 * particles.
	 */
	class ParticleForceGenerator
	{
	public:
		/**
		 * Overload this in implementations of the interface to calculate
		 * and update the force applied to the given particle.
		 */
		virtual void updateForce(Particle *particle, real duration) = 0;
	};

	/**
	 * A force generator that applies a gravitational force. One instance
	 * can be used for multiple particles.
	 */
	class ParticleGravity : public ParticleForceGenerator
	{
		/** Holds the acceleration due to gravity. */
		Vector3 gravity;

	public:
		/** Creates the generator with the given acceleration. */
		ParticleGravity(const Vector3& gravity) : gravity(gravity) {}

		/** Applies the gravitational force to the given particle. */
		virtual void updateForce(Particle* particle, real duration) override;
	};

	/**
	 * A force generator that applies a drag force. One instance
	 * can be used for multiple particles.
	 */
	class ParticleDrag : public ParticleForceGenerator
	{
		/** Holds the velocity drag coefficient. */
		real k1;

		/** Holds the velocity squared drag coefficient. */
		real k2;

	public:
		/** Creates the generator with the given coefficients. */
		ParticleDrag(real k1, real k2) : k1(k1), k2(k2) {}

		/** Applies the drag force to the given particle. */
		virtual void updateForce(Particle* particle, real duration) override;
	};
}
#pragma once

#include <vector>
#include "physics/precision.h"
#include "physics/particle.h"
#include "physics/pfgen.h"

namespace physics {

	/**
	 * Holds all the force generators and the particles they
	 */
	class ParticleForceRegistry
	{
	protected:

		/**
		 * Keeps track of one force generator and the particle it
		 * applies to.
		 */
		struct ParticleForceRegistration
		{
			Particle *particle;
			ParticleForceGenerator *fg;
		};

		/**
		 * Holds the list of registrations.
		 */
		typedef std::vector<ParticleForceRegistration> Registry;
		Registry registrations;
	
	public:
		/**
		 * Registers the given force generator to apply to the
		 * given particle.
		 */
		void add(Particle* particle, ParticleForceGenerator* fg);

		/**
		 * Removes the given registered pair from the registry.
		 * If the pair is not registered, this method will have
		 * no effect.
		 */
		void remove(Particle* particle, ParticleForceGenerator* fg);

		/**
		 * Clears all registration from the registry. This will
		 * not delete the particles or the force generators
		 * themselves, just of records of their connection.
		 */
		void clear();

		/**
		 * Calls all the force generators to update the forces of
		 * their corresponding particles.
		 */
		void updateForces(real duration);
	};
}
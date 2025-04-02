#pragma once

#include <vector>
#include "physics/precision.h"
#include "physics/core.h"
#include "physics/particle.h"
#include "physics/pfreg.h"
#include "physics/pcontacts.h"
#include "physics/pcommon.h"

namespace physics {

	/**
	 * Keeps track of a set of particles, and provides the means to
	 * update them all.
	 */
	class ParticleWorld
	{
	public:
		typedef std::vector<Particle*> Particles;
		typedef std::vector<ParticleContactGenerator*> ContactGenerators;

	protected:

		/**
		 * Holds the particles
		 */
		Particles particles;

		/** Holds the force generators for the particles in this world. */
		ParticleForceRegistry registry;

		/** Holds the resolver for contacts. */
		ParticleContactResolver resolver;

		/**
		 * Contact generators.
		 */
		ContactGenerators contactGenerators;

		/** Holds the list of contacts. */
		ParticleContact* contacts;

		/** 
		 * Holds the maximum number of contacts allowed (e.g.: the
		 * size of the contacts array).
		 */
		unsigned maxContacts;

		/**
		 * True if the world should calculate the number of iterations
		 * to give the contact resolver at each frame.
		 */
		bool calculateIterations;

	public:
		/**
		 * Creates a new particle simulator that can handle up to the
		 * given number of contacts per frame. You can also optionally
		 * give a number of contact-resolution iterations to use. If you
		 * don’t give a number of iterations, then twice the number of
		 * contacts will be used.
		 */
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0) : maxContacts(maxContacts), resolver(iterations)
		{
			calculateIterations = iterations == 0;
			contacts = new ParticleContact[maxContacts];
		}

		~ParticleWorld()
		{
			delete[] contacts;
		}

		/**
		 * Initializes the world for a simulation frame. This clears
		 * the force accumulators for particles in the world. After
		 * calling this, the particles can have their forces for this
		 * frame added.
		 */
		void startFrame();

		/**
		 * Calls each of the registered contact generators to report
		 * their contacts. Returns the number of generated contacts.
		 */
		unsigned generateContacts();

		/**
		 * Integrates all the particles in this world forward in time
		 * by the given duration.
		 */
		void integrate(real duration) const;

		/**
		 * Processes all the physics for the particle world.
		 */
		void runPhysics(real duration);

		/**
		 *  Returns the list of particles.
		 */
		Particles& getParticles();

		/**
		 * Returns the list of contact generators.
		 */
		ContactGenerators& getContactGenerators();

		/**
		 * Returns the force registry.
		 */
		ParticleForceRegistry& getForceRegistry();
	};

	class GroundContacts : public ParticleContactGenerator
	{
		ParticleWorld::Particles* particles;

	private:
		real restitution;

	public:
		GroundContacts(ParticleWorld::Particles* particles, real restitution = 0.2f) : particles(particles), restitution(restitution)
		{
		}

	public:

		virtual unsigned addContact(ParticleContact* contact, unsigned limit) const override;
	};
} // namespace physics
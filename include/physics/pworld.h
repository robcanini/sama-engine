#pragma once

#include "physics/precision.h"
#include "physics/core.h"
#include "physics/particle.h"
#include "physics/pfreg.h"
#include "physics/pcontacts.h"

namespace physics {

	/**
	 * Keeps track of a set of particles, and provides the means to
	 * update them all.
	 */
	class ParticleWorld
	{
	public:
		/**  Holds one particle in the linked list of particles. */
		struct ParticleRegistration
		{
			Particle* particle;
			ParticleRegistration* next;
		};

		/** Holds the list of registrations. */
		ParticleRegistration* firstParticle;

		/** Holds the force generators for the particles in this world. */
		ParticleForceRegistry registry;

		/** Holds the resolver for contacts. */
		ParticleContactResolver resolver;

		/** Holds one registered contact generator. */
		struct ContactGenRegistration
		{
			ParticleContactGenerator* gen;
			ContactGenRegistration* next;
		};

		/** Holds the list of contact generators. */
		ContactGenRegistration* firstContactGen;

		/** Holds the list of contacts. */
		ParticleContact* contacts;

		/** 
		 * Holds the maximum number of contacts allowed (e.g.: the
		 * size of the contacts array).
		 */
		unsigned maxContacts;

		unsigned iterations;

	public:
		/**
		 * Creates a new particle simulator that can handle up to the
		 * given number of contacts per frame. You can also optionally
		 * give a number of contact-resolution iterations to use. If you
		 * don’t give a number of iterations, then twice the number of
		 * contacts will be used.
		 */
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0) : maxContacts(maxContacts), iterations(iterations)
		{
			calculateIterations = iterations == 0;
		}

		~ParticleWorld()
		{
			ParticleRegistration* current = firstParticle;

			while (current)
			{
				ParticleRegistration* next = current->next;

				// Libera la particella associata
				delete current->particle;

				// Libera il nodo della linked list
				delete current;

				current = next;
			}

			firstParticle = nullptr;

			// (Opzionale) Se hai una linked list di ContactGenRegistration, liberala qui:
			ContactGenRegistration* currentGen = firstContactGen;

			while (currentGen)
			{
				ContactGenRegistration* nextGen = currentGen->next;

				delete currentGen->gen;   // Solo se tu sei il proprietario del generatore
				delete currentGen;

				currentGen = nextGen;
			}

			firstContactGen = nullptr;

			// (Opzionale) Se `contacts` è un array allocato con `new[]`, liberalo:
			delete[] contacts;
			contacts = nullptr;
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
		void integrate(float duration)
		{
			ParticleRegistration* reg = firstParticle;
			while (reg)
			{
				// Integrate the particle for the frame duration.
				reg->particle->integrate(static_cast<real>(duration));

				// Get the next registration.
				reg = reg->next;
			}
		}

		/**
		 * Processes all the physics for the particle world.
		 */
		void runPhysics(real duration);

	private:
		bool calculateIterations;
	};
}
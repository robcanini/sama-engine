#include <cstddef>
#include "physics/pworld.h"

namespace physics {

	void ParticleWorld::startFrame()
	{
		for (Particles::iterator p = particles.begin();
			p != particles.end();
			p++)
		{
			// Remove all forces from the accumulator
			(*p)->clearAccumulator();
		}
	}

	unsigned ParticleWorld::generateContacts()
	{
		unsigned limit = maxContacts;
		ParticleContact* nextContact = contacts;

		for (ContactGenerators::iterator g = contactGenerators.begin();
			g != contactGenerators.end();
			g++)
		{
			unsigned used = (*g)->addContact(nextContact, limit);
			limit -= used;
			nextContact += used;

			// We've run out of contacts to fill. This means we're missing
			// contacts.
			if (limit <= 0) break;
		}

		// Return the number of contacts used.
		return maxContacts - limit;
	}

	void ParticleWorld::integrate(real duration) const
	{
		for (Particles::const_iterator p = particles.begin();
			p != particles.end();
			p++)
		{
			// Remove all forces from the accumulator
			(*p)->integrate(duration);
		}
	}

	void ParticleWorld::runPhysics(real duration)
	{
		// First apply the force generators.
		registry.updateForces(duration);

		// Then integrate the objects.
		integrate(duration);

		// Generate contacts.
		unsigned usedContacts = generateContacts();
		
		// And process them.
		if (calculateIterations)
		{
			resolver.setIterations(usedContacts * 2);
		}
		resolver.resolveContacts(contacts, usedContacts, duration);
	}

	ParticleWorld::Particles& ParticleWorld::getParticles()
	{
		return particles;
	}

	ParticleWorld::ContactGenerators& ParticleWorld::getContactGenerators()
	{
		return contactGenerators;
	}

	ParticleForceRegistry& ParticleWorld::getForceRegistry()
	{
		return registry;
	}

	unsigned GroundContacts::addContact(ParticleContact* contact, unsigned limit) const
	{
		unsigned count = 0;
		for (ParticleWorld::Particles::iterator p = particles->begin();
			p != particles->end();
			p++)
		{
			real y = (*p)->getPosition().y;
			if (y <= groundY)
			{
				Vector3 groundNormal = Vector3::UP;
				Vector3 velocity = (*p)->getVelocity();
				real closingVelocity = velocity.scalarProduct(groundNormal);

				/** prevent infinite bouncing */
				real finalRestitution = restitution;
				if (std::abs(closingVelocity) < 1.0f)
				{
					finalRestitution = 0.0f;
				}

				contact->contactNormal = groundNormal;
				contact->particle[0] = *p;
				contact->particle[1] = NULL;
				contact->penetration = y - groundY;
				contact->restitution = finalRestitution;
				contact++;
				count++;
			}

			if (count >= limit) return count;
		}
		return count;
	}
} // namespace physics
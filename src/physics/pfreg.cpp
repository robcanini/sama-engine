#include "physics/pfreg.h"

namespace physics {

	void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
	{
		ParticleForceRegistration reg = { particle, fg };
		registrations.push_back(reg);
	}

	void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
	{
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++)
		{
			if (i->particle == particle && i->fg == fg)
			{
				registrations.erase(i);
				return;
			}
		}
	}

	void ParticleForceRegistry::clear()
	{
		registrations.clear();
	}

	void ParticleForceRegistry::updateForces(real duration)
	{
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++)
		{
			i->fg->updateForce(i->particle, duration);
		}
	}
}
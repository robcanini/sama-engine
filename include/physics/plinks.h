#pragma once

#include "physics/precision.h"
#include "physics/core.h"
#include "physics/particle.h"
#include "physics/pcontacts.h"

namespace physics {

	/**
	 * Links connect two particles together, generating a contact if
	 * they violate the constraints of their link. It is used as a
	 * base class for cables and rods, and could be used as a base
	 * class for springs with a limit to their extension.
	 */
	class ParticleLink
	{
	public:
		/** Holds the pair of particles that are connected by this link. */
		Particle* particle[2];


	protected:
		/** Returns the current length of the link. */
		real currentLength() const;

	public:
		/**
		 * Fills the given contact structure with the contact needed
		 * to keep the link from violating its constraint. The contact
		 * pointer should point to the first available contact in a
		 * contact array, where limit is the maximum number of
		 * contacts in the array that can be written to. The method
		 * returns the number of contacts that have been written. This
		 * format is common to contact-generating functions, but this
		 * class can only generate a single contact, so the
		 * pointer can be a pointer to a single element. The limit
		 * parameter is assumed to be at least one (zero isn’t valid),
		 * and the return value is either 0, if the cable wasn’t
		 * overextended, or one if a contact was needed.
		 */
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const = 0;
	};

	/**
	 * Cables link a pair of particles, generating a contact if they stray too far apart.
	 */
	class ParticleCable : public ParticleLink
	{
	public:
		/** Holds the maximum length of the cable. */
		real maxLength;

		/** Holds the restitution (bounciness) of the cable. */
		real restitution;

	public:
		/**
		 * Fills the given contact structure with the contact needed
		 * to keep the cable for overextending.
		 */
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const override;
	};

	/**
	 * Rods link a pair of particles, generating a contact if the
	 * stray too far apart or too close.
	 */
	class ParticleRod : public ParticleLink
	{
	public:
		/** Holds the length of the rod. */
		real length;

	public:
		/**
		 * Fills the given contact structure with the contact needed
		 * to keep the rod for extending or compressing.
		 */
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const override;
	};
}
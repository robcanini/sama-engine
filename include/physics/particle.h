#pragma once

#include <assert.h>
#include <physics/core.h>
#include <physics/precision.h>

namespace physics {

	/**
	 * A particle is the simplest object that can be simulated in the
	 * physics system.
	 */
	class Particle
	{
	public:
		/** Holds the linear position of the particle in the world space. */
		Vector3 position;

		/** Holds the linear velocity of the particle in the world space. */
		Vector3 velocity;

		/**
		 * Holds the acceleration of the particle. This value
		 * can be used to set acceleration due to gravity (its primary
		 * use) or any other constant acceleration.
		 */
		Vector3 acceleration;

		/**
		 * Holds the amount of damping applied to linear
		 * motion. Damping is required to remove energy added
		 * through numerical instability in the integrator.
		 */
		real damping;

		void setInverseMass(const real mass)
		{
			inverseMass = mass;
		}

		void setMass(const real mass)
		{
			assert(mass != 0);
			inverseMass = ((real)1.0) / mass;
		}

		real getMass() const
		{
			assert(inverseMass != 0);
			return ((real)1.0) / inverseMass;
		}

		real getInverseMass() const
		{
			return inverseMass;
		}

		void getVelocity(Vector3 &velocity) const
		{
			velocity = this->velocity;
		}

		Vector3 getVelocity() const
		{
			return velocity;
		}

		void setVelocity(Vector3 velocity)
		{
			this->velocity.x = velocity.x;
			this->velocity.y = velocity.y;
			this->velocity.z = velocity.z;
		}

		void setVelocity(real x, real y, real z)
		{
			velocity.x = x;
			velocity.y = y;
			velocity.z = z;
		}

		void setAcceleration(real x, real y, real z)
		{
			acceleration.x = x;
			acceleration.y = y;
			acceleration.z = z;
		}

		void setPosition(Vector3 position)
		{
			this->position.x = position.x;
			this->position.y = position.y;
			this->position.z = position.z;
		}

		void setPosition(real x, real y, real z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}

		Vector3 getPosition() const
		{
			return position;
		}

		void getPosition(Vector3 &position) const
		{
			position = this->position;
		}

		bool hasFiniteMass() const
		{
			return inverseMass > 0.0f;
		}

		/**
		 * Integrates the particle forward in time by the given amount.
		 * This function uses a Newton-Euler integration method, which is a
		 * linear approximation of the correct integral. For this reason it
		 * may be inaccurate in some cases.
		 */
		void integrate(real duration);

		/**
		 * Clears the forces applied to the particle.
		 * This will be called automatically after each integration step.
		 */
		void clearAccumulator();

		/**
		 * Adds the given force to the particle, to be applied at the next
		 * iteration only.
		 */
		void addForce(const Vector3 &force);

	protected:
		/**
		 * Holds the inverse of the mass of the particle. It
		 * is more useful to hold the inverse mass because
		 * integration is simpler and because in real-time
		 * simulation it is more useful to have objects with
		 * infinite mass (immovable) than zero mass
		 * (completely unstable in numerical simulation)
		 */
		real inverseMass;

		/**
		 * Holds the accumulated force to be applied at the next
		 * simulation iteration only. This value is zeroed at each
		 * integration step.
		 */
		Vector3 forceAccum;
	};
}
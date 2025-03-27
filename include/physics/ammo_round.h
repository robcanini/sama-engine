#pragma once

#include "physics/particle.h"
#include "core/frame_timer.h"

namespace physics {

	enum class ShotType
	{
		UNUSED = 0,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};

	/**
	 * This struct represents a single projectile
	 * in the balistic simulation system.
	 */
	struct AmmoRound
	{
		/** The particle object representing the projectile. */
		Particle particle;

		/** The type of the projectile to be spawned and fired. */
		ShotType type;

		/** Projectile creation timestamp. */
		unsigned startTime;

		/** Check if the projectile should be not rendered anymore at the current frame. */
		bool isNotValid(int maxAge, int zBound) const
		{
			return particle.position.y < 0.0f ||
				startTime + maxAge < core::FrameTimer::get()->lastFrameTimestamp ||
				particle.position.z > zBound;
		}
	};
}
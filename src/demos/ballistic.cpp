#include <iostream>
#include <thread>
#include "core/frame_timer.h"
#include "physics/particle.h"
#include "physics/core.h"
#include "physics/ammo_round.h"

using namespace physics;

/**
 * Simulate the shooting of different types of projectiles.
 * The demo input data can be easily customized at the
 * beginning of the execute function.
 */
struct BallisticDemo
{
	static void execute()
	{
		// demo input data
		ShotType currentShotType = ShotType::ARTILLERY;
		int projectileMaxAge = 15000;
		int projectileZBound = 200;

		core::FrameTimer* timer = core::FrameTimer::get();
		timer->update();

		Particle projectile;
		projectile.setPosition(0.0f, 1.5f, 0.0f);

		switch (currentShotType)
		{
		case ShotType::PISTOL:
			projectile.setMass(2.0f); // 2.0kg
			projectile.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
			projectile.setAcceleration(0.0f, -1.0f, 0.0f);
			projectile.damping = 0.99f;
			break;
		case ShotType::ARTILLERY:
			projectile.setMass(200.0f);
			projectile.setVelocity(0.0f, 30.0f, 40.0f);
			projectile.setAcceleration(0.0f, -20.0f, 0.0f);
			projectile.damping = 0.99f;
			break;
		case ShotType::FIREBALL:
			projectile.setMass(1.0f);
			projectile.setVelocity(0.0f, 0.0f, 10.0f);
			projectile.setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
			projectile.damping = 0.9f;
			break;
		case ShotType::LASER:
			projectile.setMass(0.1f);
			projectile.setVelocity(0.0f, 00.0f, 100.0f);
			projectile.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity
			projectile.damping = 0.99f;
			break;
		}

		AmmoRound shot;
		shot.type = currentShotType;
		shot.particle = projectile;
		shot.startTime = timer->lastFrameTimestamp;

		shot.particle.clearAccumulator();

		// Main loop.
		while (true)
		{
			timer->update();
			const double dt = timer->getDeltaTime();

			if (shot.isNotValid(projectileMaxAge, projectileZBound))
			{
				std::cout << "Projectile destroyed / hidden" << '\n';
				break;
			}

			shot.particle.integrate((real)dt);

			std::cout << "X: " << shot.particle.position.x << "; Y:" << shot.particle.position.y << "; Z:" << shot.particle.position.z << '\n';

			// Emulate workload 16ms (~60fps).
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}
};

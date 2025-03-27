#include <iostream>
#include <thread>
#include "core/frame_timer.h"
#include "physics/particle.h"
#include "physics/core.h"

using namespace physics;
using namespace core;

/**
 * Spawns a particle and applies a force to it.
 * Watch the particle being slowed down by the damping over time.
 * Eventually, the particle motion stops.
 */
struct SimpleParticleDemo
{
	static void execute()
	{
		FrameTimer* timer = FrameTimer::get();

		Particle particle;
		particle.position = Vector3(0, 0, 0);
		particle.setMass(0.1);
		particle.damping = (real)0.99;

		// Todo: demo purposes
		particle.addForce(Vector3(10, 20, 30));

		// Main loop.
		while (true)
		{
			timer->update();
			const double dt = timer->getDeltaTime();

			particle.integrate((real)dt);

			std::cout << "X: " << particle.position.x << "; Y:" << particle.position.y << "; Z:" << particle.position.z << '\n';

			// Emulate workload 16ms (~60fps).
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}
};

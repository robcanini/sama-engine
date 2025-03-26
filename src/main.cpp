#include <iostream>
#include <thread>
#include "core/frame_timer.h"
#include "cyclone/particle.h"
#include "cyclone/core.h"

using namespace cyclone;

int main()
{
	core::FrameTimer timer;

	Particle particle;
	particle.position = Vector3(0, 0, 0);
	particle.setMass(1);
	particle.damping = (real)0.99;

	bool bForceApplied = false;

	// main loop
	while (true)
	{
		timer.update();
		const double dt = timer.getDeltaTime();

		particle.integrate((real)dt);

		std::cout << "X: " << particle.position.x << "; Y:" << particle.position.y << "; Z:" << particle.position.z << '\n';

		// todo: dev purposes
		if (!bForceApplied)
		{
			particle.addForce(Vector3(1, 2, 3));
			bForceApplied = true;
		}

		// emulate workload 16ms (~60fps)
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
#include "core/frame_timer.h"
#include "physics/pworld.h"
#include "physics/plinks.h"

using namespace core;
using namespace physics;

int main()
{
	loop();
}

void loop()
{
	FrameTimer* timer = FrameTimer::get();
	while (1)
	{
		timer->update();
		const double dt = timer->getDeltaTime();
	}

	// Prepare the objects for this frame.
	// world.startFrame();
	
	// Calls to other parts of the game code.
	// runGraphicsUpdate();
	// updateCharacters();

	// Update the physics.
	// world.runPhysics();

	// if (gameOver) break;
}

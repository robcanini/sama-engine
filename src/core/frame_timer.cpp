#include "core/frame_timer.h"

namespace core {

	void core::FrameTimer::update()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		deltaTime_ = std::chrono::duration<double>(currentTime - previousTime_).count();
		previousTime_ = currentTime;
	}
}

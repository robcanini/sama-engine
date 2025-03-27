#include "core/frame_timer.h"

namespace core {

	FrameTimer* FrameTimer::singleton_ = nullptr;

	void core::FrameTimer::update()
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();

		deltaTime_ = std::chrono::duration<double>(currentTime - previousTime_).count();

		previousTime_ = currentTime;

		lastFrameTimestamp = static_cast<unsigned>(
			std::chrono::duration_cast<std::chrono::milliseconds>(
				currentTime.time_since_epoch()).count()
			);
	}
}

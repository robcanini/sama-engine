#pragma once

#include <chrono>

namespace core {

	class FrameTimer
	{
	public:
		FrameTimer() : previousTime_(std::chrono::high_resolution_clock::now()),
			deltaTime_(0.0);

		void update();

		double getDeltaTime() const
		{
			return deltaTime_;
		}

	private:
		std::chrono::high_resolution_clock::time_point previousTime_;
		double deltaTime_;
	};
}
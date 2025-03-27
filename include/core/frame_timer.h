#pragma once

#include <chrono>

namespace core {

    class FrameTimer
    {
    public:
        FrameTimer(const FrameTimer&) = delete;

        void operator=(const FrameTimer&) = delete;

        static FrameTimer *get()
        {
            if (singleton_ == nullptr) {
                singleton_ = new FrameTimer();
            }
            return singleton_;
        }

        void update();

        double getDeltaTime() const
        {
            return deltaTime_;
        }

        unsigned lastFrameTimestamp;

    protected:
        static FrameTimer* singleton_;

        FrameTimer()
            : previousTime_(std::chrono::high_resolution_clock::now()), deltaTime_(0.0), lastFrameTimestamp(0)
        {
        }

    private:
        std::chrono::high_resolution_clock::time_point previousTime_;
        double deltaTime_;
    };

}

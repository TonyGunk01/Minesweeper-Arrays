#pragma once
#include <chrono>

using namespace std;
using namespace chrono;

namespace Time
{
    class TimeManager
    {
        private:
            static time_point<steady_clock> previous_time;
            static float delta_time;

            static void updateDeltaTime();
            static float calculateDeltaTime();
            static void updatePreviousTime();

        public:
            static void initialize();
            static void update();

            static float getDeltaTime();
    };
}
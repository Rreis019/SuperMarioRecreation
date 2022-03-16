#include "Timer.h"
#include <SDL2/SDL.h>
#include <chrono>

Timer timer = Timer();

Timer::Timer()
{
	startTick =0;
}

using namespace std::chrono;
typedef high_resolution_clock Clock;
Clock::time_point lastTime;

void Timer::tick(int LimitFps)
{
	Clock::time_point time = Clock::now();
	deltaTime = duration_cast<nanoseconds>(time - lastTime).count()  / 1000000000.0f;
	lastTime = time;
	if(deltaTime > (1.0f / LimitFps) * 1.5 ){deltaTime = 1.0f / LimitFps;}
	

	Uint32 EndTick = SDL_GetTicks();
	int tempDt = EndTick - startTick;
	if ((1000 / LimitFps) > tempDt) {
		SDL_Delay(1000 / LimitFps - (tempDt));
	}
	startTick = SDL_GetTicks();
}

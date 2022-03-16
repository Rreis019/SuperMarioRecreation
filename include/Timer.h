#pragma once

class Timer
{
public:
	Timer();
	void tick(int LimitFps); //Update the clock
	int getFps() {return  1 / deltaTime;}	//Return framerate

	//FPS = 60 -> deltaTime = 1/60 = 0.0166666666666667
	float deltaTime = 0;
	int startTick = 0;
private:
};

extern Timer timer;

#define ANIMATION(startSpriteIndex,numberSprites,delay) (timer.startTick / delay ) % numberSprites + startSpriteIndex

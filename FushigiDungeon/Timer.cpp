#include "Timer.h"
Timer::Timer()
{

}

// The time of last frame
float Timer::deltaTime = 0;
// Total time cost
unsigned int Timer::ticksCount = 0;
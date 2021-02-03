#include "SDL.h"
class Timer
{
public:
	Timer();
	static float deltaTime;
	static Uint32 ticksCount;
};
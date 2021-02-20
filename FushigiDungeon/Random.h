#pragma  once
#include <random>
#include "Math.h"

class Random
{
public:
	// Init random class and get a random seed
	static void Init();
	static void Seed(unsigned int seed);
	// Get random integer from min to max (include min and max)
	static int GetIntRange(int min, int max);

private:
	static std::mt19937 sGenerator;
};

#include "Random.h"

void Random::Init()
// Init random class and get a random seed
{
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed)
{
	sGenerator.seed(seed);
}

int Random::GetIntRange(int min, int max)
// Get random integer from min to max (include min and max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGenerator);
}

std::mt19937 Random::sGenerator;

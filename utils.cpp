#include "utils.h"
#include <chrono>
#include <random>


static std::default_random_engine g_generator(std::chrono::system_clock::now().time_since_epoch().count());


int randInt(int ceiling)
{
	std::uniform_int_distribution<int> distribution(0, ceiling);
	return distribution(g_generator);
}

int randInt(int floor, int ceiling)
{
	std::uniform_int_distribution<int> distribution(floor, ceiling);
	return distribution(g_generator);
}

float randFloat(float ceiling)
{
	std::uniform_real_distribution<float> distribution(0, ceiling);
	return distribution(g_generator);
}

float randFloat(float floor, float ceiling)
{
	std::uniform_real_distribution<float> distribution(floor, ceiling);
	return distribution(g_generator);
}



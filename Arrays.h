#pragma once
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>

///Functions for arrays manipulation
namespace Arrays
{
	void fillArrayRandom(std::vector<int>& arr, unsigned int size, int min, int max);

	void showArray(std::vector<int>& arr);
}
#include "Arrays.h"

void Arrays::fillArrayRandom(std::vector<int>& arr, unsigned int size, int min, int max)
{
	srand((unsigned int)time(0));

	for (unsigned int i = 0; i < size; i++)
		arr.push_back(std::rand() % (max - min + 1) + min);
}

void Arrays::showArray(std::vector<int>& arr)
{
	std::cout << "Here's your array:" << std::endl;
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>

#include "Arrays.h"
#include "Algorithms.h"
#include "Visualizer.h"

int main()
{

	const int arraySize = 1000;
	const int range[2] = { 50, 900 };
	std::vector<int> exampleArray;

	Arrays::fillArrayRandom(exampleArray, arraySize, range[0], range[1]);

	//shows array values in the console
	//uncomment if you don't need console
	//ShowWindow(GetConsoleWindow(), SW_HIDE); //for hiding console
	//Arrays::showArray(exampleArray);

	Visualizer::draw(exampleArray, Algorithms::Type::bubbleSort);
	system("pause");
}


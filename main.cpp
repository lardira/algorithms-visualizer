#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Arrays.h"
#include "Algorithms.h"

//TODO: Quicksort, Mergesort, SelectionSort, HeapSort, InsertionSort

void drawRods(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window)
{
	for (int i = 0; i < arr.size(); i++)
	{
		rods[i].setSize(sf::Vector2f(rods[0].getSize().x, (float)arr[i]));
		rods[i].setPosition(rods[i].getPosition().x, (float)window.getSize().y - rods[i].getSize().y);

		window.draw(rods[i]);
	}
}

void Draw(std::vector<int>& arr)
{
	const unsigned int screenSize[2] = { 1080, 1080 };
	sf::RenderWindow window = { sf::VideoMode(screenSize[0], screenSize[1]), "Agorithms Visualizer" };

	std::vector<sf::RectangleShape> rods;

	//create a graphical text to display later
	sf::Font font;
	unsigned int defaultSize = 35, minSize = 4;
	if (!font.loadFromFile("fonts/main_04b03b.ttf"))
		return;

	std::string sInfo;
	std::string algorithmType = "Algorithm: Selection Sort";
	sInfo = sInfo + algorithmType + "\nQuantity: " + std::to_string(arr.size());
	sf::Text info(sInfo, font, 32);
	info.setFillColor(sf::Color::Green);

	//creating rods
	for (int i = 0; i < arr.size(); i++)
	{
		sf::Vector2f initialSize = { (float)window.getSize().x / arr.size(), (float)arr[i]};
		sf::RectangleShape rod(initialSize);
		rod.setPosition(sf::Vector2f(i * initialSize.x, (float)window.getSize().y - initialSize.y));

		rods.push_back(rod);
	}

	//main drawing loop
	//the starting point for algorithms (dunno how to do it differently)
	int step = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(info);

		Algorithms::selectionSort(arr, step);
		step++;

		drawRods(rods, arr, window);
		window.display();
	}
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE); //for hiding console

	const int arraySize = 1000;
	std::vector<int> example;

	Arrays::fillArrayRandom(example, arraySize, 50, 1000);
	Arrays::showArray(example);

	Draw(example);
	
	return 0;
}


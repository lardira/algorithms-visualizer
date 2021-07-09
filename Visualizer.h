#pragma once
#include <SFML\Graphics.hpp>
#include "Algorithms.h"

namespace Visualizer
{
	void drawRods(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window);
	void fillRodsArray(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window);
	void draw(std::vector<int>& arr);
}
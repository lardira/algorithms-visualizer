#pragma once
#include <SFML\Graphics.hpp>
#include "Algorithms.h"

namespace Visualizer
{
	/// <summary>
	/// Draws rods on the screen
	/// *Each rod has the same size as a value with the same index in the array
	/// </summary>
	/// <param name="rods"> - Array of rods (sf::Shape)</param>
	/// <param name="arr"> - Array with predefined values</param>
	/// <param name="window"> - Window to draw things in</param>
	void drawRods(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window);

	/// <summary>
	/// Creates rods with dependant size and fills the array with them
	/// </summary>
	/// <param name="rods"> - Array of rods (sf::Shape)</param>
	/// <param name="arr"> - Array with predefined values</param>
	/// <param name="window"> - Window to draw things in</param>
	void fillRodsArray(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window);
	
	/// <summary>
	/// Main draw loop, sets up the window and draws everything
	/// </summary>
	/// <param name="arr"> - Array with predefined values</param>
	void draw(std::vector<int>& arr, Algorithms::Type type);
}
#include "Visualizer.h"

namespace Visualizer //TODO: Quicksort, Mergesort, HeapSort
{	

/// <summary>
/// Draws rods on the screen
/// *Each rod has the same size as a value with the same index in the array
/// </summary>
/// <param name="rods"> - Array of rods (sf::Shape)</param>
/// <param name="arr"> - Array with predefined values</param>
/// <param name="window"> - Window to draw things in</param>
void drawRods(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window)
{
	for (int i = 0; i < arr.size(); i++)
	{
		rods[i].setSize(sf::Vector2f(rods[0].getSize().x, (float)arr[i]));
		rods[i].setPosition(rods[i].getPosition().x, (float)window.getSize().y - rods[i].getSize().y);

		window.draw(rods[i]);
	}
}

/// <summary>
/// Creates rods with dependant size and fills the array with them
/// </summary>
/// <param name="rods"> - Array of rods (sf::Shape)</param>
/// <param name="arr"> - Array with predefined values</param>
/// <param name="window"> - Window to draw things in</param>
void fillRodsArray(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window)
{
	for (int i = 0; i < arr.size(); i++)
	{
		sf::Vector2f initialSize = { (float)window.getSize().x / arr.size(), (float)arr[i] };
		sf::RectangleShape rod(initialSize);
		rod.setPosition(sf::Vector2f(i * initialSize.x, (float)window.getSize().y - initialSize.y));

		rods.push_back(rod);
	}
}

//easier and more readable way of storing algorithms info
static struct Info
{
public:
	Info() = default;
	~Info() = default;

	Info(std::string type, size_t quantity)
	{
		SetAlgorithmType(type);
		SetQuantity(quantity);
	}

	//copy constructor
	Info(Info& info)
		: algorithmType(info.GetAlgorithmType()), quantity(info.GetQuantity())
	{
	}

	std::string GetInfo() const
	{
		return algorithmType + "\n" + quantity;
	}

	void SetAlgorithmType(std::string type)
	{
		algorithmType = type;
	}

	std::string GetAlgorithmType() const
	{
		return algorithmType;
	}

	void SetQuantity(size_t quantity)
	{
		Info::quantity = "Quantity: " + std::to_string(quantity);
	}

	std::string GetQuantity() const
	{
		return quantity;
	}

private:
	std::string algorithmType;
	std::string quantity;
};

void draw(std::vector<int>& arr)
{
	const unsigned int screenSize[2] = { 1080, 1080 };
	sf::RenderWindow window = { sf::VideoMode(screenSize[0], screenSize[1]), "Agorithms Visualizer" };

	std::vector<sf::RectangleShape> rods;

	//create a graphical text to display later
	sf::Font font;
	unsigned int defaultSize = 35, minSize = 4;
	if (!font.loadFromFile("fonts/main_04b03b.ttf"))
		return;

	Info description("Selection Sort", arr.size());

	sf::Text info(description.GetInfo(), font, 32);
	info.setFillColor(sf::Color::Green);

	fillRodsArray(rods, arr, window);

	/// <summary>
	/// the starting point for algorithms (dunno how to do it differently)
	/// </summary>
	int step = 0;

	//main drawing loop☺
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//show info
		window.draw(info);

		//calls sorting algorithm (step is required cuz it's using 
		// a sorting algorithm in a while loop
		Algorithms::selectionSort(arr, step);
		step++;

		//draws updated rods
		drawRods(rods, arr, window);
		window.display();
	}
}

}
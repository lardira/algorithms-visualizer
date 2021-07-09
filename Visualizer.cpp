#include "Visualizer.h"

namespace Visualizer //TODO: Quicksort, Mergesort, HeapSort
{	

void drawRods(std::vector<sf::RectangleShape>& rods, std::vector<int>& arr, sf::RenderWindow& window)
{
	for (int i = 0; i < arr.size(); i++)
	{
		rods[i].setSize(sf::Vector2f(rods[0].getSize().x, (float)arr[i]));
		rods[i].setPosition(rods[i].getPosition().x, (float)window.getSize().y - rods[i].getSize().y);

		window.draw(rods[i]);
	}
}

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

	Info(Algorithms::Type type, size_t quantity)
	{

		switch (type)
		{
		case Algorithms::Type::bubbleSort:
			SetAlgorithmType("Bubble Sort");
			break;

		case Algorithms::Type::insertionSort:
			SetAlgorithmType("Insertion Sort");
			break;

		case Algorithms::Type::selectionSort:
			SetAlgorithmType("Selection Sort");
			break;

		default:
			throw std::invalid_argument("Recieved a wrong algorithm type");
			break;
		}

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

	void SetAlgorithmType(Algorithms::Type type)
	{
		switch (type)
		{
		case Algorithms::Type::bubbleSort:
			algorithmType = "Bubble Sort";
			break;

		case Algorithms::Type::insertionSort:
			algorithmType = "Insertion Sort";
			break;

		case Algorithms::Type::selectionSort:
			algorithmType = "Selection Sort";
			break;

		default:
			throw std::invalid_argument("Recieved a wrong algorithm type");
			break;
		}
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

void draw(std::vector<int>& arr, Algorithms::Type type)
{
	const unsigned int screenSize[2] = { 1080, 1080 };
	sf::RenderWindow window = { sf::VideoMode(screenSize[0], screenSize[1]), "Agorithms Visualizer" };

	std::vector<sf::RectangleShape> rods;

	const std::vector<int> copyArray(arr);

	//create a graphical text to display later
	sf::Font font;
	unsigned int defaultSize = 35, minSize = 4;
	if (!font.loadFromFile("fonts/main_04b03b.ttf"))
		return;

	Info description(type, arr.size());

	sf::Text info(description.GetInfo(), font, 32);
	sf::Text hints("F1: bubble sort F2: insertion sort F3: selection sort", font, 24);
	info.setFillColor(sf::Color::Green);
	hints.setFillColor(sf::Color::Green);
	hints.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 0));

	fillRodsArray(rods, arr, window);

	/// <summary>
	/// the starting point for algorithms (dunno how to do it differently)
	/// </summary>
	int step = 0;
	//main drawing loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				switch (event.key.code)
				{
				case sf::Keyboard::F1:
					type = Algorithms::Type::bubbleSort;
					step = 0;
					arr = copyArray;
					description.SetAlgorithmType(type);
					info.setString(description.GetInfo());
					break;

				case sf::Keyboard::F2:
					type = Algorithms::Type::insertionSort;
					step = 0;
					arr = copyArray;
					description.SetAlgorithmType(type);
					info.setString(description.GetInfo());
					break;

				case sf::Keyboard::F3:
					type = Algorithms::Type::selectionSort;
					step = 0;
					arr = copyArray;
					description.SetAlgorithmType(type);
					info.setString(description.GetInfo());
					break;

				default:
					break;
				}
		}

		window.clear();
		//show info
		window.draw(info);
		window.draw(hints);

		//calls sorting algorithm (step is required cuz it's using 
		// a sorting algorithm in a while loop
		if (step < arr.size())
		{
			switch (type)
			{
			case Algorithms::Type::bubbleSort:
				Algorithms::bubbleSort(arr, step);
				break;

			case Algorithms::Type::insertionSort:
				Algorithms::insertionSort(arr, step);
				break;

			case Algorithms::Type::selectionSort:
				Algorithms::selectionSort(arr, step);
				break;

			default:
				throw std::invalid_argument("Recieved a wrong algorithm type");
				break;
			}
			step++;
		}

		//draws updated rods
		drawRods(rods, arr, window);
		window.display();
	}
}

}
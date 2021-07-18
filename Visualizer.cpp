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

void colorRods(std::vector<sf::RectangleShape>& rods, std::pair<int, int>& idsCompared, int step)
{
	for (size_t i = 0; i < rods.size(); i++)
		if (i != idsCompared.first || i != idsCompared.second)
			rods[i].setFillColor(sf::Color::White);

	rods[idsCompared.first].setFillColor(sf::Color::Green);
	rods[idsCompared.second].setFillColor(sf::Color::Green);
	rods[step].setFillColor(sf::Color::Blue);
}

void clearRods(std::vector<sf::RectangleShape>& rods)
{
	for (size_t i = 0; i < rods.size(); i++)
		rods[i].setFillColor(sf::Color::White);
}

//easier and more readable way of storing algorithms info
class AlgorithmDescription
{
public:
	AlgorithmDescription() = default;
	~AlgorithmDescription() = default;

	AlgorithmDescription(std::string type, size_t quantity)
	{
		SetAlgorithmType(type);
		SetQuantity(quantity);
	}

	AlgorithmDescription(Algorithms::Type type, size_t quantity)
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
	AlgorithmDescription(AlgorithmDescription& info)
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
		AlgorithmDescription::quantity = "Quantity: " + std::to_string(quantity);
	}

	std::string GetQuantity() const
	{
		return quantity;
	}

private:
	std::string algorithmType;
	std::string quantity;
};

class HintsPanel
{
public:
	bool isEnabled = false;
	sf::RectangleShape& panel;
	sf::Text& sfText;

private:
	std::string text = 
	{
			"Tilda(~): Close Hints\n"
			"Esc: Close Program\n"
			"Space: Pause/Play\n"
			"Up/Down: Change Speed\n"
			"F1: Bubble Sort\n"
			"F2: Insertion Sort\n"
			"F3: Selection Sort\n"
	};

public:
	HintsPanel(sf::RectangleShape& sfShape, sf::Text& sfText):
		panel(sfShape), sfText(sfText)
	{		
		unsigned int charSize = 24;
		sfShape.setSize(sf::Vector2f(15.f * charSize, 10.f * charSize));
		//gray color rgba(149, 165, 166)
		//alpha channel (200)
		sfShape.setFillColor(sf::Color(149, 165, 166, 200));
		sfText.setString(text);
		sfText.setCharacterSize(charSize);
		sfText.setFillColor(sf::Color::Green);
	}

	HintsPanel() = default;
	~HintsPanel() = default;

	void setPosition(sf::Vector2f& pos)
	{
		sfText.setPosition(pos);
		panel.setPosition(pos);
	}

	void setPosition(float x, float y)
	{
		sf::Vector2f newPos = { x, y };
		sfText.setPosition(newPos);
		panel.setPosition(newPos);
	}
};

void draw(std::vector<int>& arr, Algorithms::Type type)
{
	bool isShowing = false, isShowingHints = false;
	const unsigned int screenSize[2] = { 1000, 1000 };
	sf::RenderWindow window = { sf::VideoMode(screenSize[0], screenSize[1]), "Agorithms Visualizer" };

	std::vector<sf::RectangleShape> rods;
	std::pair<int, int> idsCompared;
	const std::vector<int> copyArray(arr);

	int timeToSLeep = 50;

	//create a graphical text to display later
	sf::Font font;
	unsigned int defaultSize = 35, minSize = 4;
	if (!font.loadFromFile("fonts/main_04b03b.ttf"))
		return;

	AlgorithmDescription description(type, arr.size());
	sf::Text info(description.GetInfo(), font, 32);
	info.setFillColor(sf::Color::Green);

	sf::RectangleShape panelShape;
	sf::Text hints;
	HintsPanel hintsPanel(panelShape, hints);
	hintsPanel.sfText.setFont(font);
	hintsPanel.setPosition((float)window.getSize().x / 2, 0);

	sf::Text howToShowHints(hints);
	howToShowHints.setString("Press (~) to show hints");

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
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Tilde:
					hintsPanel.isEnabled = !hintsPanel.isEnabled;
					break;
					//reset variabled and switch to another algorithm
				case sf::Keyboard::F1:
				case sf::Keyboard::F2:
				case sf::Keyboard::F3:
					type = (Algorithms::Type)(event.key.code - sf::Keyboard::F1);
					idsCompared.first = 0;
					idsCompared.second = 0;
					step = 0;
					arr = copyArray;
					description.SetAlgorithmType(type);
					info.setString(description.GetInfo());
					break;

				case sf::Keyboard::Space:
					isShowing = !isShowing;
					break;

				case sf::Keyboard::Escape:
					std::exit(1);
					break;

				case sf::Keyboard::Down:
					timeToSLeep = timeToSLeep < 500 ? timeToSLeep + 25 : timeToSLeep;
					break;

				case sf::Keyboard::Up:
					timeToSLeep = timeToSLeep - 25 > 0 ? timeToSLeep - 25 : 0;
					break;

				default:
					//TODO:throw an exception
					break;
				}
			}
		}

		//wait before proceeding for clearer visualization
		std::this_thread::sleep_for(std::chrono::milliseconds(timeToSLeep));

		//refreshing window for drawing new frame
		window.clear();

		//calls sorting algorithm (step is required cuz it's using 
		// a sorting algorithm in a while loop
		if (step < arr.size() && isShowing)
		{
			switch (type)
			{
			case Algorithms::Type::bubbleSort:
				Algorithms::bubbleSort(arr, step, idsCompared);
				break;

			case Algorithms::Type::insertionSort:
				Algorithms::insertionSort(arr, step, idsCompared);
				break;

			case Algorithms::Type::selectionSort:
				Algorithms::selectionSort(arr, step, idsCompared);
				break;

			default:
				throw std::invalid_argument("Recieved a wrong algorithm type");
				break;
			}
			step++;
		}

		//color rods that's being compared or clear them if the program is done visualization
		step < rods.size() ? colorRods(rods, idsCompared, step) : clearRods(rods);
		//draws updated rods
		drawRods(rods, arr, window);
		//drawing algorithm description
		window.draw(info);
		//drawing hints panel
		if (hintsPanel.isEnabled)
		{
			window.draw(hintsPanel.panel);
			window.draw(hintsPanel.sfText);
		}
		else
		{
			window.draw(howToShowHints);
		}
		//displays everything that has been drawn to the window
		window.display();
	}
}

}
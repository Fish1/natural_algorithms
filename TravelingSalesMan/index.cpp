#include <SFML/Graphics.hpp>

#include <iostream>

#include <utility>

#include <vector>

#include <cmath>

#include <fstream>

#include <random>

#include "LocalRandomSearch.hpp"

#include "Utilities.hpp"

void plot(sf::RenderWindow & window, std::vector<Coordinate> coordinates)
{
	sf::CircleShape point(3.0f);

	Coordinate lastCoordinate = coordinates.at(coordinates.size() - 1);

	for(Coordinate coordinate : coordinates)
	{
		point.setPosition(coordinate.x, coordinate.y);
		point.setOrigin(1.5f, 1.5f);

		window.draw(point);

		sf::Vertex line[] = 
		{ 
			sf::Vertex(sf::Vector2f(coordinate.x, coordinate.y)), 
			sf::Vertex(sf::Vector2f(lastCoordinate.x, lastCoordinate.y)) 
		};
		
		window.draw(line, 2, sf::Lines);

		lastCoordinate = coordinate;
	}
}

int main(void)
{
	std::vector<Coordinate> coordinates;	
	loadCoordinates("data", coordinates);

	sf::RenderWindow window(sf::VideoMode(500, 500), "Sales Man");

	LocalRandomSearch lrv(coordinates);

	uint64_t i = 0;

	while(window.isOpen())
	{

		lrv.run();

		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::Enter)
				{
					std::cout << "Iteration: " << lrv.getTotalIterations() << " Heat: " << lrv.getHeat() << std::endl;
				}
		}

		if(i % 100 == 0)
		{
			window.clear();
			plot(window, lrv.getBestList());
			window.display();
		}

		++i;
	}

	return 0;
}

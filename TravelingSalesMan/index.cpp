#include <SFML/Graphics.hpp>

#include <iostream>

#include <utility>

#include <vector>

#include <cmath>

#include <fstream>

#include <random>

#include "LocalRandomSearch.hpp"

#include "Utilities.hpp"

void plot(sf::RenderWindow & window, std::vector<Coordinate> & best, std::vector<Coordinate> & current)
{
	sf::RectangleShape point(sf::Vector2f(5.0f, 5.0f));

	Coordinate lastCoordinate = current.at(current.size() - 1);

	for(Coordinate coordinate : current)
	{
		
		sf::Vertex line[] = 
		{ 
			sf::Vertex(sf::Vector2f(coordinate.x, coordinate.y), sf::Color::Red), 
			sf::Vertex(sf::Vector2f(lastCoordinate.x, lastCoordinate.y), sf::Color::Red) 
		};
		
		window.draw(line, 2, sf::Lines);
		lastCoordinate = coordinate;
	}
	
	lastCoordinate = best.at(best.size() - 1);

	for(Coordinate coordinate : best)
	{
		sf::Vertex line[] = 
		{ 
			sf::Vertex(sf::Vector2f(coordinate.x, coordinate.y), sf::Color::Green), 
			sf::Vertex(sf::Vector2f(lastCoordinate.x, lastCoordinate.y), sf::Color::Green) 
		};
		
		window.draw(line, 2, sf::Lines);
		lastCoordinate = coordinate;
	}
	
	for(Coordinate coordinate : best)
	{
		point.setPosition(coordinate.x, coordinate.y);
		point.setOrigin(2.5f, 2.5f);
//		point.setFillColor(sf::Color::Red);

		window.draw(point);
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
					std::cout << "Iteration: " << lrv.getTotalIterations() << " Heat: " << lrv.getHeat();
					std::cout << " Best Perimeter: " << lrv.getBestPerimeter() << std::endl;
				}
		}

		if(i % 100 == 0)
		{
			window.clear();
			plot(window, lrv.getBestList(), lrv.getCurrentList());
			window.display();
		}

		++i;
	}

	return 0;
}

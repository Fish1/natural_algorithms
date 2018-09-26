#include "Utilities.hpp"

#include <cmath>

#include <random>

#include <fstream>

#include <iostream>

double calculateDistance(Coordinate a, Coordinate b)
{
	return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));	
}
 
double calculatePerimeter(std::vector<Coordinate> coordinates)
{
	double result = 0.0;
	
	Coordinate lastCoordinate = coordinates.at(coordinates.size() - 1);

	for(Coordinate coordinate : coordinates)
	{
		double distance = calculateDistance(lastCoordinate, coordinate);

		result += distance;

		lastCoordinate = coordinate;	
	}

	return result;
}

void randomizeOrder(std::vector<Coordinate> & coordinates)
{
	std::random_device device;
	std::uniform_int_distribution<int> distribution(0, coordinates.size() - 1);

	for(uint32_t index = 0; index < coordinates.size(); ++index)
	{
		uint32_t swap_index = distribution(device);

		Coordinate tempCoordinate = coordinates.at(index);
		coordinates.at(index) = coordinates.at(swap_index);
		coordinates.at(swap_index) = tempCoordinate;
	}
}

void randomSwap(std::vector<Coordinate> & coordinates)
{
	std::random_device device;
	std::uniform_int_distribution<int> distribution(0, coordinates.size() - 1);

	uint32_t i = distribution(device);	
	uint32_t j = distribution(device);	

	Coordinate tempCoordinate = coordinates.at(j);
	coordinates.at(j) = coordinates.at(i);
	coordinates.at(i) = tempCoordinate;
}

void randomSwapNeighbors(std::vector<Coordinate> & coordinates)
{
	std::random_device device;
	std::uniform_int_distribution<int> distribution(0, coordinates.size() - 1);
	
	uint32_t i = distribution(device);
	uint32_t j = (i + 1) % coordinates.size();
	
	Coordinate tempCoordinate = coordinates.at(j);
	coordinates.at(j) = coordinates.at(i);
	coordinates.at(i) = tempCoordinate;
}

void randomSwapNeighborsInArea(std::vector<Coordinate> & coordinates, uint32_t start, uint32_t end)
{
	/*
	if(start > coordinates.size() - 1)
	{
		start = 0;
	}

	if(end > coordinates.size() - 1)
	{
		end = coordinates.size() - 1;
	}
	*/

	std::random_device device;
	std::uniform_int_distribution<int> distribution(start, end);
	
	uint32_t i = distribution(device) % coordinates.size();
	uint32_t j = (i + 1) % coordinates.size();

	if(i >= coordinates.size())
	{
		i = coordinates.size() - 1;
	}
	
	if(j >= coordinates.size())
	{
		j = coordinates.size() - 1;
	}
	
	Coordinate tempCoordinate = coordinates.at(j);
	coordinates.at(j) = coordinates.at(i);
	coordinates.at(i) = tempCoordinate;
}

void loadCoordinates(std::string filename, std::vector<Coordinate> & coordinates)
{
	std::ifstream file(filename);

	coordinates.clear();

	double x, y;

	while(file >> x && file >> y)
	{
		Coordinate coord(x, y);

		coordinates.push_back(coord);
	}
}

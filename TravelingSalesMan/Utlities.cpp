#include "Utilities.hpp"

#include <cmath>

#include <random>

#include <fstream>

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

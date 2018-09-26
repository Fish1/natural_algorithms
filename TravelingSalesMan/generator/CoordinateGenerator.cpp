#include <fstream>

#include <random>

#include "Utilities.hpp"

#include "Coordinate.hpp"

void generateCoordinateData(std::string filename, uint32_t amount)
{
	std::ofstream file(filename);

	std::random_device device;
	std::uniform_real_distribution<double> distribution(1.0, 800.0);

	for(uint32_t index = 0; index < amount; ++index)
	{
		file << distribution(device);
		file << " ";
		file << distribution(device);
		file << std::endl;	
	}

	file.close();
}

void generateCircleData(std::string filename, uint32_t amount)
{
	std::ofstream file(filename);

	std::vector<Coordinate> coords;

	for(uint32_t index = 0; index < amount; ++index)
	{
		double x = std::cos((double)index * 2.0 * 3.1415 / (double)amount);
		double y = std::sin((double)index * 2.0 * 3.1415 / (double)amount);

		x *= 200;
		y *= 200;

		x += 250;
		y += 250;

		Coordinate c(x, y);

		coords.push_back(c);
	}

	randomizeOrder(coords);

	for(Coordinate coord : coords)
	{
		file << coord.x << " " << coord.y << std::endl;
	}

	file.close();
}

int main(int argc, char ** argv)
{
	std::string filename(argv[1]);
	
	uint32_t amount = std::stoi(argv[2]);

	//generateCoordinateData(filename, amount);
		
	generateCircleData(filename, amount);
}

#include <fstream>

#include <random>

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

int main(int argc, char ** argv)
{
	std::string filename(argv[1]);
	
	uint32_t amount = std::stoi(argv[2]);

	generateCoordinateData(filename, amount);
}

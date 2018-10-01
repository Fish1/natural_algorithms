#include <iostream>

#include <vector>

#include "Fitness.hpp"

std::vector<Pair> generateInitialRow(unsigned int size)
{
	std::vector<Pair> result;

	for(unsigned int index = 0; index < size; ++index)
	{
		Pair p(index * 2, index * 2 + 1);
		
		result.push_back(p);
	}

	return result;
}

void printGrid(std::vector<Pair> grid, unsigned int size)
{
	for(unsigned int y = 0; y < size; ++y)
	{
		std::cout << "\t";

		for(unsigned int x = 0; x < size; ++x)
		{
			std::cout << grid.at(x + size * y).m_a << ":" << grid.at(x + size * y).m_b << "\t";
		}

		std::cout << std::endl;
	}
}

void printGrid_test(std::vector<Pair> grid, unsigned int columns)
{
	for(unsigned int index = 0; index < grid.size(); ++index)
	{
		if(index % columns == 0)
		{
			std::cout << std::endl << "\t";
		}	

		std::cout << grid.at(index).m_a << ":" << grid.at(index).m_b << "\t";
	}

	std::cout << std::endl;
}

std::vector<Pair> solveStochastic(std::vector<Pair> initialRow)
{
	srand(time(0));

	unsigned int size = initialRow.size();

	std::vector<Pair> result;
	std::vector<Pair> bestResult;
	unsigned int bestFitness;

	result.insert(result.end(), initialRow.begin(), initialRow.end());
	std::vector<Pair> previousRow;
	previousRow.insert(previousRow.end(), initialRow.begin(), initialRow.end());

	unsigned int neighborhood = 1;

	// get initial solution x (random solution)
	// get neighborhood k  (last row)

	// x1 = shake x in neighborhood k

	// x2 = firstImprovement(x1) find the first better solution

	// k += 1 (add another row to the neighborhood

	// when we get to k = rowCount, go back to bottom

	
	// CREATE INITIAL SOLUTION
	for(unsigned int row = 1; row < size; ++row)
	{
		std::vector<unsigned int> leftNumbers;
		for(unsigned int index = 0; index < size; ++index)
			leftNumbers.push_back(index * 2);
		
		std::vector<unsigned int> rightNumbers;
		for(unsigned int index = 0; index < size; ++index)
			rightNumbers.push_back((index * 2) + 1);

		
		for(unsigned int column = 0; column < size; ++column)
		{
			Pair newPair;

			unsigned int leftNumberIndex = rand() % leftNumbers.size();
			newPair.m_a = leftNumbers.at(leftNumberIndex);
			leftNumbers.erase(leftNumbers.begin() + leftNumberIndex);
			
			unsigned int rightNumberIndex = rand() % rightNumbers.size();
			newPair.m_b = rightNumbers.at(rightNumberIndex);
			rightNumbers.erase(rightNumbers.begin() + rightNumberIndex);

			result.push_back(newPair);
		}
	}

	bestResult = result;
	
	bestFitness = fitness_test(bestResult, size);

	while(bestFitness != 0)
	{

	// FIND FIRST IMPROVEMENT FROM CHANGING THE NEIGHBORHOOD
	for(unsigned int run = 0; run < 10000; ++run)
	{
		for(unsigned int row = 1; row < neighborhood + 1; ++row)
		{
			for(unsigned int index = 0; index < 2; ++index)
			{
				// swap two left values
				unsigned int swap_left_1 = rand() % size;	
				unsigned int swap_left_2 = rand() % size;
				unsigned int a_1 = result.at(swap_left_1 + size * neighborhood).m_a;
				unsigned int a_2 = result.at(swap_left_2 + size * neighborhood).m_a;
				result.at(swap_left_1 + size * row).m_a = a_2;
				result.at(swap_left_2 + size * row).m_a = a_1;

				// swap two right values
				unsigned int swap_right_1 = rand() % size;
				unsigned int swap_right_2 = rand() % size;
				unsigned int b_1 = result.at(swap_right_1 + size * neighborhood).m_b;
				unsigned int b_2 = result.at(swap_right_2 + size * neighborhood).m_b;
				result.at(swap_right_1 + size * row).m_b = b_2;
				result.at(swap_right_2 + size * row).m_b = b_1;
			}
		}

		unsigned int currentFitness = fitness_test(result, size);
	
		unsigned int localFitness =  fitnessNonSquare(result, neighborhood, size);

		if(localFitness == 0)
		//if(localFitness < bestFitness)
		//if(currentFitness < bestFitness)
		{
			printGrid(result, size);
			std::cout << "Fitness: " << currentFitness << std::endl << std::endl;
			bestFitness = currentFitness;
			bestResult = result;
			break;
		}
		printGrid(result, size);
		std::cout << "Fitness: " << currentFitness << std::endl << std::endl;
	}

	result = bestResult;

	//CHANGE THE NEIGHBORHOOD
	neighborhood += 1;
	if(neighborhood == size)
	{
		std::cout << "test" << std::endl;
		neighborhood = 2;	
	}
	
	}
	
	return result;
} 


int main(int argc, char ** argv)
{
	std::cout << "xddddddddddddddddddddd.com/xddddddddddd.html" << std::endl;
	unsigned int size = std::atoi(argv[1]);

	std::vector<Pair> i = generateInitialRow(size);

	std::cout << std::endl;

	std::vector<Pair> result;

	result = solveStochastic(i);

	printGrid(result, size);

	std::cout << std::endl;

	unsigned int f = fitness_test(result, size);

	std::cout << "Fitness Test: " << f << std::endl << std::endl;
	
	return 0;
}

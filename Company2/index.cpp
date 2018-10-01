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

	result.insert(result.end(), initialRow.begin(), initialRow.end());

	std::vector<Pair> previousRow;

	previousRow.insert(previousRow.end(), initialRow.begin(), initialRow.end());

	unsigned int iterations = 0;

	for(unsigned int row = 0; row < size - 1; ++row)
	{

		std::vector<Pair> newRow;
	
		std::vector<Pair> tempResult = result;

		unsigned int bestFitness = -1;

		unsigned int currentFitness;
		
		do
		{
			std::vector<unsigned int> leftNumbers;
			for(unsigned int index = 0; index < size; ++index)
				leftNumbers.push_back(index * 2);
			
			std::vector<unsigned int> rightNumbers;
			for(unsigned int index = 0; index < size; ++index)
				rightNumbers.push_back((index * 2) + 1);

			tempResult = result;
			newRow.clear();

			for(unsigned int column = 0; column < size; ++column)
			{
				Pair newPair;

				unsigned int leftNumberIndex = rand() % leftNumbers.size();
				newPair.m_a = leftNumbers.at(leftNumberIndex);
				leftNumbers.erase(leftNumbers.begin() + leftNumberIndex);
				
				unsigned int rightNumberIndex = rand() % rightNumbers.size();
				newPair.m_b = rightNumbers.at(rightNumberIndex);
				rightNumbers.erase(rightNumbers.begin() + rightNumberIndex);

				newRow.push_back(newPair);
			}
			
			++iterations;

			tempResult.insert(tempResult.end(), newRow.begin(), newRow.end());

			currentFitness = fitnessNonSquare(tempResult, row + 2, size);

			if(currentFitness < bestFitness)
			{
				printGrid_test(tempResult, size);

				std::cout << "Current Fitness: " << currentFitness << std::endl;
			
				bestFitness = currentFitness;

				iterations = 0;
			}
		} 
		while(currentFitness != 0 && iterations < 1000 * ((row * 5) + 1));
		
		previousRow = newRow;	

		result = tempResult;
		
		if(iterations == 1000 * ((row * 5) + 1))
		{
			// this is the second row so don't delete row 1
			if(row == 0)
			{
				result.erase(result.end() - size, result.end());
			
			}
			// otherwise delete the last two rows
			else
			{
				std::cout << "ERASE 2" << std::endl;
				result.erase(result.end() - (2 * size), result.end());
			}
			row -= 1;
			previousRow.clear();
			previousRow.insert(previousRow.end(), result.end() - size, result.end());

			std::cout << result.size() << std::endl;

			for(Pair p : result)
				std::cout << "(" << p.m_a << ":" << p.m_b << ") ";
		}

		iterations = 0;
	}

	return result;
} 


int main(int argc, char ** argv)
{
	unsigned int size = std::atoi(argv[1]);

	std::vector<Pair> i = generateInitialRow(size);

	std::cout << std::endl;

	std::vector<Pair> result;

	solveStochastic(i);

//	printGrid(result, size);

	std::cout << std::endl;

//	unsigned int f = fitness_test(result, size);

//	std::cout << "Fitness Test: " << f << std::endl << std::endl;
	
	return 0;
}

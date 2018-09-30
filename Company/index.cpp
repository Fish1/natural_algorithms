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


std::vector<Pair> solveForOdd(std::vector<Pair> initialRow)
{
	unsigned int size = initialRow.size();

	std::vector<Pair> result = initialRow;

	std::vector<Pair> previousRow = initialRow;

	for(unsigned int row = 0; row < size - 1; ++row)
	{
		std::vector<Pair> newRow;
		newRow.resize(size);

		for(unsigned int column = 0; column < size; ++column)
		{
			newRow.at(column).m_a = previousRow.at((column + 1) % size).m_a;
		}

		for(unsigned int column = 0; column < size; ++column)
		{
			newRow.at(column).m_b = previousRow.at((column + size - 1) % size).m_b;
		}

		result.insert(result.end(), newRow.begin(), newRow.end());

		previousRow = newRow;
	}

	return result;
}

std::vector<Pair> solveForMultipleFour(std::vector<Pair> initialRow)
{
	unsigned int size = initialRow.size();

	std::vector<Pair> result = initialRow;

	std::vector<Pair> previousRow = initialRow;

	for(unsigned int row = 0; row < size - 1; ++row)
	{
		std::vector<Pair> newRow;

		for(unsigned int column = 0; column < size; ++column)
		{
			Pair pair;

			// half way we do special stuff
			if(row == (size / 2) - 1)
			{
				pair.m_a = previousRow.at((column + (size / 2)) % size).m_a;
				
				// even column
				if(column % 2 == 0)
				{
					pair.m_b = previousRow.at((column + 1) % size).m_b;	
				}
				// odd column
				else if(column % 2 == 1)
				{
					pair.m_b = previousRow.at((column + size - 1) % size).m_b;	
				}
			}		
			// even row	
			else if(row % 2 == 0)
			{
				// even column
				if(column % 2 == 0)
				{
					pair.m_a = previousRow.at((column + 1) % size).m_a;
					pair.m_b = previousRow.at((column + size - 1) % size).m_b;
				}
				// odd column
				else if(column % 2 == 1)
				{
					pair.m_a = previousRow.at((column + size - 1) % size).m_a;
					pair.m_b = previousRow.at((column + 1) %  size).m_b;
				}
			}
			// odd row
			else if(row % 2 == 1)
			{
				// even column
				if(column % 2 == 0)
				{
					pair.m_a = previousRow.at((column + size - 1) % size).m_a;
					pair.m_b = previousRow.at((column + 1) %  size).m_b;
				}
				// odd column
				else if(column % 2 == 1)
				{
					pair.m_a = previousRow.at((column + 1) % size).m_a;
					pair.m_b = previousRow.at((column + size - 1) % size).m_b;
				}

			}

			newRow.push_back(pair);	
		}

		result.insert(result.end(), newRow.begin(), newRow.end());

		previousRow = newRow;
	}

	return result;
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
			
			tempResult.insert(tempResult.end(), newRow.begin(), newRow.end());

			currentFitness = fitnessNonSquare(tempResult, row + 2, size);
			
			++iterations;

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
			result.clear();
			result.insert(result.end(), initialRow.begin(), initialRow.end());
			previousRow.clear();
			previousRow.insert(previousRow.end(), initialRow.begin(), initialRow.end());
			row = -1;

			std::cout << "test" << std::endl;
		}
	}

	return result;
} 


int main(int argc, char ** argv)
{
	unsigned int size = std::atoi(argv[1]);

	std::vector<Pair> i = generateInitialRow(size);

	std::cout << std::endl;

	std::vector<Pair> result;
/*
	if(size % 2 == 1)
	{
		std::cout << "Odd" << std::endl << std::endl;
		result = solveForOdd(i);
	}
	else if(size % 4 == 0)
	{
		std::cout << "Muliple of Four" << std::endl << std::endl;
		result = solveForMultipleFour(i);
	}
	else	
	{
		std::cout << "No pattern found" << std::endl << std::endl;
		result = solveStochastic(i);
	}
*/

	solveStochastic(i);

	printGrid(result, size);

	std::cout << std::endl;

	/*
	unsigned int f = fitness(result, size);

	std::cout << "Fitness: " << f << std::endl;
*/

	unsigned int f = fitness_test(result, size);

	std::cout << "Fitness Test: " << f << std::endl << std::endl;

	/*
	std::vector<Pair> a = {{0,1}, {2,3}, {4,5}, {6,7}, {8,9}, {10,11},
				{10,3}, {0,5}, {2,7}, {4,9}, {6,8}, {8,1}};

	printGrid_test(a, 6);

	std::cout << "Fit: " << fitnessNonSquare(a, 2, 6) << std::endl;
	*/
	
	return 0;
}

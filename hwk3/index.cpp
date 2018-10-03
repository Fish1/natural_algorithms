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
	
	bestFitness = fitness(bestResult, size);

	unsigned int bestNeighborhoodFitness = bestFitness;

	unsigned int iterations = 0;

	unsigned int currentFitness = bestFitness;

	bestNeighborhoodFitness = currentFitness;

	std::vector<Pair> bestNeighborhoodResult = result;

	while(bestFitness != 0)
	{
		// FIND FIRST IMPROVEMENT FROM CHANGING THE NEIGHBORHOOD
		for(unsigned int run = 0; run < 10000; ++run)
		{
			unsigned int row = size - 1 - (rand() % neighborhood);
		
			// WIGGLE	
			{
				if(rand() % 2 == 0)
				{
					// swap two left values
					unsigned int swap_left_1 = rand() % size;	
					unsigned int swap_left_2 = rand() % size;
					unsigned int a_1 = result.at(swap_left_1 + size * row).m_a;
					unsigned int a_2 = result.at(swap_left_2 + size * row).m_a;
					result.at(swap_left_1 + size * row).m_a = a_2;
					result.at(swap_left_2 + size * row).m_a = a_1;
				}
				else
				{
					// swap two right values
					unsigned int swap_right_1 = rand() % size;
					unsigned int swap_right_2 = rand() % size;
					unsigned int b_1 = result.at(swap_right_1 + size * row).m_b;
					unsigned int b_2 = result.at(swap_right_2 + size * row).m_b;
					result.at(swap_right_1 + size * row).m_b = b_2;
					result.at(swap_right_2 + size * row).m_b = b_1;
				}
			}

			// GET CURRENT FITNESS
			currentFitness = fitness(result, size);
			++iterations;

			// IF CURRENT FITNESS IS THE BEST ONE FOR THE NEW NEIGHBORHOOD THEN KEEP NOTE
			// THIS SHOULD BE TRUE FOR THE FIRST ONE ALWAYS
			if(currentFitness < bestNeighborhoodFitness)
			{
				bestNeighborhoodFitness = currentFitness;
				bestNeighborhoodResult = result;
		
				// IF THE CURRENT FITNESS IS BETTER THAN THE GLOBAL
				// PRINT THE INFORMATION
				// NOTE THE BEST	
				if(currentFitness < bestFitness)
				{
					printGrid(result, size);
					std::cout << "Fitness: " << currentFitness << std::endl;
					std::cout << "Iterations: " << iterations << std::endl << std::endl;
					bestFitness = currentFitness;
					bestResult = result;
				}
			
				// KEEP GOING IF WE ARE FINDING BETTER SOLUTIONS	
				run = 0;
			}
		}

		// CHANGE THE NEIGHBORHOOD
		neighborhood += 1;
		// RESET THE BEST NEIGHBORHOOD 
		bestNeighborhoodFitness = -1;
		result = bestNeighborhoodResult;
		if(neighborhood == size)
		{
			neighborhood = 1;
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

	result = solveStochastic(i);

	printGrid(result, size);

	std::cout << std::endl;

	unsigned int f = fitness(result, size);

	std::cout << "Fitness Test: " << f << std::endl << std::endl;
	
	return 0;
}

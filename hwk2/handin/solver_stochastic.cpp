#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "utility.hpp"

std::vector<int> find_solution(std::string filename, unsigned int approx_completeness)
{
	std::ifstream file(filename);
		
	int stack_count;
	file >> stack_count;

	if(stack_count == 0)
	{
		return {};
	}

	int current_stack[stack_count];
	int target_stack[stack_count];

	std::vector<int> big_stacks;
	std::vector<int> small_stacks;
	std::vector<int> solution;

	// read in the current stacks
	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> current_stack[index];	
	}

	// read in the target stacks
	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> target_stack[index];	
	}
	
	// determine the stacks that are too large, and the stacks that are too small
	for(unsigned int index = 0; index < stack_count; ++index)
	{
		int current_size = current_stack[index];
		int target_size = target_stack[index];

		int difference = target_size - current_size;

		if(difference < 0)
		{
			big_stacks.push_back(index);
		}
		else if(difference > 0)
		{
			small_stacks.push_back(index);
		}
	}

	// if approx_completeness is zero then randomly choose between 1 and 500 + stack_count
	while(approx_completeness == 0)
	{
		unsigned int random_range = big_stacks.size() * big_stacks.size();
		// if random range is 0 then there is nothing to fix
		if(random_range == 0)
			return {};
		approx_completeness = rand() % random_range;
	}

	while(true)
	{
		// randomly have a chance of ending the solution
		if(rand() % approx_completeness == 0)
			return solution;
		
		// if there are no more big stacks to pickup from then end the solution
		if(big_stacks.size() == 0)
			return solution;

		// randomly select a big stack to pickup from	
		int big_stacks_random_index = rand() % big_stacks.size();	
		int random_pickup = big_stacks.at(big_stacks_random_index);

		// remove one from that stack	
		current_stack[random_pickup] -= 1;

		// add that stack to the solution
		solution.push_back(random_pickup);

		// randomly select a small stack to dropoff at 
		int small_stacks_random_index = rand() % small_stacks.size();
		int random_dropoff = small_stacks.at(small_stacks_random_index);		

		// add one to that stack
		current_stack[random_dropoff] += 1;
		
		// add that stack to the solution
		solution.push_back(random_dropoff);

		// if the pickup stack is now equal to its target
		// remove it from the list
		if(current_stack[random_pickup] == target_stack[random_pickup])
		{
			big_stacks.erase(big_stacks.begin() + big_stacks_random_index);
		}

		// if the dropoff stack is now equal to its target
		// remove it from the list
		if(current_stack[random_dropoff] == target_stack[random_dropoff])
		{
			small_stacks.erase(small_stacks.begin() + small_stacks_random_index);
		}	
	}

	return solution;
}

void mutate(std::vector<int> & solution)
{
	if(solution.size() == 0 || 
		solution.size() == 1 || 
		solution.size() == 2)
	{
		return;
	}

	// select a random stack
	int i = rand() % solution.size();
	
	// select a random stack, but if i is even then select an even
	// 	if i is odd then select an odd
	int j = ((rand() % ((solution.size() - 2) / 2)) * 2) + (i % 2);

	// swap the values at the locations
	int i_val = solution.at(i);
	solution.at(i) = solution.at(j);
	solution.at(j) = i_val;
}


int main(int argc, char ** argv)
{
	srand(clock());

	std::string filename = argv[1];
	unsigned int completeness;	

	if(argc == 2)
	{
		filename = argv[1];
		completeness = 0;	
	}
	else if(argc == 3)
	{
		filename = argv[1];
		completeness = std::stoi(argv[2]);
	}
	else
	{
		std::cout << "bad arguments" << std::endl;
		std::cout << "./solver <file> <completeness>" << std::endl;
		return 1;
	}

	std::cout << "From File: " << filename << std::endl << std::endl;
	
	uint64_t best_fitness = UINT64_MAX;
	std::vector<int> best_solution;
	std::string best_op_solution;

	uint32_t fitness_calls = 0;

	for(uint32_t index = 0; index < 1000; ++index)
	{
		// generate a random solution
		std::vector<int> solution = find_solution(filename, completeness);

		for(uint32_t index = 0; index < 100; ++index)
		{
			mutate(solution);

			std::string op_solution = pairs_to_ops(solution);
			uint64_t current_fitness = fitness(op_solution, filename);
			fitness_calls += 1;

			// if current fitness is better than the best
			// replace the best with the current
			if(current_fitness < best_fitness)
			{
				best_fitness = current_fitness;
				best_solution = solution;
				best_op_solution = op_solution;
			}
		
			// print some data at intervals	
			if(fitness_calls == 1000 || fitness_calls == 10000 ||
				fitness_calls == 100000)
			{
				std::cout << "Fitness: " << best_fitness << std::endl;
				std::cout << "Solution: " << best_op_solution << std::endl; 
				std::cout << std::endl;
			}	
		}
	}

	std::cout << std::endl;

	return 0;
}

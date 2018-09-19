#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "utility.hpp"

struct Solution_Data 
{
	std::string solution_1000;
	uint64_t fitness_1000;

	std::string solution_10000;
	uint64_t fitness_10000;

	std::string solution_100000;
	uint64_t fitness_100000;
};

// find a random solution, by only picking from big stacks and dropping on small stacks
// stop randomly or until all the stacks are at target height
std::string find_solution(std::string filename, unsigned int approx_completeness)
{
	std::ifstream file(filename);
		
	int stack_count;

	file >> stack_count;

	approx_completeness += (stack_count * stack_count);

	int current_stack[stack_count];

	int target_stack[stack_count];

	std::vector<int> big_stacks;
	std::vector<int> small_stacks;

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> current_stack[index];	
	}

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> target_stack[index];	
	}

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
	
	std::stringstream result;

	unsigned int location = 0;
	
	int move_count = 0;
	
	int stop_power = 0;
	
	while(true)
	{
		if(approx_completeness == 0)
			return result.str();
		if(rand() % approx_completeness == 0)
		{
			return result.str();
		}

		if(big_stacks.size() == 0)
		{
			return result.str();
		}
	
		int big_stacks_random_index = rand() % big_stacks.size();	
		int random_pickup = big_stacks.at(big_stacks_random_index);
	
		current_stack[random_pickup] -= 1;
		result << random_pickup << " ";

		++move_count;

	/*	
		if(approx_completeness == 0)
			return result.str();
		if(rand() % approx_completeness == 0)
		{
			return result.str();
		}
	*/

		int small_stacks_random_index = rand() % small_stacks.size();
		int random_dropoff = small_stacks.at(small_stacks_random_index);		

		current_stack[random_dropoff] += 1;
		result << random_dropoff << " ";

	//	++move_count;

		if(current_stack[random_pickup] == target_stack[random_pickup])
		{
			big_stacks.erase(big_stacks.begin() + big_stacks_random_index);
		}

		if(current_stack[random_dropoff] == target_stack[random_dropoff])
		{
			small_stacks.erase(small_stacks.begin() + small_stacks_random_index);
		}	
	}

	return result.str();
}

std::string mutate(std::string thing)
{
	std::vector<int> current_solution;

	std::stringstream ss(thing);
	
	int number = 0;
	while(ss >> number)
	{
		current_solution.push_back(number);
	}

	if(current_solution.size() == 0)
		return "X";

	int i = rand() % current_solution.size();

	int j = ((rand() % ((current_solution.size() - 2) / 2)) * 2) + (i % 2);

	int i_val = current_solution[i];
	current_solution[i] = current_solution[j];
	current_solution[j] = i_val;


	std::stringstream result;
	for(int i : current_solution)
	{
		result << i;
		result << " ";
	}

	return result.str();
}

// this function will attempt to find a better solution by running the
// random solution algorithm many times
struct Solution_Data find_best_solution(std::string file, unsigned int run_times, unsigned int approx_completeness)
{
	struct Solution_Data result;

	std::string best_solution = "X";
	uint64_t best_fitness = fitness("X", file);

	for(unsigned int index = 1; index <= run_times; ++index)
	{
		std::string pair_solution;
		
		if(approx_completeness == 0)
		{
			pair_solution = find_solution(file, (rand() % 199) + 1);
		}
		else
		{
			pair_solution = find_solution(file, approx_completeness);
		}

		std::string operation_solution = pairs_to_ops(pair_solution);

		uint64_t fit = fitness(operation_solution, file);

		if(fit < best_fitness)
		{
			best_fitness = fit;
			best_solution = operation_solution;
		}
		
		if(index == 1000)
		{
			result.fitness_1000 = best_fitness;
			result.solution_1000 = best_solution;		
		}
		else if(index == 10000)
		{
			result.fitness_10000 = best_fitness;
			result.solution_10000 = best_solution;
		}
		else if(index == 100000)
		{
			result.fitness_100000 = best_fitness;
			result.solution_100000 = best_solution;
		}
	}

	return result;
}

int main(int argc, char ** argv)
{
	srand(clock());

	std::string filename = argv[1];
/*
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

	struct Solution_Data data = find_best_solution(filename, 100000, completeness);

	std::cout << "Runs = 1000" << std::endl;
	std::cout << "Fitness = " << data.fitness_1000 << std::endl;
	std::cout << "Solution = " << data.solution_1000 << std::endl << std::endl;

	std::cout << "Runs = 10000" << std::endl;
	std::cout << "Fitness = " << data.fitness_10000 << std::endl;
	std::cout << "Solution = " << data.solution_10000 << std::endl << std::endl;

	std::cout << "Runs = 100000" << std::endl;
	std::cout << "Fitness = " << data.fitness_100000 << std::endl;
	std::cout << "Solution = " << data.solution_100000 << std::endl;
*/
	std::string s = find_solution(filename, 100);

	std::cout << s << std::endl;

	std::cout << std::endl;
	
	for(unsigned int index = 0; index < 100000; ++index)
	{
		s = mutate(s);
		std::cout << s << std::endl;
	}

	for(unsigned int index = 0; index < 100; ++index)
	{
		std::string solution = find_solution(filename, 100);

		for(unsigned int index = 0; index < 1000; ++index)
		{
			std::string op_solution = pairs_to_ops(solution);
			int fit = fitness(op_solution, filename);
		}
	}
	return 0;
}

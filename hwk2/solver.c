#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstring>

std::string pairs_to_ops(std::string pairs)
{
	std::stringstream ss(pairs);
	std::stringstream result; 

	unsigned int pickup;
	unsigned int dropoff;
	unsigned int location = 0;

	while(ss >> pickup && ss >> dropoff)
	{
		int difference = pickup - location;
		char buffer_pickup[std::abs(difference)];
		
		if(difference < 0)
		{
			memset(buffer_pickup, 'L', sizeof(char) * std::abs(difference));		
			result.write(buffer_pickup, std::abs(difference));
		}
		else if(difference > 0)
		{
			memset(buffer_pickup, 'R', sizeof(char) * std::abs(difference));		
			result.write(buffer_pickup, std::abs(difference));
		}
		
		result << "P";

		location += difference;

		difference = dropoff - location;
	
		char buffer_dropoff[std::abs(difference)];
		
		if(difference < 0)
		{
			memset(buffer_dropoff, 'L', sizeof(char) * std::abs(difference));		
			result.write(buffer_dropoff, std::abs(difference));
		}
		else if(difference > 0)
		{
			memset(buffer_dropoff, 'R', sizeof(char) * std::abs(difference));		
			result.write(buffer_dropoff, std::abs(difference));
		}
		
		result << "D";

		location += difference;
	}

	result << "X";

	return result.str();
}

std::string find_solution(std::string filename, unsigned int stop_power)
{
	std::ifstream file(filename);
		
	int stack_count;

	file >> stack_count;

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
	
	while(true)
	{
		if(rand() % stop_power == 0)
		{
			return result.str();
		}

		if(big_stacks.size() == 0)
			return result.str();
	
		int big_stacks_random_index = rand() % big_stacks.size();	
		int random_pickup = big_stacks.at(big_stacks_random_index);
	
		current_stack[random_pickup] -= 1;
		result << random_pickup << " ";

		int small_stacks_random_index = rand() % small_stacks.size();
		int random_dropoff = small_stacks.at(small_stacks_random_index);		

		current_stack[random_dropoff] += 1;
		result << random_dropoff << " ";

		// check if they should be removed from large_stacks or small_stacks
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

long fitness(std::string solution, std::string filename) 
{
	int stacks[100] = {0};
	int target[100] = {0};

	int pos = 0;
	long operation_count = 0;

	long score;
	int stack_count;
	bool holding = false;
	int i;
	char c;

	char str[] = "Your score is: ";

	FILE *f;

	f = fopen(filename.c_str(), "r");
	if(!f) 
	{
	    exit(EXIT_FAILURE);
	}

	fscanf(f, "%d", &stack_count);

	for(i = 0; i < stack_count; i++) {
	    fscanf(f, "%d", &(stacks[i]));
	}

	for(i = 0; i < stack_count; i++) {
	    fscanf(f, "%d", &(target[i]));
	}

	fclose(f);

	for(char c : solution)
	{
	    operation_count++;
	    switch(c) {
	    case 'L':
	        if(pos > 0) {
	            pos--;
	        }
	        break;
	    case 'R':
	        if(pos < (stack_count - 1)) {
	            pos++;
	        }
	        break;
	    case 'P':
	        if(!holding && stacks[pos] > 0) {
	            stacks[pos]--;
	            holding = true;
	        }
	        break;
	    case 'D':
	        if(holding) {
	            stacks[pos]++;
	            holding = false;
	        }
	        break;
	    default:
	        operation_count--;
	        break;
	    }

		if(c == 'X')
			break;
	}

	score = operation_count;
	for(i = 0; i < stack_count; i++) 
	{
		long dif = stacks[i] - target[i];
		dif = dif >= 0 ? dif : -dif;
		score += dif * dif * dif;
	}

	return score;
}

struct Solution_Data 
{
	std::string operations;
	long fitness;
};

struct Solution_Data find_best_solution(std::string file, unsigned int run_times, unsigned int stop_power)
{
	std::string best_solution = "X";
	long best_fitness = fitness("X", file);

	for(unsigned int index = 0; index < run_times; ++index)
	{
		std::string pair_solution = find_solution(file, stop_power);
		std::string operation_solution = pairs_to_ops(pair_solution);

		long fit = fitness(operation_solution.c_str(), file);

		if(fit < best_fitness)
		{
			best_fitness = fit;
			best_solution = operation_solution;
		}		
	}

	return {best_solution, best_fitness};
}

int main(int argc, char ** argv)
{
	srand(clock());

	// test for stop powers between 1 and 200
	for(unsigned int stop_power = 2; stop_power <= 200; ++stop_power)
	{
		unsigned int test_times = 10;

		unsigned int total_fitness = 0;
		// test each stop power 1000 times	
		for(unsigned int index = 0; index < test_times; ++index)
		{
			unsigned int run_times = 10000;
			struct Solution_Data sd = find_best_solution(argv[1], run_times, stop_power);
					
			std::cout << "runs = " << run_times << "; " << " stop_power = " << stop_power << "; ";	
			std::cout << "fitness = " << sd.fitness << std::endl;
			
			total_fitness += sd.fitness;
		}

		std::cout << "stop_power = " << stop_power << " average_fitness = " << (double)total_fitness / (double)test_times << std::endl << std::endl;
	}
}

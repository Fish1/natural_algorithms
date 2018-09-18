#include <stdio.h>

#include <stdlib.h>

#include <fstream>

#include <iostream>

#include <sstream>

#include <vector>

#include <cmath>

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

		for(unsigned int index = 0; index < std::abs(difference); ++index)
		{
			if(difference < 0)
			{
				result << "L";
			}
			else if(difference > 0)
			{
				result << "R";
			}
		}

		result << "P";

		location += difference;

		difference = dropoff - location;
		
		for(unsigned int index = 0; index < std::abs(difference); ++index)
		{
			if(difference < 0)
			{
				result << "L";
			}
			else if(difference > 0)
			{
				result << "R";
			}
		}
		
		result << "D";

		location += difference;
	}

	result << "X";

	return result.str();
}

std::string find_solution(std::string filename)
{
	std::ifstream file(filename);
		
	int stack_count;

	file >> stack_count;

	int current_stack[stack_count];

	int target_stack[stack_count];

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> current_stack[index];	
	}

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		file >> target_stack[index];	
	}

	for(int i : current_stack)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for(int i : target_stack)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	
	std::stringstream result;

	unsigned int location = 0;

	bool run = true;
	
	while(run == true)
	{
		int random_pickup = rand() % stack_count;
	
		int random_pickup_search = 0;
	
		// dont pickup stacks that are too short
		while(current_stack[random_pickup] <= target_stack[random_pickup])
		{
			random_pickup = rand() % stack_count;		

			random_pickup_search += 1;

			if(random_pickup_search == 10000)
			{
				run = false;
				break;
			}
		}
	
		if(run == false)
			break;
	
		current_stack[random_pickup] -= 1;
		result << random_pickup << " ";

		int random_dropoff = rand() % stack_count;		

		//dont drop at a stack that is too big
		while(current_stack[random_dropoff] >= target_stack[random_dropoff])
		{
			random_dropoff = rand() % stack_count;	
		}

		current_stack[random_dropoff] += 1;

		result << random_dropoff << " ";
	}

	return result.str();
}

int main(int argc, char ** argv)
{
	srand(time(NULL));

	std::string pair_solution = find_solution(argv[1]);
	std::string operation_solution = pairs_to_ops(pair_solution);

//	std::cout << operation_solution << std::endl;

	std::stringstream system_call;

	system_call << "echo ";
	system_call << operation_solution;
	system_call << " | ./fitness ";
	system_call << argv[1];		

//	std::cout << system_call.str() << std::endl;

	system(system_call.str().c_str());
}

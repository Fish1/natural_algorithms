#include <iostream>

#include "utility.hpp"

std::string solve(std::string filename)
{
	std::ifstream fs(filename);

	int64_t stack_count;
	// get the stack count
	fs >> stack_count;

	int64_t current_stacks[stack_count];
	int64_t target_stacks[stack_count];	

	// read current stacks
	for(size_t index = 0; index < stack_count; ++index)
	{
		fs >> current_stacks[index];
	}

	// read target stack	
	for(size_t index = 0; index < stack_count; ++index)
	{
		fs >> target_stacks[index];
	}

	unsigned int last_action_index = 0;
	unsigned int times_passing_last_action_index = 0;
	unsigned int current_location = 0;
	bool right = true;
	bool holding = false;
	std::stringstream result;

	// if you pass the same spot that an action was completed twice, then stop running
	while(times_passing_last_action_index < 2)
	{
		// determine if to pickup
		if(holding == false)
		{
			int64_t difference = current_stacks[current_location] - target_stacks[current_location];
			bool pickup = difference > 0;
			
			if(pickup)
			{
				result << "P";
				last_action_index = current_location;
				times_passing_last_action_index = 0;
				current_stacks[current_location] -= 1;
				holding = true;
			}
		}

		// determine if to drop
		if(holding == true)
		{
			int64_t difference = current_stacks[current_location] - target_stacks[current_location];
			bool dropoff = difference < 0;
			
			if(dropoff)
			{
				result << "D";
				last_action_index = current_location;
				times_passing_last_action_index = 0;
				current_stacks[current_location] += 1;
				holding = false;
			}
		}

		// determine direction to move	
		if(right == true && current_location == stack_count - 1)
		{
			right = false;
		}
		else if(right == false && current_location == 0)
		{
			right = true;
		}

		// move
		if(right)
		{
			result << "R";
			current_location += 1;		
		}
		else
		{
			result << "L";
			current_location -= 1;
		}

		// if ontop of a past index, record it
		if(current_location == last_action_index)
		{
			times_passing_last_action_index += 1;
		}		
	}

	return result.str();
}

int main(int argc, char ** argv)
{
	std::string filename = std::string(argv[1]);

	std::string solution = solve(filename);		
	
	int fit = fitness(solution, filename);
	
	std::cout << "Fitness: " << fit << std::endl;
	
	std::cout << "Solution: " << solution << std::endl;

	return 0;
}

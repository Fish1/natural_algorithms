#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

/*
	reimplementation of confers fitness.c program
*/
uint64_t fitness(std::string solution, std::string filename)
{
	int stacks[100] = {0};
	int target[100] = {0};

	int position = 0;
	uint64_t operation_count = 0;
	
	unsigned int stack_count;
	bool holding = false;
	
	std::ifstream infile(filename);

	infile >> stack_count;

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		infile >> stacks[index];
	}

	for(unsigned int index = 0; index < stack_count; ++index)
	{
		infile >> target[index];
	}

	infile.close();

	for(char c : solution)
	{
		++operation_count;

		if(c == 'X')
			break;

		switch(c)
		{
			case 'L':
				if(position > 0)
					--position;
				break;
			case 'R':
				if(position < (stack_count - 1))
					++position;
				break;
			case 'P':
				if(!holding && stacks[position] > 0)
				{
					--stacks[position];
					holding = true;
				}
				break;	
			case 'D':
				if(holding)
				{
					++stacks[position];
					holding = false;
				}
				break;
			default:
				--operation_count;
				break;
		}
	}

	uint64_t score = operation_count;
	for(unsigned int index = 0; index < stack_count; ++index)
	{
		int64_t dif = stacks[index] - target[index];
		dif = dif >= 0 ? dif : -dif;
		score += dif * dif * dif;
	}
	
	return score;
}

std::string pairs_to_ops(std::string pairs)
{
	std::stringstream ss(pairs);
	std::stringstream result; 
	
	int location = 0;

	while(true)
	{
		int pickup;

		if(ss >> pickup)
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
		}
		else
		{
			break;
		}
	
		int dropoff;

		if(ss >> dropoff)
		{
			int difference = dropoff - location;
		
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
		else
		{
			break;
		}
	}

	result << "X";

	return result.str();
}

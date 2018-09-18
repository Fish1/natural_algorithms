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

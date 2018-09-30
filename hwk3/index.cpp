#include <iostream>
#include <vector> 
class Pair
{
public:
	unsigned int a;
	unsigned int b;
};

Pair getElement(std::vector<Pair> data, unsigned int n, unsigned int x, unsigned int y)
{
	return data.at(x * n + y);
}

int fitness(std::vector<Pair> data, unsigned int rowLength)
{
	return 0;	
}

bool repeats(std::vector<Pair> data)
{
	for(unsigned int indexA = 0; indexA < data.size(); ++indexA)
	{
		Pair p = data.at(indexA);

		for(unsigned int indexB = 0; indexB < data.size(); ++indexB)
		{
			if(indexB == indexA)
				continue;

			Pair p2 = data.at(indexB);	

			if(p.a == p2.a && p.b == p2.b)
			{
				return true;
			}
		}
	}

	return false;
}

std::vector<Pair> generateNextRow(std::vector<Pair> row)
{ 
	std::vector<Pair> result;
	
	// get the last element and put it at the begining
	Pair p = {row.at(row.size() - 1).a, row.at(1).b};
	result.push_back(p);

	// the next element is of the row before it, don't add the last one because we already did
	for(unsigned int index = 0; index < row.size() - 1; ++index)
	{
		Pair p = {row.at(index).a, 0};
		result.push_back(p);
	}

	// now for the right side
	// the next element is of the row after it
	for(unsigned int index = 1; index < row.size() - 1; ++index)
	{
		result.at(index).b = row.at(index + 1).b;
	}

	result.at(result.size() - 1).b = row.at(0).b;


	return result;
}

// move left row down
std::vector<Pair> generateNextRowLeft(std::vector<Pair> row)
{
	std::vector<Pair> result;
	
	// get the last element and put it at the begining
	Pair p = {row.at(row.size() - 1).a, row.at(0).b};
	result.push_back(p);

	// the next element is of the row before it, don't add the last one because we already did
	for(unsigned int index = 0; index < row.size() - 1; ++index)
	{
		Pair p = {row.at(index).a, row.at(index + 1).b};
		result.push_back(p);
	}

	return result;
}

// move right row up
std::vector<Pair> generateNextRowRight(std::vector<Pair> row)
{
	std::vector<Pair> result;
	
	// the next element is of the row before it, don't add the last one because we already did
	for(unsigned int index = 0; index < row.size() - 1; ++index)
	{
		Pair p = {row.at(index).a, row.at(index + 1).b};
		result.push_back(p);
	}

	Pair p = {row.at(row.size() - 1).a, row.at(0).b};
	result.push_back(p);

	return result;

}

void print(std::vector<Pair> data)
{
	for(Pair p : data)
	{
		std::cout << "\t" <<  p.a << ":" << p.b << " ";
	}

	std::cout << std::endl;
}

void solveEvenN(unsigned int n)
{
	std::vector<Pair> endResult;
	
	std::vector<Pair> row;

	for(unsigned int index = 0; index < n; ++index)
	{
		row.push_back({index*2, (index*2)+1});	
	}

	print(row);

	endResult.insert(endResult.end(), row.begin(), row.end());

	for(unsigned int index = 0; index < row.size() - 1; ++index)
	{

//		row = generateNextRowRight(row);
//		row = generateNextRowRight(row);
//		row = generateNextRowRight(row);
	
//		if(index == (n/2) - 1)
//			row = generateNextRowRight(row);
		
		
//		row = generateNextRowLeft(row);
		row = generateNextRow(row);
//		row = generateNextRow(row);
//		row = generateNextRow(row);

		print(row);

		endResult.insert(endResult.end(), row.begin(), row.end());
	}

	std::cout << "Repeats: " << repeats(endResult) << std::endl;
}

void solveOddN(unsigned int n)
{
	std::vector<Pair> endResult;
	
	std::vector<Pair> row;

	for(unsigned int index = 0; index < n; ++index)
	{
		row.push_back({index*2, (index*2)+1});	
	}

	print(row);

	endResult.insert(endResult.end(), row.begin(), row.end());

	for(unsigned int index = 0; index < row.size() - 1; ++index)
	{
		row = generateNextRow(row);
		print(row);

		endResult.insert(endResult.end(), row.begin(), row.end());
	}

	std::cout << "Repeats: " << repeats(endResult) << std::endl;
}

int main(int argc, char ** argv)
{
	unsigned int n = std::stoi(argv[1]);

	if(n % 2 == 0)
	{
		solveEvenN(n);
	}
	else if(n % 2 == 1)
	{
		solveOddN(n);
	}

	return 0;

}

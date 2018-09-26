#include <iostream>

#include <vector>

// 0 0 0 1
// 1 0 2 3
// 2 0 4 5

// 0 1 2 4
// 1 1 0 5
// 2 1 1 3

// 0 2 3 5
// 1 2 1 4
// 2 2 0 2

/*
0 1
2 3
4 5

4 3
0 5
2 1

2 5
4 1
0 3
*/

/*
0 1
2 3
4 5 
6 7

6 3
0 5
2 7
4 1

4 5
6 7
0 1
2 3

2 7
4 1
6 3
0 5
*/

int fitness(unsigned int , unsigned int n)
{
		

	return 0;
}

class Pair
{
public:
	unsigned int a;
	unsigned int b;
};

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

	result.at(result.size() - 1


	return result;
}

void print(std::vector<Pair> data)
{
	for(Pair p : data)
	{
		std::cout << p.a << ":" << p.b << " ";
	}

	std::cout << std::endl;
}

int main(void)
{
	std::vector<Pair> row = {{0,1}, {2,3}, {4,5}};
	print(row);

	row = generateNextRow(row);
	print(row);
}

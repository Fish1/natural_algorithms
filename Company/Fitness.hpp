#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <vector>

#include "Pair.hpp"

// expects all pairs in a single vector
unsigned int fitness(std::vector<Pair> data, unsigned int size)
{
	unsigned int f = 0;

	// count the rows for violations of repeating values	
	for(unsigned int y = 0; y < size; ++y)
	{
		for(unsigned int element = 0; element < 2 * size; ++element)
		{
			bool hasElement = false;

			for(unsigned int x = 0; x < size; ++x)
			{
				if(data.at(x + size * y).m_a == element
					|| data.at(x + size * y).m_b == element)
				{
					hasElement = true;
					break;
				}
			}
		
			if(hasElement == false)
				f += 1;	
		}
	}

	// count the columns for violations of repeating values
	for(unsigned int x = 0; x < size; ++x)
	{
		for(unsigned int element = 0; element < 2 * size; ++element)
		{
			bool hasElement = false;	
			for(unsigned int y = 0; y < size; ++y)
			{
				if(data.at(x + size * y).m_a == element 
					|| data.at(x + size * y).m_b == element)
				{
					hasElement = true;
					break;	
				}
			}
	
			if(hasElement == false)
				f += 1;
		}
	}

	// count the repeating pairs
	for(unsigned int pairLeft = 0; pairLeft < 2 * size - 1; ++pairLeft)
	{
		for(unsigned int pairRight = pairLeft + 1; pairRight < 2 * size; ++pairRight)
		{
			Pair pairToCheck(pairLeft, pairRight);
			unsigned int pCount = 0;

			for(unsigned int y = 0; y < size; ++y)
			{
				for(unsigned int x = 0; x < size; ++x)
				{
					Pair & pairAtLocation = data.at(x + size * y);
					
					if(pairAtLocation == pairToCheck)
					{
						pCount += 1;	
					}					
				}
			}

			if(pCount >= 2)
			{
				f += pCount - 1;
			}
		}
	}
	
	return f;
}

unsigned int fitness_test(std::vector<Pair> data, unsigned int size)
{
	unsigned int f = 0;

	// count the rows for violations of repeating values	
	for(unsigned int y = 0; y < size; ++y)
	{
		for(unsigned int element = 0; element < 2 * size; ++element)
		{
			bool hasElement = false;

			for(unsigned int x = 0; x < size; ++x)
			{
				if(data.at(x + size * y).m_a == element
					|| data.at(x + size * y).m_b == element)
				{
					hasElement = true;
					break;
				}
			}
		
			if(hasElement == false)
				f += 1;	
		}
	}

	// count the columns for violations of repeating values
	for(unsigned int x = 0; x < size; ++x)
	{
		for(unsigned int element = 0; element < 2 * size; ++element)
		{
			bool hasElement = false;	
			for(unsigned int y = 0; y < size; ++y)
			{
				if(data.at(x + size * y).m_a == element 
					|| data.at(x + size * y).m_b == element)
				{
					hasElement = true;
					break;	
				}
			}
	
			if(hasElement == false)
				f += 1;
		}
	}

	// get first element count all elements of the same,
	// if you find same elements remove them

	unsigned int duplicatedPairs = 0;

	while(data.size() > 0)
	{
		Pair pairCheck = data.at(0);
		
		data.erase(data.begin());

		for(unsigned int index = 0; index < data.size(); ++index)
		{
			Pair pairAtLocation = data.at(index);

			if(pairAtLocation == pairCheck)
			{
				duplicatedPairs += 1;
				data.erase(data.begin() + index);
				--index;
			}	
		}	
	}	

	f += duplicatedPairs;

	return f;
}


unsigned int fitnessNonSquare(std::vector<Pair> data, unsigned int rows, unsigned int columns)
{
	unsigned int f = 0;

	// count the rows for violations of repeating values	
	for(unsigned int y = 0; y < rows; ++y)
	{
		for(unsigned int element = 0; element < 2 * columns; ++element)
		{
			bool hasElement = false;

			for(unsigned int x = 0; x < columns; ++x)
			{
				if(data.at(x + columns * y).m_a == element
					|| data.at(x + columns* y).m_b == element)
				{
					hasElement = true;
					break;
				}
			}
		
			if(hasElement == false)
				f += 1;	
		}
	}

	// count the columns for violations of repeating values
	// modified because rememebr we don't have all rows
	for(unsigned int x = 0; x < columns; ++x)
	{
		for(unsigned int element = 0; element < 2 * columns; ++element)
		{
			unsigned int elementCount = 0;
			for(unsigned int y = 0; y < rows; ++y)
			{
				if(data.at(x + columns * y).m_a == element 
					|| data.at(x + columns * y).m_b == element)
				{
					elementCount += 1;
				}
			}
				

			if(elementCount >= 2)
			{
				f += elementCount - 1;
			}	
		}
	}

	// get first element count all elements of the same,
	// if you find same elements remove them

	unsigned int duplicatedPairs = 0;

	while(data.size() > 0)
	{
		Pair pairCheck = data.at(0);
		
		data.erase(data.begin());

		for(unsigned int index = 0; index < data.size(); ++index)
		{
			Pair pairAtLocation = data.at(index);

			if(pairAtLocation == pairCheck)
			{
				duplicatedPairs += 1;
				data.erase(data.begin() + index);
				--index;
			}	
		}	
	}

	f += duplicatedPairs;

	return f;
}

#endif

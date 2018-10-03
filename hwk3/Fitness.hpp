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

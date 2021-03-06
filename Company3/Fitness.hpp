#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <vector>

#include "Pair.hpp"

// expects all pairs in a single vector
unsigned int fitness(const std::vector<Pair> & data, unsigned int size)
{
	unsigned int f = 0;

	for(unsigned int element = 0; element < 2 * size; ++element)
	{
		// count the rows for violations of repeating values	
		for(unsigned int y = 0; y < size; ++y)
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

		// count the columns for violations of repeating values
		for(unsigned int x = 0; x < size; ++x)
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

	unsigned int duplicatedPairs = 0;

	for(unsigned int index = 0; index < data.size(); ++index)
	{
		Pair pairCheck = data.at(index);

		for(unsigned int index2 = index + 1; index2 < data.size(); ++index2)
		{
			Pair pairAtLocation = data.at(index2);

			if(pairAtLocation == pairCheck)
			{
				duplicatedPairs += 1;
			}
		}
	}

	f += duplicatedPairs;

	return f;
}


#endif

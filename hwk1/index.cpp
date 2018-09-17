// Jacob Enders
// HWK 1
// Natural Algorithms

#include <iostream>

#include <math.h>

#include <float.h>

#include <stdlib.h>

// this is the function that we are trying to find the max for
double f(double * coords, unsigned int dim)
{
	double sum1 = 0;

	for(unsigned int index = 1; index <= dim; ++index)
	{
		sum1 += pow((coords[index - 1] + pow(-1.0, index) * (index % 4)), 2);
	}

	double sum2 = 0;

	for(unsigned int index = 1; index <= dim; ++index)
	{
		sum2 += pow(coords[index - 1], index);	
	}

	double result = (-1.0) * sqrt(sum1) + sin(sum2);

	return result;
}

// get a random double between min an max
double random(double min, double max)
{
	double difference = max - min;

	double random_number = rand() / (double)RAND_MAX;
	random_number *= difference;

	return min + random_number;
}

// find the maximum value of f with dimension dim
void find_max(unsigned int dim)
{
	double best = -DBL_MAX;
	double best_coords[dim];
	double function_calls = 0;

	double coords [dim];
	const double step = 1.0;

	// this loop is for the number of times to jump to a random spot
	for(unsigned int index = 0; index < 100; ++index)
	{
		// select a random spot to search
		for(unsigned int index = 0; index < dim; ++index)
		{
			coords[index] = random(-8.0, 8.0);
		}
		
		// twitch around 1000 times
		for(unsigned int index = 0; index < 1000; ++index)
		{
			// get the result at the spot
			double result = f(coords, dim);
			function_calls += 1;

			// if this spot is greater than the previous greatest spot
			// record this spot as the greatest spot
			if(result > best)
			{
				best = result;

				for(unsigned int index = 0; index < dim; ++index)
				{
					best_coords[index] = coords[index];
				}
			}

			// if the function has been called 1000, 10000 or 100000 times
			// then print information
			if(function_calls == 1000 || function_calls == 10000 || function_calls == 100000)
			{
				std::cout << "--- " << function_calls << " ---" << std::endl;
				std::cout << "Best Value = " << best << std::endl;
				std::cout << "Best Coords = ";
				for(unsigned int index = 0; index < dim; ++index)
				{
					std::cout << best_coords[index] << ", ";
				}
				std::cout << std::endl;
			}	
			
			// twitch around a little	
			//for(unsigned int index = 0; index < 1; ++index)
			{
				for(unsigned int index = 0; index < dim; ++index)
				{
					double old = coords[index];
					coords[index] = coords[index] + random(-step, step);
					if(coords[index] < -8.0 || coords[index] > 8.0)
					{
						coords[index] = old;
						--index;
					}
				}	
			}
		}
	}
}
        
int main(void)
{
	srand(time(NULL));

	std::cout << std::endl << "Dim 1 " << std::endl;
	find_max(1);
	std::cout << std::endl << "Dim 2 " << std::endl;
	find_max(2);
	std::cout << std::endl << "Dim 3 " << std::endl;
	find_max(3);
	std::cout << std::endl << "Dim 5 " << std::endl;
	find_max(5);
	std::cout << std::endl << "Dim 8 " << std::endl;
	find_max(8);
	std::cout << std::endl << "Dim 13 " << std::endl;
	find_max(13);
}

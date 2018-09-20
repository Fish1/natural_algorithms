#include <stdio.h>

#include <math.h>

#include <float.h>

#include <stdlib.h>

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

double bestImprovement(double x)
{
	do
	{
		int a = 1;
	} while(a == 1);

	return 1;

}

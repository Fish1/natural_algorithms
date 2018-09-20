#include <iostream>

#include <cmath>

#include "LocalRandomSearch.hpp"

#include "Utilities.hpp"

LocalRandomSearch::LocalRandomSearch(std::vector<Coordinate> initial)
{
	m_currentList = initial;
	m_currentPerimeter = calculatePerimeter(m_currentList);

	m_bestList = initial;
	m_bestPerimeter = m_currentPerimeter;

	m_totalIterations = 0;

	m_swapsSinceImprovement = 0;
	
	m_heat = 0;
	m_heatHelp = 0;
}

void LocalRandomSearch::run()
{
	++m_totalIterations;

	if(m_swapsSinceImprovement == 1000)
	{
		randomSwap(m_currentList);
		
		double m_oldPerimeter = m_currentPerimeter;	
		m_currentPerimeter = calculatePerimeter(m_currentList);

		if(m_currentPerimeter < m_bestPerimeter)
		{
			m_bestList = m_currentList;
			m_bestPerimeter = m_currentPerimeter;
		}
		
		if(m_currentPerimeter < m_oldPerimeter)
		{
			m_swapsSinceImprovement = 0;
		}
	}
	else
	{
		double currentPerimeter = m_currentPerimeter;
		
		std::vector<Coordinate> tmpCoords = m_currentList;
		randomSwap(tmpCoords);
		double tmpPerimeter = calculatePerimeter(tmpCoords);
	
		double perimeter = currentPerimeter;
	
		if(rand() % 100 < m_heat)
		{
			m_currentList = tmpCoords;
			m_currentPerimeter = tmpPerimeter;
			m_swapsSinceImprovement = 0;
			perimeter = tmpPerimeter;		
		}
		else if(tmpPerimeter < currentPerimeter)
		{
			m_currentList = tmpCoords;
			m_currentPerimeter = tmpPerimeter;
			m_swapsSinceImprovement = 0;
			perimeter = tmpPerimeter;		

		}
		else
		{
		//	m_swapsSinceImprovement += 1;

		}

		m_heatHelp += 

/*		
		m_heatHelp += 1;
		m_heat = (std::sin(((double)m_heatHelp / 1000000.0) * 2.0 * 3.1415) + 1) * 50.0;
		if(m_heatHelp == 1000000)
			m_heatHelp = 0;
*/
		m_heat = std::sin((double)m_totalIterations) + sin((double)m_totalIterations / 10000.0) * 100.0;
		m_heat -= 30.0f;

		if(perimeter < m_bestPerimeter)
		{
			m_bestPerimeter = m_currentPerimeter;
			m_bestList = m_currentList;
			std::cout << "Iteration: " << m_totalIterations
			<< " Perimeter: " << m_bestPerimeter<< std::endl;
		}
	}
}

std::vector<Coordinate> & LocalRandomSearch::getBestList()
{
	return m_bestList;
}

uint64_t LocalRandomSearch::getTotalIterations()
{
	return m_totalIterations;
}

double LocalRandomSearch::getHeat()
{
	return m_heat;
}

double LocalRandomSearch::getBestPerimeter()
{
	return m_bestPerimeter;
}

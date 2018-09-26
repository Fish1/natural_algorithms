#include <iostream>

#include <cmath>

#include <algorithm>

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

	m_distribution = std::uniform_real_distribution<double>(0.0, 100.0);
	m_distributionOnList = std::uniform_int_distribution<int>(0, m_currentList.size() - 1);

	m_totalImprovements = PAST_SIZE;
	std::fill(std::begin(m_pastImprovements), std::end(m_pastImprovements), 1);	
	m_currentImprovement = 0;
	
	m_areaStart = 0;
	m_areaEnd = 5;

	m_areaSize = 3;

	m_bestAreaPerimeter = m_currentPerimeter;
}

void LocalRandomSearch::run()
{
	++m_totalIterations;
	{
		std::vector<Coordinate> tmpCoords = m_currentList;
		//randomSwap(tmpCoords);
		randomSwapNeighborsInArea(tmpCoords, m_areaStart, m_areaEnd);
		double tmpPerimeter = calculatePerimeter(tmpCoords);

		// remove the current improvement from the total
		m_totalImprovements -= m_pastImprovements[m_currentImprovement];

		// add the new improvement to the total
		//if(tmpPerimeter < m_currentPerimeter)
		if(tmpPerimeter < m_bestAreaPerimeter)
		{
			m_pastImprovements[m_currentImprovement] = 0;
			m_totalImprovements += 0;

			m_bestAreaPerimeter = tmpPerimeter;
		}
		else
		{
			m_pastImprovements[m_currentImprovement] = 1;
			m_totalImprovements += 1;
		}

		// iterate to the next element in the array
		m_currentImprovement += 1;
		m_currentImprovement = m_currentImprovement % PAST_SIZE;

		// calculate average improvement
		// 0 = alot of improvement
		// 1 = no improvement
		double averageImprovement = (double)m_totalImprovements / (double)PAST_SIZE;

		m_heat = 100 * averageImprovement;

		// randomly accept the temporary coordinates based on the current heat	
		if(m_distribution(m_randomDevice) < m_heat)
		{
			m_currentList = tmpCoords;
			m_currentPerimeter = tmpPerimeter;
		}
		// if you don't blindly accept it, then only accpet it if it's smaller
		// than the current
		//else if(tmpPerimeter < m_currentPerimeter)
		else if(tmpPerimeter < m_currentPerimeter)
		{
			m_currentList = tmpCoords;
			m_currentPerimeter = tmpPerimeter;
		}

		// if the current perimeter is less than the best
		// then the best is now the current
		if(m_currentPerimeter < m_bestPerimeter)
		{
			m_bestPerimeter = m_currentPerimeter;
			m_bestList = m_currentList;
			std::cout << "Iteration: " << m_totalIterations
			<< " Perimeter: " << m_bestPerimeter<< std::endl;
		}

		//if(m_totalIterations % 100000 == 0)
		if(m_heat > 90) // || m_totalIterations % 100000 == 0)
		{
			m_areaStart = m_distributionOnList(m_randomDevice);
			m_areaEnd = m_areaStart + (m_distributionOnList(m_randomDevice) % (m_currentList.size() - m_areaStart));
			m_areaEnd = m_areaStart + m_areaSize;
			if(m_areaEnd >= m_currentList.size())
				m_areaEnd = m_currentList.size() - 1;

			m_bestAreaPerimeter = m_currentPerimeter;

			m_totalImprovements = 0;
			std::fill(std::begin(m_pastImprovements), std::end(m_pastImprovements), 0);	
			m_currentImprovement = 0;

//			std::cout << "Start: " << m_areaStart << " End: " << m_areaEnd << std::endl;

//			m_currentPerimeter = m_bestPerimeter;
//			m_currentList = m_bestList;

			m_areaSize += 1;
			m_areaSize = m_areaSize % (m_currentList.size() / 5);
		}
	}
}

std::vector<Coordinate> & LocalRandomSearch::getBestList()
{
	return m_bestList;
}

std::vector<Coordinate> & LocalRandomSearch::getCurrentList()
{
	return m_currentList;
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

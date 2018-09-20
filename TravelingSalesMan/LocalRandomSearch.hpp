#ifndef LOCALRANDOMSEARCH_HPP
#define LOCALRANDOMSEARCH_HPP

#include <vector>

#include <cstdint>

#include "Coordinate.hpp"

class LocalRandomSearch
{
private:
	std::vector<Coordinate> m_currentList;
	double m_currentPerimeter;

	std::vector<Coordinate> m_bestList;
	double m_bestPerimeter;

	uint64_t m_totalIterations;

	uint64_t m_swapsSinceImprovement;

	double m_heat;
	int m_heatHelp;

public:
	LocalRandomSearch(std::vector<Coordinate>);

	void run();

	std::vector<Coordinate> & getBestList();

	uint64_t getTotalIterations();

	double getHeat();

	double getBestPerimeter();
};

#endif

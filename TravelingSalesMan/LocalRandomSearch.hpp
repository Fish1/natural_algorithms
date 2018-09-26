#ifndef LOCALRANDOMSEARCH_HPP
#define LOCALRANDOMSEARCH_HPP

#define PAST_SIZE 100000

#include <vector>

#include <cstdint>

#include <random>

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

	std::random_device m_randomDevice;
	std::uniform_real_distribution<double> m_distribution;
	std::uniform_int_distribution<int> m_distributionOnList;

	bool m_pastImprovements[PAST_SIZE];
	uint32_t m_totalImprovements;
	uint64_t m_currentImprovement;

	uint32_t m_areaStart;
	uint32_t m_areaEnd;

	uint32_t m_areaSize;
	uint32_t m_areaSizeHelper = 0;

	double m_bestAreaPerimeter;

public:
	LocalRandomSearch(std::vector<Coordinate>);

	void run();

	std::vector<Coordinate> & getBestList();

	std::vector<Coordinate> & getCurrentList();

	uint64_t getTotalIterations();

	double getHeat();

	double getBestPerimeter();

};

#endif

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>

#include <string>

#include "Coordinate.hpp"

double calculateDistance(Coordinate a, Coordinate b); 

double calculatePerimeter(std::vector<Coordinate> coordinates);

void randomizeOrder(std::vector<Coordinate> & coordinates);

void randomSwap(std::vector<Coordinate> & coordinates);

void loadCoordinates(std::string filename, std::vector<Coordinate> & coordinates);

#endif

#ifndef GENERATOROFMAZE_HPP
#define GENERATOROFMAZE_HPP

#include <iostream>
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include "GeneratorOfMaze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"
#include <random>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <map>

class GeneratorOfMaze: public MazeGenerator{
private:
	std::pair<int, int> CurrentCoordinate;
	std::map<std::pair<int, int>, bool> CurrentStatus;
	std::vector<Direction> PossibleDirection;
public:
	GeneratorOfMaze();
	~GeneratorOfMaze();
	
	void generateMaze(Maze& maze);
	void RemoveWall(Maze& maze);
	std::pair<int, int> NextCell(std::pair<int, int> CurrentCoordinate, Direction TargetDir);
	bool AllTrue(Maze& maze, std::map<std::pair<int, int>, bool> CurrentStatus);
	std::vector<Direction> GetDirection(Maze& maze, std::pair<int, int> CurrentCoordinate);
	Direction GetRandomDirection(std::vector<Direction> PossibleDirection);
};


#endif



#ifndef SOLVEROFMAZE_HPP
#define SOLVEROFMAZE_HPP

#include <iostream>
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <random>


class SolverOfMaze: public MazeSolver{
public:
	SolverOfMaze();
	~SolverOfMaze();

	void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void SeekEndOfDark(const Maze& maze, MazeSolution& mazeSolution);
	std::vector<Direction> GetDirection(const Maze& maze, std::pair<int, int> CurrentCoordinate);
	Direction GetRandomDirection(std::vector<Direction> PossibleDirection);

private:
	std::pair<int, int> CurrentCoordinate;
	std::pair<int, int> FinishSolving;
	std::map<std::pair<int, int>, bool> CurrentStatus;
	std::vector<Direction> PossibleDirection;

};

#endif

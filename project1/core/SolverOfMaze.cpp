#include <iostream>
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "SolverOfMaze.hpp"
#include "Direction.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <random>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, SolverOfMaze, "XuYihan's Solver (Required)");

SolverOfMaze::SolverOfMaze(){}
SolverOfMaze::~SolverOfMaze(){}

std::vector<Direction> SolverOfMaze::GetDirection(const Maze& maze, std::pair<int, int> CurrentCoordinate){
	std::vector<Direction> PossibleDirection;

	if(CurrentCoordinate.first - 1 >= 0 and 
		maze.wallExists(CurrentCoordinate.first, CurrentCoordinate.second, Direction::left) == false and 
		CurrentStatus[std::pair<int, int>(CurrentCoordinate.first - 1, CurrentCoordinate.second)] == false){
		
		PossibleDirection.push_back(Direction::left);
	}
	if(CurrentCoordinate.first + 1 < maze.getWidth() and 
		maze.wallExists(CurrentCoordinate.first, CurrentCoordinate.second, Direction::right) == false and 
		CurrentStatus[std::pair<int, int>(CurrentCoordinate.first + 1, CurrentCoordinate.second)] == false){
		
		PossibleDirection.push_back(Direction::right);
	}
	if(CurrentCoordinate.second - 1 >= 0 and 
		maze.wallExists(CurrentCoordinate.first, CurrentCoordinate.second, Direction::up) == false and 
		CurrentStatus[std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second - 1)] == false){
		
		PossibleDirection.push_back(Direction::up);
	}
	if(CurrentCoordinate.second + 1 < maze.getHeight() and 
		maze.wallExists(CurrentCoordinate.first, CurrentCoordinate.second, Direction::down) == false and 
		CurrentStatus[std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second + 1)] == false){
	
		PossibleDirection.push_back(Direction::down);
	}
	return PossibleDirection;
}

Direction SolverOfMaze::GetRandomDirection(std::vector<Direction> PossibleDirection){
	std::random_device device;
	std::default_random_engine engine{device()};
	int LastIndex = PossibleDirection.size() - 1;
	std::uniform_int_distribution<int> distribution{0, LastIndex};
	int RandomIndex = distribution(engine);
	return PossibleDirection[RandomIndex];
}

void SolverOfMaze::SeekEndOfDark(const Maze& maze, MazeSolution& mazeSolution){
	std::pair<int, int> SavedCoordinate = CurrentCoordinate;
	std::vector<Direction> PossibleDirection = GetDirection(maze, CurrentCoordinate);
	CurrentStatus[std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second)] = true;

	while(mazeSolution.isComplete() == false and PossibleDirection.size() != 0){
		Direction TargetDir = GetRandomDirection(PossibleDirection);
		mazeSolution.extend(TargetDir);
		CurrentCoordinate = std::pair<int, int>(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second);
		SeekEndOfDark(maze, mazeSolution);
		if(CurrentCoordinate != std::pair<int, int>(FinishSolving.first, FinishSolving.second) and 
			mazeSolution.isComplete() == false){
			
			mazeSolution.backUp();
	}
		CurrentCoordinate = SavedCoordinate;

		PossibleDirection = GetDirection(maze, CurrentCoordinate);
	}
}

void SolverOfMaze::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
	std::pair<int, int> StartingCell = 	mazeSolution.getStartingCell();
	std::pair<int, int> EndingCell = mazeSolution.getEndingCell();
	CurrentCoordinate = std::pair<int, int>(StartingCell.first, StartingCell.second); 
	FinishSolving = std::pair<int, int>(EndingCell.first, EndingCell.second);
	for(int i = 0; i < maze.getWidth(); i++){
		for(int j = 0; j < maze.getHeight(); j++){
			for(int k = 0; k < maze.getWidth() * maze.getHeight(); k++){
				CurrentStatus[std::pair<int, int>(i, j)] = false;
			}
		}
	}
	SeekEndOfDark(maze, mazeSolution);

}
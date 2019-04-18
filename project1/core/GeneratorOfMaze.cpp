#include <iostream>
#include "GeneratorOfMaze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"
#include <random>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <map>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, GeneratorOfMaze, "XuYihan's Maze (Required)");

//constructor and deconstructor:
GeneratorOfMaze::GeneratorOfMaze(){}
GeneratorOfMaze::~GeneratorOfMaze(){}

std::vector<Direction> GeneratorOfMaze::GetDirection(Maze& maze, std::pair<int, int> CurrentCoordinate){
	std::vector<Direction> PossibleDirection;

	if(CurrentCoordinate.first - 1 >= 0){
		std::pair<int, int> CurrentCoordinate2 = std::pair<int, int>(CurrentCoordinate.first - 1, CurrentCoordinate.second);
		if(CurrentStatus[CurrentCoordinate2] == false){
			PossibleDirection.push_back(Direction::left);
		}
	}
	if(CurrentCoordinate.first + 1 < maze.getWidth()){
		std::pair<int, int> CurrentCoordinate2 = std::pair<int, int>(CurrentCoordinate.first + 1, CurrentCoordinate.second);
		if(CurrentStatus[CurrentCoordinate2] == false){
			PossibleDirection.push_back(Direction::right);
		}
	}
	if(CurrentCoordinate.second - 1 >= 0){
		std::pair<int, int> CurrentCoordinate2 = std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second - 1);
		if(CurrentStatus[CurrentCoordinate2] == false){
			PossibleDirection.push_back(Direction::up);
		}
	}
	if(CurrentCoordinate.second + 1 < maze.getHeight()){
		std::pair<int, int> CurrentCoordinate2 = std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second + 1);
		if(CurrentStatus[CurrentCoordinate2] == false){
			PossibleDirection.push_back(Direction::down);
		}
	}
	return PossibleDirection;
}

Direction GeneratorOfMaze::GetRandomDirection(std::vector<Direction> PossibleDirection){
	std::random_device device;
	std::default_random_engine engine{device()};
	int LastIndex = PossibleDirection.size() - 1;
	std::uniform_int_distribution<int> distribution{0, LastIndex};
	int RandomIndex = distribution(engine);
	return PossibleDirection[RandomIndex];
}

bool GeneratorOfMaze::AllTrue(Maze& maze, std::map<std::pair<int, int>, bool> CurrentStatus){
	for(int i = 0; i < maze.getWidth(); i++){
		for(int j = 0; j < maze.getHeight(); j++){
			if(CurrentStatus[std::pair<int, int>(i, j)] == false){
				return false;
			}
		}
	}
	return true;
}

std::pair<int, int> GeneratorOfMaze::NextCell(std::pair<int, int> CurrentCoordinate, Direction TargetDir){
	if(TargetDir == Direction::left){
		CurrentCoordinate = {CurrentCoordinate.first - 1, CurrentCoordinate.second};
	}
	else if(TargetDir == Direction::right){
		CurrentCoordinate = {CurrentCoordinate.first + 1, CurrentCoordinate.second};
	}
	else if(TargetDir == Direction::up){
		CurrentCoordinate = {CurrentCoordinate.first, CurrentCoordinate.second - 1};
	}
	else if(TargetDir == Direction::down){
		CurrentCoordinate = {CurrentCoordinate.first, CurrentCoordinate.second + 1};
	}

	return CurrentCoordinate;
}

void GeneratorOfMaze::RemoveWall(Maze& maze){
	std::pair<int, int> SavedCoordinate = CurrentCoordinate;
	std::vector<Direction> PossibleDirection = GetDirection(maze, CurrentCoordinate);
	CurrentStatus[std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second)] = true;

	while(AllTrue(maze, CurrentStatus) != true and PossibleDirection.size() != 0){
		Direction TargetDir = GetRandomDirection(PossibleDirection);
		maze.removeWall(CurrentCoordinate.first, CurrentCoordinate.second, TargetDir);
		CurrentCoordinate = NextCell(CurrentCoordinate, TargetDir);
		CurrentStatus[std::pair<int, int>(CurrentCoordinate.first, CurrentCoordinate.second)] = true;
		RemoveWall(maze);
		CurrentCoordinate = SavedCoordinate;
		PossibleDirection = GetDirection(maze, CurrentCoordinate);
	}
}

void GeneratorOfMaze::generateMaze(Maze& maze){
	maze.addAllWalls();	
	//set the status;
	for(int i = 0; i < maze.getWidth(); i++){
		for(int j = 0; j < maze.getHeight(); j++){
			for(int k = 0; k < maze.getWidth() * maze.getHeight(); k++){
				CurrentStatus[std::pair<int, int>(i, j)] = false;
			}
		}
	}
	RemoveWall(maze);

}



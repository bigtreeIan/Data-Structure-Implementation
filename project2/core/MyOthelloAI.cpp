#include "MyOthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloBoard.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, yihanx2::SmartAI, "Yihan's OthelloAI (Required)");

yihanx2::SmartAI::SmartAI(){}
yihanx2::SmartAI::~SmartAI(){}

int yihanx2::SmartAI::EvaluateState(const OthelloGameState& state, OthelloCell MyTile){
	if(MyTile == OthelloCell::white){
		int Score = state.whiteScore() - state.blackScore();
		return Score;
	}
	else{
		int Score = state.blackScore() - state.whiteScore();
		return Score;
	}
}

OthelloCell yihanx2::SmartAI::MyColor(const OthelloGameState& state){
	if(state.isWhiteTurn()){
		return OthelloCell::white;
	}
	else{
		return OthelloCell::black;
	}
}

bool yihanx2::SmartAI::IgnoreInitial(const OthelloGameState& state, int x, int y){
	int W = state.board().width() - 1;
	int H = state.board().height() - 1;
	int LeftUpX = W / 2;
	int LeftUpY = H /2;

	int RightUpX = W / 2 + 1;
	int RightUpY = H / 2;

	int LeftDownX = W / 2;
	int LeftDownY = H / 2 + 1;

	int RightDownX = W / 2 + 1;
	int RightDownY = H / 2 + 1;

	if(x == LeftUpX and y == LeftUpY){
		return false;
	}
	if(x == LeftDownX and y == LeftDownY){
		return false;
	}
	if(x == RightUpX and y == RightUpY){
		return false;
	}
	if(x == RightDownX and y == RightDownY){
		return false;
	}
	return true;
}

std::vector<std::pair<int, int>> yihanx2::SmartAI::ValidMove(const OthelloGameState& state){
	std::vector<std::pair<int, int>> PossibleCoordinate;
	for(int i = 0; i < state.board().width(); ++i){
		for(int j = 0; j < state.board().height(); ++j){				
			if(state.isValidMove(i, j) == true and IgnoreInitial(state, i, j)){
				PossibleCoordinate.push_back(std::pair<int, int>(i, j));
			}
		}		
	}
	return PossibleCoordinate;
}

int yihanx2::SmartAI::SearchState(const OthelloGameState& state, int depth, OthelloCell MyTile, std::pair<int, int> TargetMove){
	int WorseCase = state.board().width() * state.board().height();
	std::unique_ptr<OthelloGameState> GameStatePtr = state.clone();
	GameStatePtr->makeMove(TargetMove.first, TargetMove.second);
	
	if(depth == 0 or GameStatePtr->isGameOver() == true){
		int Score = EvaluateState(*GameStatePtr, MyTile);
		return Score;
	}
	else{
		if((GameStatePtr->isBlackTurn() and MyTile == OthelloCell::black) or (GameStatePtr->isWhiteTurn() and MyTile == OthelloCell::white)){
			int Score = -WorseCase;
			std::vector<std::pair<int, int>> PossibleCoordinate = ValidMove(*GameStatePtr);
			for(int i = 0; i < PossibleCoordinate.size(); ++i){
				int TempScore = SearchState(*GameStatePtr, depth - 1, MyTile, PossibleCoordinate[i]);
				if(TempScore > Score){
					Score = TempScore;
				}
			}
			return Score;
		}
		else{
			int Score = WorseCase;
			std::vector<std::pair<int, int>> PossibleCoordinate = ValidMove(*GameStatePtr);
			for(int i = 0; i < PossibleCoordinate.size(); ++i){
				int TempScore = SearchState(*GameStatePtr, depth - 1, MyTile, PossibleCoordinate[i]);
				if(TempScore < Score){
					Score = TempScore;
				}
			}
			return Score;
		}
	}
}

std::pair<int, int> yihanx2::SmartAI::chooseMove(const OthelloGameState& state){
	OthelloCell MyTile = MyColor(state);
	std::pair<int, int> FinalMove;
	std::vector<std::pair<int, int>> PossibleCoordinate = ValidMove(state);
	int WorseCase = state.board().width() * state.board().height();
	int InitialNumber = -WorseCase;
	for(int i = 0; i < PossibleCoordinate.size(); ++i){
		int BestCase = SearchState(state, 4, MyTile, PossibleCoordinate[i]);
		if(BestCase >= InitialNumber){
			InitialNumber = BestCase;
			FinalMove = std::pair<int, int>(PossibleCoordinate[i].first, PossibleCoordinate[i].second);
		}
	}
	return FinalMove;
}
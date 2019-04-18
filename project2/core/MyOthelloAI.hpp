#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include <iostream>
#include <vector>
#include <map>
#include "OthelloAI.hpp"
#include "OthelloBoard.hpp"
#include "OthelloGameState.hpp"

namespace yihanx2{
	class SmartAI: public OthelloAI{
	public:
		SmartAI();
		~SmartAI();
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		int EvaluateState(const OthelloGameState& state, OthelloCell MyTile);
		int SearchState(const OthelloGameState& state, int depth, OthelloCell MyTile, std::pair<int, int> TargetMove);
		OthelloCell MyColor(const OthelloGameState& state);
		std::vector<std::pair<int, int>> ValidMove(const OthelloGameState& state);
		bool IgnoreInitial(const OthelloGameState& state, int x, int y);
	};
};

#endif
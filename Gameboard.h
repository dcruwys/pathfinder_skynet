
#include <cstdint>
#include <iostream>
#include <vector>


enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of grid agent

namespace grid
{
	struct State{
		static const int boardSize = 30; //size of grid
		static const int rows = 6; //rows of grid
		static const int cols = 5; //columns of grid
		int agentLoc; //location of agent
		int board[boardSize]; //grid
	};

	inline bool operator==(const State &lhs, const State &rhs){
		return lhs.agentLoc == rhs.agentLoc;
	}

	struct Action{
		direction myDirection; //give an action a direction
		Action(direction directionIN){
			//read a direction in in the constructor and set it to the direction of the Action
			myDirection = directionIN;
		}
	};
}

class Gameboard {
	
public:
	Gameboard(){}
	void GetActions(grid::State &nodeID, std::vector<grid::Action> &actions);
	void ApplyAction(grid::State &s, grid::Action a);
	void UndoAction(grid::State &s, grid::Action a);
};




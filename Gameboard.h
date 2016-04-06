#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

namespace Grid
{
	enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of grid agent

	struct State{
		static const int boardSize = 100; //size of grid
		static const int rows = 10; //rows of grid
		static const int cols = 10; //columns of grid
		int agentLocX; // x location of agent
		int agentLocY; // y location of agent
		int board[rows][cols]; //grid
	};

	inline bool operator==(const State &lhs, const State &rhs){
		return (lhs.agentLocX == rhs.agentLocX && lhs.agentLocY == rhs.agentLocY);
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
	void GetActions(Grid::State &nodeID, std::vector<Grid::Action> &actions);
	void ApplyAction(Grid::State &s, Grid::Action a);
	void UndoAction(Grid::State &s, Grid::Action a);
};




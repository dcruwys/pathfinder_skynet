#pragma once
#include <cstdint>
#include <iostream>
#include <vector>




namespace SlidingTile4x4
{
	enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of puzzle blank

	struct State{
		static const int boardSize = 16; //size of grid
		static const int rows = 4; //rows of grid
		static const int cols = 4; //columns of grid
		int blankTileX = 0;
		int blankTileY = 4;
		int board[4][4]; //grid
		void swapTiles(int puzzle[4][4], int aX, int aY, int bX, int bY)
		{
			int temp = puzzle[aX][aX];
			puzzle[aX][aY] = puzzle[bX][bY];
			puzzle[bX][bY] = temp;
		}
	};

	inline bool operator==(const State &lhs, const State &rhs){
		for (int i = 0, int j; i < 4; ++i)
		{
			for (j = 0; j < 4; ++j)
			{
				if (lhs.board[i][j] != rhs.board[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	struct Action{
		direction myDirection; //give an action a direction
		Action(direction directionIN){
			//read a direction in in the constructor and set it to the direction of the Action
			myDirection = directionIN;
		}
	};
}

class SlidingTile {

public:
	SlidingTile(){}
	void GetActions(SlidingTile4x4::State &nodeID, std::vector<SlidingTile4x4::Action> &actions);
	void ApplyAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a);
	void UndoAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a);
};




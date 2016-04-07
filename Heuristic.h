#pragma once
#include "SlidingTile.h"
#include <cmath>

class Heuristic {
public:
	Heuristic() { };

	int getHeuristic(SlidingTile4x4::State &s, SlidingTile4x4::State &g) {
		//h = heuristic value to return for state s
		int h = 0;
		int tempRow = 0;
		int tempCol = 0;
		//loop through the sliding tile grid
		//using index, keep track of what tile value is supposed to be at a given i,j location
		for (int i = 0, j = 0, index = 0; i < s.rows; ++i) {
			for (j = 0; j < s.cols; ++j, ++index) {
				if (s.board[i][j] != index && s.board[i][j] != 0)
				{
					h = h + abs((s.board[i][j] / s.rows) - i) + abs((s.board[i][j] % s.cols) - j);
				}
			}
		}
		return h;
	}

	int getHeuristic(Tree::State &s, Tree::State &g) {
		return 0;
	}

	int getHeuristic(Grid::State &s, Grid::State &g) {

	}

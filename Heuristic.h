#pragma once
#include "SlidingTile.h"
#include <cmath>

class Heuristic {
public:
	Heuristic() { };

	int getHeuristic(SlidingTile4x4::State &s, SlidingTile4x4::State &g) {
		//h = heuristic value to return for state s
        int sum = 0;
        for(int i = 0; i < s.board.size(); ++i) {
            if (s.board.at(i) != 0) {
                int h = std::abs(s.board.at(i) - i);
                int temp = h % s.size;
                h = h / s.size;
                sum += h + temp;
            }
        }
        return sum;
	}

	int getHeuristic(Tree::State &s, Tree::State &g) {
		return 0;
	}

	int getHeuristic(Grid::State &s, Grid::State &g) {
		return 0;
	}
};

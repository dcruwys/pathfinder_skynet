#pragma once
#include "SlidingTile.h"
#include <cmath>

class Heuristic {
public:
	Heuristic() { };

	int hcost(SlidingTile &s) {
		//h = heuristic value to return for state s
        int sum = 0;
        for(int i = 0; i < sizeof(s.tiles); ++i) {
            if (s.tiles[i] != 0) {
                int h = std::abs(s.tiles[i] - i);
                int temp = h % 4;
                h = h / 4;
                sum += h + temp;
            }
        }
        return sum;
	}
};

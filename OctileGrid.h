#pragma once
//#ifndef OctileGrid_h
//#define OctileGrid_h


#include <vector>
#include <stdlib.h>
#include <cmath>

enum oGridAction{UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

struct coordinate {
	int x, y, fcost, gcost, hcost;
};

bool operator==(const coordinate &c1, const coordinate &c2);

class OctileGrid{
public:
	OctileGrid(int w, int h);
	void GetActions(coordinate &nodeID, std::vector<oGridAction> &actions);
	void ApplyAction(coordinate &s, oGridAction a);
	void UndoAction(coordinate &s, oGridAction a);
private:
	char map[180][120];
	int width;
	int height;
	//std::vector<std::vector<char>> map;
	
};

struct OD {
	int hcost(const coordinate &start, const coordinate &goal){
		int xdist = abs(start.x - goal.x);
		int ydist = abs(start.y - goal.y);

		//max(x, y) + (sqrt(2)-1)*min(x, y)
		return std::max(xdist, ydist) + (sqrt(2)-1) * std::min(xdist, ydist);
	}
};

//
//
//#endif

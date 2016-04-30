#pragma once
//#ifndef OctileGrid_h
//#define OctileGrid_h

#include <vector>

enum oGridAction{UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

struct coordinate {
	int x, y;
};

bool operator==(const coordinate &c1, const coordinate &c2);

class OctileGrid{
public:
	OctileGrid(int w, int h);
	void GetActions(coordinate &nodeID, std::vector<oGridAction> &actions);
	void ApplyAction(coordinate &s, oGridAction a);
	void UndoAction(coordinate &s, oGridAction a);
	char map[180][120];
private:
	int width;
	int height;
	//std::vector<std::vector<char>> map;
	
};

//
//
//#endif

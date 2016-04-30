#ifndef OctileGrid_h
#define OctileGride_h

#include <vector>

enum oGridAction{UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

struct coordinate {
	int x, y;
};

bool operator==(const coordinate &c1, const coordinate &c2);

class OctileGrid
{
public:
	OctileGrid(int w, int h);
	void GetActions(coordinate &nodeID, std::vector<oGridAction> &actions);
	void ApplyAction(coordinate &s, oGridAction a);
	void UndoAction(coordinate &s, oGridAction a);
private:
	int width;
	int height;
	std::vector<std::vector<char>> map;
};

#endif
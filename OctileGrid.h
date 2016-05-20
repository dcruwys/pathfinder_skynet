#pragma once
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <cstdint>

enum Action{ UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

struct Coordinate
{
	int x, y;
};

inline bool operator==(const Coordinate &c1, const Coordinate &c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

struct OctileDistance
{
	int hcost(const Coordinate &start, const Coordinate &goal)
	{
		int xdist = abs(goal.x - start.x);
		int ydist = abs(goal.y - start.y);
		return std::max(xdist, ydist) + (sqrt(2) - 1) * std::min(xdist, ydist);
	}
};

class OctileGrid
{
public:
	OctileGrid(int width, int height);
	void GetActions(Coordinate &nodeID, std::vector<Action> &actions);
	void ApplyAction(Coordinate &s, Action a);
	void UndoAction(Coordinate &s, Action a);
	uint64_t Rank(Coordinate &s);
	char map[194][194];
private:
	int width;
	int height;
};
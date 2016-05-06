#pragma once

#include "InefficientAstar.h"

#include <vector>
#include <stdlib.h>
#include <algorithm>

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
	int hcost(const Node<Coordinate> &start, const Node<Coordinate> &goal)
	{
		int xdist = std::abs(goal.c.x - start.c.x);
		int ydist = std::abs(goal.c.y - start.c.y);
		return std::max(xdist, ydist) + (sqrt(2) - 1) * std::min(xdist, ydist);
	}
};

class OctileGrid
{
public:
	OctileGrid(int width, int height);
	void GetActions(Node<Coordinate> &nodeID, std::vector<Action> &actions);
	void ApplyAction(Node<Coordinate> &s, Action a);
	void UndoAction(Node<Coordinate> &s, Action a);
private:
	char map[180][120];
	int width;
	int height;
};
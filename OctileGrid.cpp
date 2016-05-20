#include "OctileGrid.h"

#include <fstream>
#include <iostream>
#include <string>

OctileGrid::OctileGrid(int width, int height)
{
	this->width = width;
	this->height = height;
	const char* filename1 = "orz301d.map";
	std::string buffer;
	std::ifstream read;
	read.open(filename1);
	if (read.is_open())
	{
		buffer.clear();
		int i = 0;
		int k = 0;
		while (getline(read, buffer))
		{
			if (i > 3)
			{
				for (int j = 0; j < 120; j++)
				{
					map[k][j] = buffer[j];
				}
				k++;
				buffer.clear();
			}
			i++;
		}
	}
	read.close();
}

void OctileGrid::GetActions(Coordinate &nodeID, std::vector<Action> &actions)
{
	actions.clear();
	if (nodeID.x < width - 1 && map[nodeID.y][nodeID.x + 1] == '.')
	{
		actions.push_back(Action::RIGHT);
	}
	if (nodeID.x > 0 && map[nodeID.y][nodeID.x - 1] == '.')
	{
		actions.push_back(Action::LEFT);
	}
	if (nodeID.y < height - 1 && map[nodeID.y - 1][nodeID.x] == '.')
	{
		actions.push_back(Action::UP);
	}
	if (nodeID.y > 0 && map[nodeID.y + 1][nodeID.x] == '.')
	{
		actions.push_back(Action::DOWN);
	}
	if (nodeID.x < width - 1 && nodeID.y < height && map[nodeID.y - 1][nodeID.x + 1] == '.')
	{
		actions.push_back(Action::UPRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y < height - 1 && map[nodeID.y - 1][nodeID.x - 1] == '.')
	{
		actions.push_back(Action::UPLEFT);
	}
	if (nodeID.x < width - 1 && nodeID.y > 0 && map[nodeID.y + 1][nodeID.x + 1] == '.')
	{
		actions.push_back(Action::DOWNRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y > 0 && map[nodeID.y + 1][nodeID.x - 1] == '.')
	{
		actions.push_back(Action::DOWNLEFT);
	}
}

void OctileGrid::ApplyAction(Coordinate &s, Action a)
{
	switch (a)
	{
	case Action::RIGHT: s.x++; break;
	case Action::LEFT: s.x--; break;
	case Action::UP: s.y--; break;
	case Action::DOWN: s.y++; break;
	case Action::UPRIGHT: s.x++; s.y--; break;
	case Action::UPLEFT: s.x--; s.y--; break;
	case Action::DOWNRIGHT: s.x++; s.y++; break;
	case Action::DOWNLEFT: s.x--; s.y++; break;
	}
}

void OctileGrid::UndoAction(Coordinate &s, Action a)
{
	switch (a)
	{
	case Action::RIGHT: s.x--; break;
	case Action::LEFT: s.x++; break;
	case Action::UP: s.y++; break;
	case Action::DOWN: s.y--; break;
	case Action::UPRIGHT: s.x--; s.y++; break;
	case Action::UPLEFT: s.x++; s.y++; break;
	case Action::DOWNRIGHT: s.x--; s.y--; break;
	case Action::DOWNLEFT: s.x++; s.y--; break;
	}
}

uint64_t OctileGrid::Rank(Coordinate &s)
{
	return s.x * height + s.y;
}
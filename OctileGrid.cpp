#include "OctileGrid.h"
#include <iostream>
#include <fstream>
#include <string>

bool operator==(const coordinate &c1, const coordinate &c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

OctileGrid::OctileGrid(int w, int h)
{
	width = w;
	height = h;
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

void OctileGrid::GetActions(coordinate &nodeID,  std::vector<oGridAction> &actions)
{
	std::cout << nodeID.x << " " << nodeID.y << std::endl;
	std::cout << map[nodeID.y][nodeID.x] << std::endl;
	actions.clear();
	if (nodeID.x < width && map[nodeID.y][nodeID.x+1] == '.')
	{
		actions.push_back(oGridAction::RIGHT);
	}
	if (nodeID.x > 0 && map[nodeID.y][nodeID.x-1] == '.')
	{
		actions.push_back(oGridAction::LEFT);
	}
	if (nodeID.y < height && map[nodeID.y-1][nodeID.x] == '.')
	{
		actions.push_back(oGridAction::UP);
	}
	if (nodeID.y > 0 && map[nodeID.y+1][nodeID.x] == '.')
	{
		actions.push_back(oGridAction::DOWN);
	}
	if (nodeID.x < width && nodeID.y < height && map[nodeID.y-1][nodeID.x+1] == '.')
	{
		actions.push_back(oGridAction::UPRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y < height && map[nodeID.y-1][nodeID.x-1] == '.')
	{
		actions.push_back(oGridAction::UPLEFT);
	}
	if (nodeID.x < width && nodeID.y > 0 && map[nodeID.y+1][nodeID.x+1] == '.')
	{
		actions.push_back(oGridAction::DOWNRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y > 0 && map[nodeID.y+1][nodeID.x-1] == '.')
	{
		actions.push_back(oGridAction::DOWNLEFT);
	}
}

void OctileGrid::ApplyAction(coordinate &s, oGridAction a)
{
	switch (a)
	{
	case oGridAction::RIGHT: s.x++; break;
	case oGridAction::LEFT: s.x--; break;
	case oGridAction::UP: s.y--; break;
	case oGridAction::DOWN: s.y++; break;
	case oGridAction::UPRIGHT: s.x++; s.y--; break;
	case oGridAction::UPLEFT: s.x--; s.y--; break;
	case oGridAction::DOWNRIGHT: s.x++; s.y++; break;
	case oGridAction::DOWNLEFT: s.x--; s.y++; break;
	}
}

void OctileGrid::UndoAction(coordinate &s, oGridAction a)
{
	switch (a)
	{
	case oGridAction::RIGHT: s.x--; break;
	case oGridAction::LEFT: s.x++; break;
	case oGridAction::UP: s.y++; break;
	case oGridAction::DOWN: s.y--; break;
	case oGridAction::UPRIGHT: s.x--; s.y++; break;
	case oGridAction::UPLEFT: s.x++; s.y++; break;
	case oGridAction::DOWNRIGHT: s.x--; s.y--; break;
	case oGridAction::DOWNLEFT: s.x++; s.y--; break;
	}
}
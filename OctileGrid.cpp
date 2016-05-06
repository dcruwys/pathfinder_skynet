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

void OctileGrid::GetActions(Node<Coordinate> &nodeID, std::vector<Action> &actions)
{
	actions.clear();
	if (nodeID.c.x < width - 1 && map[nodeID.c.y][nodeID.c.x + 1] == '.')
	{
		actions.push_back(Action::RIGHT);
	}
	if (nodeID.c.x > 0 && map[nodeID.c.y][nodeID.c.x - 1] == '.')
	{
		actions.push_back(Action::LEFT);
	}
	if (nodeID.c.y < height - 1 && map[nodeID.c.y - 1][nodeID.c.x] == '.')
	{
		actions.push_back(Action::UP);
	}
	if (nodeID.c.y > 0 && map[nodeID.c.y + 1][nodeID.c.x] == '.')
	{
		actions.push_back(Action::DOWN);
	}
	if (nodeID.c.x < width - 1 && nodeID.c.y < height && map[nodeID.c.y - 1][nodeID.c.x + 1] == '.')
	{
		actions.push_back(Action::UPRIGHT);
	}
	if (nodeID.c.x > 0 && nodeID.c.y < height - 1 && map[nodeID.c.y - 1][nodeID.c.x - 1] == '.')
	{
		actions.push_back(Action::UPLEFT);
	}
	if (nodeID.c.x < width - 1 && nodeID.c.y > 0 && map[nodeID.c.y + 1][nodeID.c.x + 1] == '.')
	{
		actions.push_back(Action::DOWNRIGHT);
	}
	if (nodeID.c.x > 0 && nodeID.c.y > 0 && map[nodeID.c.y + 1][nodeID.c.x - 1] == '.')
	{
		actions.push_back(Action::DOWNLEFT);
	}
}

void OctileGrid::ApplyAction(Node<Coordinate> &s, Action a)
{
	switch (a)
	{
	case Action::RIGHT: s.c.x++; break;
	case Action::LEFT: s.c.x--; break;
	case Action::UP: s.c.y--; break;
	case Action::DOWN: s.c.y++; break;
	case Action::UPRIGHT: s.c.x++; s.c.y--; break;
	case Action::UPLEFT: s.c.x--; s.c.y--; break;
	case Action::DOWNRIGHT: s.c.x++; s.c.y++; break;
	case Action::DOWNLEFT: s.c.x--; s.c.y++; break;
	}
}

void OctileGrid::UndoAction(Node<Coordinate> &s, Action a)
{
	switch (a)
	{
	case Action::RIGHT: s.c.x--; break;
	case Action::LEFT: s.c.x++; break;
	case Action::UP: s.c.y++; break;
	case Action::DOWN: s.c.y--; break;
	case Action::UPRIGHT: s.c.x--; s.c.y++; break;
	case Action::UPLEFT: s.c.x++; s.c.y++; break;
	case Action::DOWNRIGHT: s.c.x--; s.c.y--; break;
	case Action::DOWNLEFT: s.c.x++; s.c.y--; break;
	}
}
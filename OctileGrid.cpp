#include "OctileGrid.h"
#include <iostream>

bool operator==(const coordinate &c1, const coordinate &c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

//TODO: read in map data from file to map[][]
OctileGrid::OctileGrid(int w, int h): width(w), height(h)
{
	const char* filename1 = "orz301d.map";
	FILE *pfile;
	pfile = fopen(filename1, "rb");
	char buffer[120];
	for (int i = 0; i < height; i++)
	{
		if (fgets(buffer, 120, pfile))
		{
			puts(buffer);
			for (int j = 0; j < height; j++)
			{
				map[i][j] = buffer[j];
			}
		}
	}
	fclose(pfile);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void OctileGrid::GetActions(coordinate &nodeID,  std::vector<oGridAction> &actions)
{
	actions.clear();
	if (nodeID.x < width && map[nodeID.x++][nodeID.y] != 'T' && map[nodeID.x++][nodeID.y] != '@')
	{
		actions.push_back(oGridAction::RIGHT);
	}
	if (nodeID.x > 0 && map[nodeID.x--][nodeID.y] != 'T' && map[nodeID.x--][nodeID.y] != '@')
	{
		actions.push_back(oGridAction::LEFT);
	}
	if (nodeID.y < height && map[nodeID.x][nodeID.y++] != 'T' && map[nodeID.x][nodeID.y++] != '@')
	{
		actions.push_back(oGridAction::UP);
	}
	if (nodeID.y > 0 && map[nodeID.x][nodeID.y--] != 'T' && map[nodeID.x][nodeID.y--] != '@')
	{
		actions.push_back(oGridAction::DOWN);
	}
	if (nodeID.x < width && nodeID.y < height && map[nodeID.x++][nodeID.y++] != 'T' && map[nodeID.x++][nodeID.y++] != '@')
	{
		actions.push_back(oGridAction::UPRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y < height && map[nodeID.x--][nodeID.y++] != 'T' && map[nodeID.x--][nodeID.y++] != '@')
	{
		actions.push_back(oGridAction::UPLEFT);
	}
	if (nodeID.x < width && nodeID.y > 0 && map[nodeID.x++][nodeID.y--] != 'T' && map[nodeID.x++][nodeID.y--] != '@')
	{
		actions.push_back(oGridAction::DOWNRIGHT);
	}
	if (nodeID.x > 0 && nodeID.y > 0 && map[nodeID.x--][nodeID.y--] != 'T' && map[nodeID.x--][nodeID.y--] != '@')
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
	case oGridAction::UP: s.y++; break;
	case oGridAction::DOWN: s.y--; break;
	case oGridAction::UPRIGHT: s.x++; s.y++; break;
	case oGridAction::UPLEFT: s.x--; s.y++; break;
	case oGridAction::DOWNRIGHT: s.x++; s.y--; break;
	case oGridAction::DOWNLEFT: s.x--; s.y--; break;
	}
}

void OctileGrid::UndoAction(coordinate &s, oGridAction a)
{
	switch (a)
	{
	case oGridAction::RIGHT: s.x--; break;
	case oGridAction::LEFT: s.x++; break;
	case oGridAction::UP: s.y--; break;
	case oGridAction::DOWN: s.y++; break;
	case oGridAction::UPRIGHT: s.x--; s.y--; break;
	case oGridAction::UPLEFT: s.x++; s.y--; break;
	case oGridAction::DOWNRIGHT: s.x--; s.y++; break;
	case oGridAction::DOWNLEFT: s.x++; s.y++; break;
	}
}
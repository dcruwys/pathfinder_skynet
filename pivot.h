#include "OctileGrid.h"

struct pivot_info
{
	Coordinate pivot;
	int costs[180][120];

	pivot_info()
	{
		for (int i = 0; i < 180; i++)
		{
			for (int j = 0; j < 120; j++)
			{
				costs[i][j] = 1;
			}
		}
	}
};

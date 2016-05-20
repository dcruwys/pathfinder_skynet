#include "OctileGrid.h"

struct pivot_info
{
	Coordinate pivot;
	int costs[194][194];

	pivot_info()
	{
		for (int i = 0; i < 194; i++)
		{
			for (int j = 0; j < 194; j++)
			{
				costs[i][j] = 1;
			}
		}
	}
};

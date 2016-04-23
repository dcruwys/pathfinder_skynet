
#pragma once
#include <vector>
#include <fstream>
#include "BFS.h"
#include <iostream>
#include <cstring>
#include "SlidingTile.h"
#include "Heuristic.h"
#include <algorithm>

class PDB
{
public:
	PDB(bool pdb)
	{
		std::vector<int> pattern_a = { 0, 1, 4, 5 };
		std::vector<int> pattern_b = { 0, 2, 3, 6, 7 };
		std::vector<int> pattern_c = { 0, 8, 9, 12, 13 };
		std::vector<int> pattern_d = { 0, 10, 11, 14, 15 };
		std::vector<int> pattern_e = { 0, 1, 2, 3, 4, 5, 6, 7 };
		MDdist = 0;
		hcost1 = 0;
		hcost2 = 0;
		hcost3 = 0;
		hcost4 = 0;
		hcost5 = 0;
		//the max of manhattan distance and pdbs a-d
		int j = 0;
		int x = 0;
		if (pdb)
		{
			x = 4;
		}
		else
		{
			x = 5;
			j = 3;
		}
		const char* filename1 = "pdb_a.txt";
		const char* filename2 = "pdb_b.txt";
		const char* filename3 = "pdb_c.txt";
		const char* filename4 = "pdb_d.txt";
		const char* filename5 = "pdb_e.txt";
		for (int i = j; i < x; i++)
		{
			SlidingTile puzzle16;
			FILE *pfile;
			uint32_t result = 0;
			switch (i)
			{
			case 0: pfile = fopen(filename1, "rb"); break;
			case 1: pfile = fopen(filename2, "rb"); break;
			case 2: pfile = fopen(filename3, "rb"); break;
			case 3: pfile = fopen(filename4, "rb"); break;
			case 4: pfile = fopen(filename5, "rb"); break;
			}
			if (pfile != nullptr)
			{
				uint32_t rank = 0;
				switch (i)
				{
				case 0:
					buffer = (uint8_t *)malloc(sizeof(uint8_t)* puzzle16.GetMaxRank(pattern_a));
					if (buffer != nullptr) std::cout << sizeof(buffer) << std::endl;
					result = fread(buffer, sizeof(uint8_t), puzzle16.GetMaxRank(pattern_a), pfile);
					rank = puzzle16.Rank(pattern_a);
					hcost1 = (int)buffer[rank];
					fclose(pfile);
					break;
				case 1:
					buffer = (uint8_t *)malloc(sizeof(uint8_t)* puzzle16.GetMaxRank(pattern_b));
					if (buffer != nullptr) std::cout << sizeof(buffer) << std::endl;
					result = fread(buffer, sizeof(uint8_t), puzzle16.GetMaxRank(pattern_b), pfile);
					rank = puzzle16.Rank(pattern_b);
					hcost2 = (int)buffer[rank];
					fclose(pfile);
					break;
				case 2:
					buffer = (uint8_t *)malloc(sizeof(uint8_t)* puzzle16.GetMaxRank(pattern_c));
					if (buffer != nullptr) std::cout << sizeof(buffer) << std::endl;
					result = fread(buffer, sizeof(uint8_t), puzzle16.GetMaxRank(pattern_c), pfile);
					rank = puzzle16.Rank(pattern_c);
					hcost3 = (int)buffer[rank];
					fclose(pfile);
					break;
				case 3:
					buffer = (uint8_t *)malloc(sizeof(uint8_t)* puzzle16.GetMaxRank(pattern_d));
					if (buffer != nullptr) std::cout << sizeof(buffer) << std::endl;
					result = fread(buffer, sizeof(uint8_t), puzzle16.GetMaxRank(pattern_d), pfile);
					rank = puzzle16.Rank(pattern_d);
					hcost4 = (int)buffer[rank];
					fclose(pfile);
					break;
				case 4:
					buffer = (uint8_t *)malloc(sizeof(uint8_t)* puzzle16.GetMaxRank(pattern_e));
					if (buffer != nullptr) std::cout << sizeof(buffer) << std::endl;
					result = fread(buffer, sizeof(uint8_t), puzzle16.GetMaxRank(pattern_e), pfile);
					rank = puzzle16.Rank(pattern_e);
					hcost5 = (int)buffer[rank];
					fclose(pfile);
					break;
				}
			}
			else
			{
				std::cout << "You have not provided the appropriate pattern database, and I would" <<
					" generate them for you, but it would take too long. Uncomment main to generate if you need to." << std::endl;
			}
		}
	}

	int hcost(SlidingTile &s)
	{
		Heuristic MD;
		MDdist = MD.hcost(s);
		int temp1 = std::max(hcost2, hcost3);
		int temp2 = std::max(hcost4, hcost5);
		int temp3 = std::max(hcost1, MDdist);
		int temp4 = std::max(temp1, temp2);
		return std::max(temp4, temp3);
	}
private:
	uint8_t *buffer;
	SlidingTile state;
	int MDdist;
	int hcost1;
	int hcost2;
	int hcost3;
	int hcost4;
	int hcost5;
};
//
//  STP.cpp
//  HW #2
//
//  Created by Nathan Sturtevant on 4/20/16.
//  Copyright © 2016 NS Software. All rights reserved.
//

#include <stdio.h>
#include "STP.h"

uint64_t Factorial(int temp)
{
	uint64_t table[17] =
			{ 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000};
	return table[temp];
}

STPState::STPState()
{
	for (int x = 0; x < 16; x++)
		values[x] = x;
	blank = 0;
	hcost = 0;
}
STPState::STPState(const STPState &s) {
	blank = s.blank;
	hcost = s.hcost;
	fcost = s.fcost;
	gcost = s.gcost;
	for(int i = 0; i < 16; i++){
		values[i] = s.values[i];
	}
}

STPState::~STPState(){}

std::ostream &operator<<(std::ostream &out, const STPState &s)
{
	out << "Blank: " << s.blank << "; h: " << s.hcost << "\n";
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			out << s.values[4*y+x]/10 << s.values[4*y+x]%10 << " ";
		}
		out << "\n";
	}
	return out;
}

bool operator==(const STPState &s, const STPState &t)
{
	for (int x = 0; x < 16; x++)
		if (s.values[x] != t.values[x])
			return false;
	return true;
}

void STP::GetActions(STPState &nodeID, std::vector<slideDir> &actions)
{
	actions.resize(0);
	switch (nodeID.blank)
	{
		case 0:
			actions.push_back(kDown);
			actions.push_back(kRight);
			break;
		case 1:
		case 2:
			actions.push_back(kDown);
			actions.push_back(kRight);
			actions.push_back(kLeft);
			break;
		case 3:
			actions.push_back(kDown);
			actions.push_back(kLeft);
			break;
		case 4:
		case 8:
			actions.push_back(kDown);
			actions.push_back(kUp);
			actions.push_back(kRight);
			break;
		case 5:
		case 6:
		case 9:
		case 10:
			actions.push_back(kDown);
			actions.push_back(kUp);
			actions.push_back(kRight);
			actions.push_back(kLeft);
			break;
		case 7:
		case 11:
			actions.push_back(kUp);
			actions.push_back(kDown);
			actions.push_back(kLeft);
			break;
		case 12:
			actions.push_back(kUp);
			actions.push_back(kRight);
			break;
		case 13:
		case 14:
			actions.push_back(kUp);
			actions.push_back(kRight);
			actions.push_back(kLeft);
			break;
		case 15:
			actions.push_back(kUp);
			actions.push_back(kLeft);
			break;
	}
}

void STP::ApplyAction(STPState &s, slideDir a)
{
	switch (a)
	{
		case kUp:
			s.hcost -= Distance(s.values[s.blank-4], s.blank-4);
			s.hcost += Distance(s.values[s.blank-4], s.blank);
			
			s.values[s.blank] = s.values[s.blank-4];
			s.values[s.blank-4] = 0;
			s.blank -= 4;
			break;
		case kDown:
			s.hcost -= Distance(s.values[s.blank+4], s.blank+4);
			s.hcost += Distance(s.values[s.blank+4], s.blank);

			s.values[s.blank] = s.values[s.blank+4];
			s.values[s.blank+4] = 0;
			s.blank += 4;
			break;
		case kLeft:
			s.hcost -= Distance(s.values[s.blank-1], s.blank-1);
			s.hcost += Distance(s.values[s.blank-1], s.blank);
			
			s.values[s.blank] = s.values[s.blank-1];
			s.values[s.blank-1] = 0;
			s.blank -= 1;
			break;
		case kRight:
			s.hcost -= Distance(s.values[s.blank+1], s.blank+1);
			s.hcost += Distance(s.values[s.blank+1], s.blank);
			
			s.values[s.blank] = s.values[s.blank+1];
			s.values[s.blank+1] = 0;
			s.blank += 1;
			break;
	}
}

slideDir STP::InvertAction(slideDir a)
{
	switch (a) // invert action
	{
		case kUp: return kDown; break;
		case kDown: return kUp; break;
		case kLeft: return kRight; break;
		case kRight: return kLeft; break;
	}
}

void STP::UndoAction(STPState &s, slideDir a)
{
	ApplyAction(s, InvertAction(a));
}


int STP::Distance(int tile, int loc)
{
	static int values[16][16] =
	{
		{0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6}, // 0
		{1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5}, // 1
		{2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4}, // 2
		{3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3}, // 3
		{1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5}, // 4
		{2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4}, // 5
		{3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3}, // 6
		{4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2}, // 7
		{2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4}, // 8
		{3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3}, // 9
		{4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2}, // 10
		{5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1}, // 11
		{3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3}, // 12
		{4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2}, // 13
		{5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1}, // 14
		{6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0}
	};
	return values[tile][loc];
}


uint32_t STP::Rank(const std::vector<int> pattern, STPState state)
{
	std::vector<int> dual;
	// create dual array with locations of tiles
	// that are not blanked out
	for (int i = 0; i < pattern.size(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			// for each tile in our pattern
			// set the ith value in our dual array
			// to the location of the pattern value
			// in our sliding tile
			if (state.values[j] == pattern[i])
			{
				dual.push_back(j);
			}
		}
	}
	uint32_t rankVal = 0;
	int numEntriesLeft = 16;
	for (int x = 0; x < dual.size(); x++)
	{
		for (int i = x+1; i < dual.size(); i++)
		{
			if (dual[x] < dual[i])
			{
				dual[i]--;
			}
		}
	}
	for (int x = 0; x < dual.size(); x++)
	{
		rankVal += dual[x] * (Factorial(numEntriesLeft - 1) / Factorial(16 - pattern.size()));
		numEntriesLeft--;
	}
	return rankVal;
}

uint32_t STP::GetMaxRank(std::vector<int> pattern)
{
	return Factorial(16) / Factorial(16 - pattern.size());
}

STPState STP::Unrank(uint32_t rank, const std::vector<int> pattern)
{
	STPState s;
	uint32_t unrankVal = rank;
	std::vector<int> dual;
	dual.resize(pattern.size());
	int numEntriesLeft = 16 - 1;
	for (int i = 0; i < pattern.size(); i++)
	{
		dual[i] = unrankVal / (Factorial(numEntriesLeft) / Factorial(16 - pattern.size()));
		unrankVal -= (dual[i] * (Factorial(numEntriesLeft) / Factorial(16 - pattern.size())));
		numEntriesLeft--;
	}

	for (int x = pattern.size() - 1; x >= 0; x--)
	{
		for (int y = x - 1; y >= 0; y--)
		{
			if (dual[y] <= dual[x])
			{
				dual[x]++;
			}
		}
	}

	int pindex = 0;
	for (int x = 0; x < 16; x++)
	{
		s.values[x] = -1;
		for(int y = 0; y < pattern.size(); y++) {
            if (dual[y] == x) {
                s.values[x] = pattern[y];
            }
        }
	}

	s.blank = dual[0];
    return s;
}


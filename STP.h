//
//  STP.h
//  HW #2
//
//  Created by Nathan Sturtevant on 4/20/16.
//  Copyright © 2016 NS Software. All rights reserved.
//

#ifndef STP_h
#define STP_h

#include <vector>
#include <iostream>

struct STPState {
	STPState();
	STPState(const STPState &s);
	~STPState();
	
	uint8_t values[16];
	int blank;
	int hcost;
	int fcost;
	int gcost;
};

bool operator==(const STPState &s, const STPState &t);
std::ostream &operator<<(std::ostream &out, const STPState &s);

enum slideDir {
	kUp = 1,
	kDown = 2,
	kRight = 3,
	kLeft = 4
};

class STP {
public:
	void GetActions(STPState &nodeID, std::vector<slideDir> &actions);
	void ApplyAction(STPState &s, slideDir a);
	void UndoAction(STPState &s, slideDir a);
	slideDir InvertAction(slideDir a);
	int Distance(int tile, int loc);

	STPState Unrank(uint32_t rank, const std::vector<int> pattern);
	uint32_t Rank(std::vector<int> pattern, STPState state);
	uint32_t GetMaxRank(std::vector<int> pattern);

private:
};

struct MD {
	int hcost(const STPState &s, const STPState &goal)
	{
		return s.hcost;
	}
	int hcost(const STPState &s)
	{
		return s.hcost;
	}
};


#endif /* STP_h */

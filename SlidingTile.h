#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <list>

	enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of puzzle blank

	struct Action{
		direction myDirection; //give an action a direction
		Action(direction directionIN){
			//read a direction in in the constructor and set it to the direction of the Action
			myDirection = directionIN;
		}
	};
	inline bool operator==(const Action &lhs, const Action &rhs)
	{
		return lhs.myDirection == rhs.myDirection;
	}

class SlidingTile {

public:
	SlidingTile();
	SlidingTile(const int tiles[16]);
	uint32_t Rank(std::vector<int> pattern);
	uint32_t GetMaxRank(std::vector<int> pattern);
	void Unrank(uint32_t rank, const std::vector<int> pattern);
	void GetActions(std::vector<Action> &actions);
	void ApplyAction(Action a);
	void UndoAction(Action a);
	char* Print();
	int InvertAction(Action a);
	int tiles[16];
	
private:
	int blank;
	int width;
};

//overide the == operator for easy comparisons
inline bool operator==(const SlidingTile &lhs, const SlidingTile &rhs)
{
	for (int i = 0; i < 16; i++)
	{
		if (lhs.tiles[i] != rhs.tiles[i])
		{
			return false;
		}
	}
	return true;
}




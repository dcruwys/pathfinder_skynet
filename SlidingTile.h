#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

	enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of puzzle blank

	struct Action{
		direction myDirection; //give an action a direction
		Action(direction directionIN){
			//read a direction in in the constructor and set it to the direction of the Action
			myDirection = directionIN;
		}
	};

class SlidingTile {

public:
	SlidingTile();
	SlidingTile(const int tiles[16]);
	uint64_t Rank(std::vector<int> pattern);
	uint64_t GetMaxRank(std::vector<int> &pattern);
	void Unrank(uint64_t rank);
	void GetActions(SlidingTile &nodeID, std::vector<Action> &actions);
	void ApplyAction(SlidingTile &s, Action a);
	void UndoAction(SlidingTile &s, Action a);
	void Print();
private:
	int blank;
	int tiles[16];
};




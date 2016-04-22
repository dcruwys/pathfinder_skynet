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

class SlidingTile {

public:
	SlidingTile();
	SlidingTile(const int tiles[16]);
	uint64_t Rank(std::vector<int> pattern);
	uint64_t GetMaxRank(std::vector<int> pattern);
	void Unrank(uint64_t rank, const std::vector<int> pattern);
	void GetActions(std::list<Action> &actions);
	void ApplyAction(Action a);
	void UndoAction(Action a);
	char* Print();
	int tiles[16];
private:
	int blank;
	int width;
};




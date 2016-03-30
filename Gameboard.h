
#include <cstdint>
#include <iostream>
#include <vector>


enum direction{ UP, DOWN, LEFT, RIGHT }; //enum to represent possible actions of grid agent

struct State{
	static const int boardSize = 12; //size of grid
	static const int rows = 3; //rows of grid
	static const int cols = 4; //columns of grid
	int agentLoc; //location of agent
	int board[boardSize]; //grid
};

struct Action{
	direction myDirection; //give an action a direction
	Action(direction directionIN){
		//read a direction in in the constructor and set it to the direction of the Action
		myDirection = directionIN;
	}
};

class Gameboard {
	
public:
	Gameboard(){}
	void GetActions(State &nodeID, std::vector<Action> &actions);
	void ApplyAction(State &s, Action a);
	void UndoAction(State &s, Action a);
};

inline bool operator==(const State &lhs, const State &rhs){
	return lhs.agentLoc == rhs.agentLoc;
}


#include "Gameboard.h"

//Gets all possible moves the agent can make
void Gameboard::GetActions(grid::State &nodeID, std::vector<grid::Action> &actions)
{
	//make sure actions list is empty when starting to add actions
	actions.clear();

	//if its not at the top of the grid, let the agent go up
	if (nodeID.agentLoc / nodeID.cols != 0)
	{
		//add up action to list of possible actions
		actions.push_back(grid::Action(direction::UP));
	}
	//if its not at the bottom of the grid, let the agent go down
	if (nodeID.agentLoc / nodeID.cols != nodeID.rows)
	{
		//add down action to list of possible actions
		actions.push_back(grid::Action(direction::DOWN));
	}
	//if its not at the left most side of the grid, let the agent go left
	if (nodeID.agentLoc % nodeID.cols != 0)
	{
		//add left action to list of possible actions
		actions.push_back(grid::Action(direction::LEFT));
	}
	//if its not at the right most side of the grid, let the agent go right
	if (nodeID.agentLoc % nodeID.cols != nodeID.cols - 1)
	{
		//add right action to list of pissible actions
		actions.push_back(grid::Action(direction::RIGHT));
	}
}

void Gameboard::ApplyAction(grid::State &nodeID, grid::Action a)
{
	switch (a.myDirection)
	{
	case direction::UP: nodeID.agentLoc -= nodeID.cols; break;
	case direction::DOWN: nodeID.agentLoc += nodeID.cols; break;
	case direction::LEFT: nodeID.agentLoc -= 1; break;
	case direction::RIGHT: nodeID.agentLoc += 1; break;
	default: std::cout << "invalid direction to apply" << std::endl; break;
	}
}

void Gameboard::UndoAction(grid::State &nodeID, grid::Action a)
{
	switch (a.myDirection)
	{
	case direction::UP: nodeID.agentLoc += nodeID.cols; break;
	case direction::DOWN: nodeID.agentLoc -= nodeID.cols; break;
	case direction::LEFT: nodeID.agentLoc += 1; break;
	case direction::RIGHT: nodeID.agentLoc -= 1; break;
	default: std::cout << "invalid direction to undo" << std::endl; break;
	}
}
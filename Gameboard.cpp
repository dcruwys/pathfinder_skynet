#include "Gameboard.h"

void Gameboard2::GetActions(grid::State &nodeID, std::vector<grid::Action> &actions)
{
	//clear list of actions before adding to it
	actions.clear();

	//if x position isnt at the right edge of the space, then let it go right
	if (nodeID.agentLocX < nodeID.cols - 1)
	{
		actions.push_back(grid::Action(grid::direction::RIGHT));
	}
	//if the y position isnt at the top of the space, let it go up
	if (nodeID.agentLocY < nodeID.rows - 1)
	{
		actions.push_back(grid::Action(grid::direction::UP));
	}
}


void Gameboard2::ApplyAction(grid::State &nodeID, grid::Action a)
{
	//depending which action was passed in, move either right or left
	switch (a.myDirection)
	{
	case grid::direction::UP: nodeID.agentLocY += 1; break;
	case grid::direction::RIGHT: nodeID.agentLocX += 1; break;
	default: std::cout << "invalid direction to apply" << std::endl; break;
	}
}

void Gameboard2::UndoAction(grid::State &nodeID, grid::Action a)
{
	//depending which action was passed in, move either left or down
	switch (a.myDirection)
	{
	case grid::direction::UP: nodeID.agentLocY -= 1; break;
	case grid::direction::RIGHT: nodeID.agentLocX -= 1; break;
	default: std::cout << "invalid direction to undo" << std::endl; break;
	}
}
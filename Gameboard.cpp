#include "Gameboard.h"

void Gameboard::GetActions(Grid::State &nodeID, std::vector<Grid::Action> &actions)
{
	//clear list of actions before adding to it
	actions.clear();

	//if x position isnt at the right edge of the space, then let it go right
	if (nodeID.agentLocX < nodeID.cols - 1)
	{
		actions.push_back(Grid::Action(Grid::direction::RIGHT));
	}
	//if the y position isnt at the top of the space, let it go up
	if (nodeID.agentLocY < nodeID.rows - 1)
	{
		actions.push_back(Grid::Action(Grid::direction::UP));
	}
}


void Gameboard::ApplyAction(Grid::State &nodeID, Grid::Action a)
{
	//depending which action was passed in, move either right or left
	switch (a.myDirection)
	{
	case Grid::direction::UP: nodeID.agentLocY += 1; break;
	case Grid::direction::RIGHT: nodeID.agentLocX += 1; break;
	default: std::cout << "invalid direction to apply" << std::endl; break;
	}
}

void Gameboard::UndoAction(Grid::State &nodeID, Grid::Action a)
{
	//depending which action was passed in, move either left or down
	switch (a.myDirection)
	{
	case Grid::direction::UP: nodeID.agentLocY -= 1; break;
	case Grid::direction::RIGHT: nodeID.agentLocX -= 1; break;
	default: std::cout << "invalid direction to undo" << std::endl; break;
	}
}
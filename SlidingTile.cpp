#include "SlidingTile.h"

void SlidingTile::GetActions(SlidingTile4x4::State &board, std::vector<SlidingTile4x4::Action> &actions)
{
	//clear list of actions before adding to it
	actions.clear();
	
	//push possible actions onto list of actions
	if (board.blankTileX != 0)
	{
		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::LEFT));
	}
	if (board.blankTileX != board.cols - 1)
	{
		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::RIGHT));
	}
	if (board.blankTileY != 0)
	{
		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::DOWN));
	}
	if (board.blankTileY != board.rows - 1)
	{
		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::UP));
	}
}

void SlidingTile::ApplyAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
{
	switch (a.myDirection)
	{
	case SlidingTile4x4::direction::LEFT: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX - 1, s.blankTileY);
		s.blankTileX -= 1;
		break;
	case SlidingTile4x4::direction::RIGHT: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX + 1, s.blankTileY);
		s.blankTileX += 1;
		break;
	case SlidingTile4x4::direction::DOWN: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY - 1);
		s.blankTileY -= 1;
		break;
	case SlidingTile4x4::direction::UP: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX , s.blankTileY + 1);
		s.blankTileY += 1;
		break;
	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
	}
}

void SlidingTile::UndoAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
{
	switch (a.myDirection)
	{
	case SlidingTile4x4::direction::RIGHT: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX - 1, s.blankTileY);
		s.blankTileX -= 1;
		break;
	case SlidingTile4x4::direction::LEFT: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX + 1, s.blankTileY);
		s.blankTileX += 1;
		break;
	case SlidingTile4x4::direction::UP: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY - 1);
		s.blankTileY -= 1;
		break;
	case SlidingTile4x4::direction::DOWN: 
		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY + 1);
		s.blankTileY += 1;
		break;
	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
	}
}
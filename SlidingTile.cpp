#include "SlidingTile.h"

void SlidingTile::GetActions(SlidingTile4x4::State &board, std::vector<SlidingTile4x4::Action> &actions)
{
	//clear list of actions before adding to it
	actions.clear();
	//find if can move left
	if(board.blank % board.size != 0){
        actions.push_back(SlidingTile4x4::direction::LEFT);
	}
    if(board.blank % board.size != 3){
        actions.push_back(SlidingTile4x4::direction::RIGHT);
    }
    if(board.blank / board.size != board.size-1){
        actions.push_back(SlidingTile4x4::direction::DOWN);
    }
    if(board.blank / board.size != 0){
        actions.push_back(SlidingTile4x4::direction::UP);
    }


}

void SlidingTile::ApplyAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
{
    switch(a.myDirection){
        case SlidingTile4x4::direction::LEFT: std::swap(s.board[s.blank], s.board[s.blank-1]); s.blank--;  break;
        case SlidingTile4x4::direction::RIGHT: std::swap(s.board[s.blank], s.board[s.blank+1]); s.blank++; break;
        case SlidingTile4x4::direction::UP: std::swap(s.board[s.blank], s.board[s.blank-s.size]); s.blank -= 4; break;
        case SlidingTile4x4::direction::DOWN: std::swap(s.board[s.blank], s.board[s.blank+s.size]); s.blank += 4; break;
    }
}

void SlidingTile::UndoAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
{
    switch(a.myDirection){
        case SlidingTile4x4::direction::RIGHT: std::swap(s.board[s.blank], s.board[s.blank-1]); s.blank--; break;
        case SlidingTile4x4::direction::LEFT: std::swap(s.board[s.blank], s.board[s.blank+1]); s.blank++; break;
        case SlidingTile4x4::direction::DOWN: std::swap(s.board[s.blank], s.board[s.blank-s.size]); s.blank -= 4; break;
        case SlidingTile4x4::direction::UP: std::swap(s.board[s.blank], s.board[s.blank+s.size]); s.blank += 4; break;
    }
}
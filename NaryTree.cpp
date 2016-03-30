#include "NaryTree.h"

void NaryTree::GetActions(Tree::State &s, std::vector<Tree::Action> &actions)
{
	actions.clear();
	for (int i = 0; i < branchingFactor; ++i)
	{
		actions.push_back(Tree::Action(i));
	}
}

void NaryTree::ApplyAction(Tree::State &s, Tree::Action a)
{
	s.nodeID = s.nodeID * branchingFactor + a.a + 1;
}

void NaryTree::UndoAction(Tree::State &s, Tree::Action a)
{
	s.nodeID = (s.nodeID - a.a - 1) / branchingFactor;
}
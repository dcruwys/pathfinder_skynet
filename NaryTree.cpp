#include "NaryTree.h"

void NaryTree::GetActions(Tree::State &s, std::vector<Tree::Action> &actions)
{
	//clear actions before adding to it
	actions.clear();
	for (int i = 0; i < branchingFactor; ++i)
	{
		//go through all the possible actions and put them into the actions list
		actions.push_back(Tree::Action(i));
	}
}

void NaryTree::ApplyAction(Tree::State &s, Tree::Action a)
{
	//math to compute the value of a generated node
	s.nodeID = s.nodeID * branchingFactor + a.a + 1;
}

void NaryTree::UndoAction(Tree::State &s, Tree::Action a)
{
	//opposite math of generating a new node
	s.nodeID = (s.nodeID - a.a - 1) / branchingFactor;
}
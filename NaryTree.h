
#pragma once
#include <iostream>
#include <vector>

//namespace tree for state and action so as not to confuse with other environment
namespace Tree{
	struct State{
		int nodeID;
		State(){}
		State(int nodeIN)
		{
			nodeID = nodeIN;
		}
	};

	//overide the == operator for easy comparisons
	inline bool operator==(const State &lhs, const State &rhs)
	{
		return lhs.nodeID == rhs.nodeID;
	}

	//an action
	struct Action
	{
		int a;
		Action(int in)
		{
			a = in;
		}
	};
}



class NaryTree
{
public:
	int branchingFactor;
	void GetActions(Tree::State &s, std::vector<Tree::Action> &actions);
	void ApplyAction(Tree::State &s, Tree::Action a);
	void UndoAction(Tree::State &s, Tree::Action a);
};


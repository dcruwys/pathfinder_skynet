#include <iostream>
#include <vector>

namespace Tree{
	struct State{
		int nodeID;
		State(){}
		State(int nodeIN)
		{
			nodeID = nodeIN;
		}
	};


	inline bool operator==(const State &lhs, const State &rhs)
	{
		return lhs.nodeID == rhs.nodeID;
	}

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


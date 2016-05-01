#ifndef OpenClosedList_h
#define OpenClosedList_h
#include "OctileGrid.h"

//TODO: Where to check duplicates from? Open? Closed? Both?

template <typename state>
class OpenClosedList
{
public:
	void addOpen(state &c);
	void addClosed(state &c);
	bool checkDuplicates(state &c);
	void updateCost();
	state removeBest();
	bool OpenEmpty();
private:
	std::vector<state> open;
	std::vector<state> closed;
};
template <typename state>
void OpenClosedList::addOpen(state &c)
{
	open.push_back(c);
}

template <typename state>
void OpenClosedList::addClosed(state &c)
{
    //make sure we remove from open too.
	closed.push_back(c);
}
template <typename state>
state OpenClosedList::checkDuplicates(state &c)
{
    state best = c;
	for (int i = 0; i < open.size(); i++)
	{
		if (open[i] == c)
		{
            if(open[i].fcost < c.fcost)
                best = open[i];
		}
	}
	return best;
}

template <typename state>
void OpenClosedList::updateCost()
{

}

template <typename state>
state OpenClosedList::removeBest()
{
	state best = open[0];
    int index = 0;
	for (int i = 1; i < open.size(); i++)
	{
		if (open[i].fcost < best.fcost)
		{   index = i;
			best = open[i];
		}
	}
    open.erase(open.begin()+(index-1));
	return best;
}

template <typename state>
bool OpenClosedList::OpenEmpty()
{
	return open.empty();
}
#endif
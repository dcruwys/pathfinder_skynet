#ifndef OpenClosedList_h
#define OpenClosedList_h
#include "OctileGrid.h"

//TODO: do we need to create a struct to hold coordinate and cost?
//TODO: Where to check duplicates from? Open? Closed? Both?

struct node
{
	coordinate loc;
	int gcost;
	int hcost;
	int fcost;
};

class OpenClosedList
{
public:
	void addOpen(node &c);
	void addClosed(node &c);
	bool checkDuplicates(node &c);
	void updateCost();
	node removeBest();
	bool OpenEmpty();
private:
	std::vector<node> open;
	std::vector<node> closed;
};

void OpenClosedList::addOpen(node &c)
{
	open.push_back(c);
}

void OpenClosedList::addClosed(node &c)
{
	closed.push_back(c);
}

bool OpenClosedList::checkDuplicates(node &c)
{
	//TODO: make check for more than just 1 duplicate
	for (int i = 0; i < open.size(); i++)
	{
		if (open[i].loc == c.loc)
		{
			return true;
		}
	}
	return false;
}

void OpenClosedList::updateCost()
{

}

node OpenClosedList::removeBest()
{
	node best = open[0];
	for (int i = 0; i < open.size(); i++)
	{
		if (open[i].fcost < best.fcost)
		{
			best = open[i];
		}
	}
	//TODO: remove best from open list
	return best;
}

bool OpenClosedList::OpenEmpty()
{
	return open.empty();
}
#endif
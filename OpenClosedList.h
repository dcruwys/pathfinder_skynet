#ifndef OpenClosedList_h
#define OpenClosedList_h
#include "OctileGrid.h"

//TODO: do we need to create a struct to hold coordinate and cost?
//TODO: Where to check duplicates from? Open? Closed? Both?

class OpenClosedList
{
public:
	void addOpen(coordinate &c);
	void addClosed(coordinate &c);
	bool checkDuplicates(coordinate &c);
	void updateCost();
	coordinate removeBest();
	bool OpenEmpty();
private:
	std::vector<coordinate> open;
	std::vector<coordinate> closed;
};

void OpenClosedList::addOpen(coordinate &c)
{
	open.push_back(c);
}

void OpenClosedList::addClosed(coordinate &c)
{
	closed.push_back(c);
}

bool OpenClosedList::checkDuplicates(coordinate &c)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (open[i] == c)
		{
			return true;
		}
	}
	return false;
}

void OpenClosedList::updateCost()
{

}

coordinate OpenClosedList::removeBest()
{
	
}

bool OpenClosedList::OpenEmpty()
{
	return open.empty();
}
#endif
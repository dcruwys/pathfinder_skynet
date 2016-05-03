#ifndef OpenClosedList_h
#define OpenClosedList_h

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
void OpenClosedList<state>::addOpen(state &c)
{
	open.push_back(c);
}

template <typename state>
void OpenClosedList<state>::addClosed(state &c)
{
    //make sure we remove from open too.
	closed.push_back(c);
}
template <typename state>
bool OpenClosedList<state>::checkDuplicates(state &c)
{
	//if a node on the open list has same coordinates as successor and has a
	//lower f cost than successor, then skip this successor

	for (int i = 0; i < open.size(); i++)
	{
		if (open[i] == c)
		{
            if(open[i].fcost < c.fcost)
                return false;
		}
	}
    //if a node on the closed list has same coordinates and lower fcost than
    //successor, skip this successor.
    state best = c;
    for (int i = 0; i < closed.size(); i++)
    {
        if (closed[i] == c)
        {
            if(open[i].fcost < c.fcost)
                return false;
        }
    }
    //otherwise add node to open list
    addOpen(c);
    return true;

}

template <typename state>
state OpenClosedList<state>::removeBest()
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
bool OpenClosedList<state>::OpenEmpty()
{
	return open.empty();
}
#endif
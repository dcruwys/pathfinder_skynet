#ifndef Astar_h
#define Astar_h

template<typename state, typename action, typename environment>
class Astar
{
public:
	bool getPath(environment &e, state &start, state &goal);
private:
};

template<typename state, typename action, typename environment>
bool Astar<state, action, environment>::getPath(environment &e, state &start, state &goal)
{
	
}

#endif
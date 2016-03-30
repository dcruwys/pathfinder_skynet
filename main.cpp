#include <iostream>
#include "NaryTree.h"
#include "Gameboard.h"

using namespace std;

int main() {

    NaryTree tree = NaryTree();
    NaryTree::Action
    NaryTree::State initial = new NaryTree::State(0);
    NaryTree::State goal = new NaryTree::State(8);
    BFS<NaryTree::State, NaryTree::Action, NaryTree> search = new BFS<NaryTree::State, NaryTree::Action, NaryTree>();
    uint8_t nodesExpanded;
    if(search.GetPath(tree, intial, goal))
    {
        nodesExpanded = search.GetNodesExpanded();
    }
    std::cout << nodesExpanded << std::endl;


    std::getchar();
    return 0;
}

//////////////////
//TODO:
//Nary Tree
//DFS, BFS, DFIS
/////////////////
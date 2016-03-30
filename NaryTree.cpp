//
// Created by Dan on 3/29/16.
//

#include "NaryTree.h"

void NaryTree::GetActions(Node &nodeID, std::vector<Edge> &actions) {
    actions.clear();
    for(int i = 0; i < b; ++i){
        actions.push_back(Edge(i));
    }
}

void NaryTree::ApplyAction(Node &s, Edge a) {
    Node temp(-1);
    temp.nodeID = s.nodeID*b + a.a + 1;
    s = temp;

}

void NaryTree::UndoAction(Node &s, Edge a) {
    Node temp(-1);
    temp.nodeID = (s.nodeID-a.a-1)/b;
}

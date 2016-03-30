//
// Created by Dan Cruwys on 3/29/16.
//

#ifndef HW1_NARYTREE_H
#define HW1_NARYTREE_H


#include <cstdint>
#include <iostream>
#include <vector>

struct Node{
    uint8_t nodeID;
    Node(uint8_t nodein) {
        nodeID = nodein;
    }
};
inline bool operator==(const Node& lhs, const Node& rhs){ return lhs.nodeID == rhs.nodeID; }

struct Edge{
    uint8_t a; //action number
    Edge(uint8_t in){
        a = in;
    }

};

class NaryTree {
    public:
        uint8_t b; //branching factor
        void GetActions(Node &nodeID, std::vector<Edge> &actions);
        void ApplyAction(Node &s, Edge a);
        void UndoAction(Node &s, Edge a);
};


#endif //HW1_NARYTREE_H

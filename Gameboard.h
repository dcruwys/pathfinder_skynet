
#ifndef HW1_GAMEBOARD_H
#define HW1_GAMEBOARD_H


#include <cstdint>
#include <iostream>
#include <vector>

struct State{
    static const uint32_t boardSize = 10; //size of grid
    uint32_t board [boardSize][boardSize]; //2D array of grid
    uint8_t agentX; //x location of agent
    uint8_t agentY; //y location of agent
};

struct Action{
    // 0 = up, 1 = down, 2 = left, 3 = right
    uint8_t direction;
    Action(uint8_t directionIN){
        direction = directionIN;
    }
};

class Gameboard {
public:
    void GetActions(State &nodeID, std::vector<Action> &actions);
    void ApplyAction(State &s, Action a);
    void UndoAction(State &s, Action a);
};


#endif //HW1_GAMEBOARD_H

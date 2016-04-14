#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <math.h>
namespace SlidingTile4x4 {
    enum direction {
        UP, DOWN, LEFT, RIGHT
    }; //enum to represent possible actions of puzzle blank


    struct State {
        std::vector<int> board;
        int blank;
        int size;
        direction lastAction;

        State(std::vector<int> in) {
            board = in;
            size = sqrt(board.size());
            auto i = find(in.begin(), in.end(), 0);
            blank = distance(in.begin(), i);
            std::cout << "Blank is at: " << blank << std::endl;
        }
    };

    inline bool operator==(const State &lhs, const State &rhs) {
        return lhs.board == rhs.board;
    }

    struct Action {
        direction myDirection; //give an action a direction
        Action() { }

        Action(direction directionIN) {
            //read a direction in in the constructor and set it to the direction of the Action
            myDirection = directionIN;
        }
    };
    inline bool operator!=(const Action &lhs, const Action &rhs) {
        return lhs.myDirection != rhs.myDirection;
    }

}
class SlidingTile {

public:
	SlidingTile(){}
	void GetActions(SlidingTile4x4::State &nodeID, std::vector<SlidingTile4x4::Action> &actions);
	void ApplyAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a);
	void UndoAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a);
};




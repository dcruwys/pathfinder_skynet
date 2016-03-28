

#include "Gameboard.h"
//Gets all possible moves the agent can make
void Gameboard::GetActions(State &nodeID, std::vector<Action> &actions){
    actions.clear();
    if(nodeID.agentY < nodeID.boardSize){
        actions.push_back(Action(0));
    } if(nodeID.agentY > 0){
        actions.push_back(Action(1));
    } if(nodeID.agentX < nodeID.boardSize){
        actions.push_back(Action(3));
    } if(nodeID.agentX > 0){
        actions.push_back(Action(2));
    }
}

//Applys the action
void Gameboard::ApplyAction(State &s, Action a){
    s.board[s.agentX][s.agentY] = 0;
    if(a.direction == 0){ //up
       s.agentY += 1;
    } if(a.direction == 1){ //down
        s.agentY -= 1;
    } if(a.direction == 2){//left
        s.agentX -= 1;
    } if(a.direction == 3){//right
        s.agentX += 1;
    }
    s.board[s.agentX][s.agentY] = 1;
}

//Undos the action
void Gameboard::UndoAction(State &s, Action a){
    s.board[s.agentX][s.agentY] = 0;
    if(a.direction == 0){ //up (down)
        s.agentY -= 1;
    } if(a.direction == 1){ //down (up)
        s.agentY += 1;
    } if(a.direction == 2){//left (right)
        s.agentX += 1;
    } if(a.direction == 3){//right (left)
        s.agentX -= 1;
    }
    s.board[s.agentX][s.agentY] = 1;
}

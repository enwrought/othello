#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Side side;
    Board* board;
    float eval_board(Board* prop_board);
    vector<Move*> get_all_moves(Side side, Board* prop_board);
    float minimax(Board* b, Side s, int ply);
};

#endif

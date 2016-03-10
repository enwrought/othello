#include "player.h"
#include <vector>

using namespace std;

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->side = side;
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}



/**
 * @brief: Return list of all possible moves.
 */
vector<Move*> Player::get_all_moves(Side side, Board* prop_board) {
    vector<Move*> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *new_move = new Move(i, j);
            if (prop_board->checkMove(new_move, side)) 
                moves.push_back(new_move);
            else
                delete new_move;
        }
    }
    return moves;
}



/**
 * @brief: Evaluate the passed in board
 */
float Player::eval_board(Board* prop_board){
    // TODO later: change to better heuristic
    Side oppSide = side == WHITE ? BLACK : WHITE;
    return prop_board->count(side) - prop_board->count(oppSide);
}



/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    // For now, ignore the time

    // Do move from opponent
    if (side == WHITE)
        board->doMove(opponentsMove, BLACK);
    else
        board->doMove(opponentsMove, WHITE);
    
    // If minimax, move all possibilities
    if (testingMinimax) {
        // TODO: choose best of all possible moves
        //
        // tmp return:
        // return doMove(oponentsMove, msLeft);
    }
    else {
        // Just choose the best move out of the list of moves
        float best_score = -64;
        Move *best_move = NULL;
        vector<Move*> moves = get_all_moves(side, board);
        for (unsigned int i = 0; i < moves.size(); i++) {
            Board* new_board = board->copy();
            new_board->doMove(moves[i], side);
            float board_val = eval_board(new_board);
            if (board_val > best_score) {
                best_score = board_val;
                best_move = moves[i];
            }
        }
        board->doMove(best_move, side);
        return best_move;
    }

    return NULL;
}

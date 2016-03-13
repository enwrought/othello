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
vector<Move*> Player::get_all_moves(Side s, Board* prop_board) {
    vector<Move*> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *new_move = new Move(i, j);
            if (prop_board->checkMove(new_move, s)) 
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
    /*
    Side oppSide = side == WHITE ? BLACK : WHITE;
    return prop_board->count(side) - prop_board->count(oppSide);
    */
    return prop_board->get_board_value(side);
}


// it is side s's turn to make a move
float Player::minimax(Board* b, Side s, int ply, float alpha, float beta) {
    if (ply == 0)
        return eval_board(b);

    Side opp = s == WHITE ? BLACK : WHITE; 
    vector<Move*> moves = get_all_moves(s, b);
    // choose the one that minimizes the value of next move
    if (moves.size() == 0)
        return eval_board(b);
    float best_score = s == side ? -100 : 100;
    for (unsigned int i = 0; i < moves.size(); i++) {
        Board* new_board = b->copy();
        new_board->doMove(moves[i], s);
        float board_val = minimax(new_board, opp, ply-1, alpha, beta);
        delete new_board;
        if (s == side) {
            // maximizing player
            if (board_val >= best_score) {
                best_score = board_val;
                if (best_score > alpha)
                    alpha = best_score;
                if (beta <= alpha)
                    break;
            }
        }
        else {
            if (board_val <= best_score) {
                best_score = board_val;
                if (best_score < beta)
                    beta = best_score;
                if (beta <= alpha)
                    break;
            }
        }
    }
    return best_score;
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
    Side opp = side == WHITE ? BLACK : WHITE;
    board->doMove(opponentsMove, opp);
    
    int ply = 6;
    if (testingMinimax)
        ply = 2;

    float best_score = -100;
    Move *best_move = NULL;
    vector<Move*> moves = get_all_moves(side, board);
    for (unsigned int i = 0; i < moves.size(); i++) {
        Board* new_board = board->copy();
        new_board->doMove(moves[i], side);
        float board_val = minimax(new_board, opp, ply-1, -64, 64);

        delete new_board;
        if (board_val >= best_score) {
            best_score = board_val;
            delete best_move;
            best_move = moves[i];
        }
        else {
            delete moves[i];
        }
    }
    if (best_move == NULL)
        cerr << "enwrought: passed? number of possible moves:" << 
            moves.size() << endl;
    else
        cerr << "enwrought moved: (" << best_move->x << "," << best_move->y
        << ")" << endl;
    board->doMove(best_move, side);
    return best_move;
}

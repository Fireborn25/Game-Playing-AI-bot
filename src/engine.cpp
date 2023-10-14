#include <iostream>
#include <algorithm>
#include <iostream>
#include <climits>

#include "board.hpp"
#include "engine.hpp"
using namespace std;

// Define your scoring function
int evaluate(const Board &b)
{
    int val = 0;
    int mul = 1;
    if (b.data.player_to_play == BLACK){
        mul = -1;
    }
    if (b.data.b_bishop == DEAD){
        val += 400;
    }
    if (b.data.w_bishop == DEAD){
        val -= 400;
    }
    if (b.data.b_rook_ws == DEAD){
        val += 500;
    }
    if (b.data.w_rook_ws == DEAD){
        val -= 500;
    }
    if (b.data.b_rook_bs == DEAD){
        val += 500;
    }
    if (b.data.w_rook_bs == DEAD){
        val -= 500;
    }
    if (b.data.b_pawn_ws == DEAD){
        val += 100;
    }
    else{
        val += (getx(b.data.b_pawn_ws)-3);
        val += min(gety(b.data.b_pawn_ws),abs(gety(b.data.b_pawn_ws) - 1));
    }
    if (b.data.w_pawn_ws == DEAD){
        val -= 100;
    }
    else{
        val -= (4-getx(b.data.w_pawn_ws));
        val -= min(abs(gety(b.data.w_pawn_ws -5)),abs(gety(b.data.w_pawn_ws) - 6));
    }
    if (b.data.b_pawn_bs == DEAD){
        val += 100;
    }
    else{
        val += (getx(b.data.b_pawn_bs)-3);
        val += min(gety(b.data.b_pawn_bs),abs(gety(b.data.b_pawn_bs) - 1));
    }
    if (b.data.w_pawn_bs == DEAD){
        val -= 100;
    }
    else{
        val -= (4-getx(b.data.b_pawn_ws));
        val -= min(abs(gety(b.data.b_pawn_ws -5)),abs(gety(b.data.b_pawn_ws) - 6));
    }
    return val*mul;
}

// Recursive minimax search with alpha-beta pruning
int minimax(Board &b, int depth, int alpha, int beta, bool maximizingPlayer, int check)
{
    auto legalMoves = b.get_legal_moves();
    if (legalMoves.size() == 0){
        if (maximizingPlayer){
            return INT_MIN;
        }
        return INT_MAX;
    }
    int mul = 1;
    if (depth%2 == 0){
        mul = -1;
    }
    check += 15*mul*b.in_check();
    if (depth == 0)
    {
        return evaluate(b) + legalMoves.size() + check;
    }

    if (maximizingPlayer)
    {
        int maxEval = INT_MIN;
        for (U16 move : legalMoves)
        {
            Board *childBoard = b.copy();
            (*childBoard).do_move(move);
            int eval = minimax(*childBoard, depth - 1, alpha, beta, false, check);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return maxEval;
    }
    else{
        int minEval = INT_MAX;
        for (U16 move : legalMoves)
        {
            Board *childBoard = b.copy();
            (*childBoard).do_move(move);
            int eval = minimax(*childBoard, depth - 1, alpha, beta, true, check);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return minEval;
    }
}

void Engine::find_best_move(const Board &b)
{
    int bestScore = INT_MIN;
    auto legalMoves = b.get_legal_moves();
    int alpha = INT_MIN;
    for (U16 move : legalMoves)
    {
        Board *childBoard = b.copy();
        childBoard->do_move(move);
        int score = minimax(*childBoard, 3, alpha, INT_MAX, false,0); // Depth 4 ply
        alpha = max(score,alpha);
        if (score > bestScore)
        {
            bestScore = score;
            this->best_move = move;
        }
    }

}

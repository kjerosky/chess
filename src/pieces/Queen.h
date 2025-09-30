#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {

public:

    Queen(PieceColor c, BoardLocation location);
    virtual ~Queen() override;
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

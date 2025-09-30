#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

public:

    Pawn(PieceColor c, BoardLocation location);
    virtual ~Pawn() override;
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

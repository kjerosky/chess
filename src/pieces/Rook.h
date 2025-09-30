#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {

public:

    Rook(PieceColor c, BoardLocation location);
    virtual ~Rook();
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

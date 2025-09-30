#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

public:

    Knight(PieceColor c, BoardLocation location);
    virtual ~Knight() override;
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

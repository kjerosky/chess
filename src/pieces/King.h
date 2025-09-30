#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

public:

    King(PieceColor c, BoardLocation location);
    virtual ~King() override;
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

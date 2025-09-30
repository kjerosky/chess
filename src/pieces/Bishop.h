#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {

public:

    Bishop(PieceColor c, BoardLocation location);
    virtual ~Bishop();
    
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) override;
};

#endif

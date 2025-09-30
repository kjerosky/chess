#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {

public:

    Bishop(PieceColor color, BoardLocation location);
    virtual ~Bishop();
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) override;
    virtual bool is_capturable() const override;
};

#endif

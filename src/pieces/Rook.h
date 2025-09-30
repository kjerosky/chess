#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {

public:

    Rook(PieceColor color, BoardLocation location);
    virtual ~Rook();
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) override;
    virtual bool is_capturable() const override;
};

#endif

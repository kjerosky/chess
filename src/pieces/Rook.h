#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {

public:

    Rook(PieceColor color, BoardLocation location);
    virtual ~Rook();
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) override;
    virtual int get_piece_texture_index() const override;
};

#endif

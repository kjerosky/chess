#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

public:

    King(PieceColor color, BoardLocation location);
    virtual ~King() override;
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) override;
    virtual bool is_capturable() const override;
    virtual int get_piece_texture_index() const override;
};

#endif

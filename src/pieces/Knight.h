#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

public:

    Knight(PieceColor color, BoardLocation location);
    virtual ~Knight() override;
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) override;
    virtual bool is_capturable() const override;
    virtual int get_piece_texture_index() const override;
};

#endif

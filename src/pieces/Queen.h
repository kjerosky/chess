#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {

public:

    Queen(PieceColor color, BoardLocation location);
    virtual ~Queen() override;
    
    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) override;
    virtual bool is_capturable() const override;
};

#endif

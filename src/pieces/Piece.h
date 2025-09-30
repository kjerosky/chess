#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "../BoardLocation.h"

enum class PieceColor {
    WHITE,
    BLACK
};

// --------------------------------------------------------------------------

class Piece {

public:

    Piece(PieceColor c, BoardLocation location);

    virtual ~Piece() = 0;

    // Gets the possible moves for the piece in isolation, as if no other pieces are on the board.
    virtual void get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) = 0;

    PieceColor get_color() const;

protected:

    BoardLocation location;
    PieceColor color;
    
    void add_directional_moves(int board_width, int board_height, const BoardLocation& current_pos, 
                               int dx, int dy, std::vector<BoardLocation>& possible_moves);
};

#endif

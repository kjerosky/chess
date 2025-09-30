#include "Piece.h"

Piece::Piece(PieceColor c, BoardLocation location)
:
color(c),
location(location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Piece::~Piece() = default;

// --------------------------------------------------------------------------

PieceColor Piece::get_color() const {
    return color;
}

// --------------------------------------------------------------------------

void Piece::add_directional_moves(int board_width, int board_height, const BoardLocation& current_pos, 
                                  int dx, int dy, std::vector<BoardLocation>& possible_moves) {
    int x = current_pos.x + dx;
    int y = current_pos.y + dy;
    
    // Keep moving in the direction until we hit the board edge
    while (x >= 0 && x < board_width && y >= 0 && y < board_height) {
        possible_moves.push_back({x, y});
        x += dx;
        y += dy;
    }
}



#include "Rook.h"

Rook::Rook(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Rook::~Rook() = default;

// --------------------------------------------------------------------------

void Rook::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // Rook moves horizontally and vertically
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Horizontal and vertical moves
    add_directional_moves(board_width, board_height, location, 1, 0, possible_moves);  // Right
    add_directional_moves(board_width, board_height, location, -1, 0, possible_moves); // Left
    add_directional_moves(board_width, board_height, location, 0, 1, possible_moves);  // Up
    add_directional_moves(board_width, board_height, location, 0, -1, possible_moves); // Down
}

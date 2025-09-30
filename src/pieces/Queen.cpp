#include "Queen.h"

Queen::Queen(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Queen::~Queen() = default;

// --------------------------------------------------------------------------

void Queen::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // Queen moves like a rook + bishop combined
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Rook moves (horizontal and vertical)
    add_directional_moves(board_width, board_height, location, 1, 0, possible_moves);  // Right
    add_directional_moves(board_width, board_height, location, -1, 0, possible_moves); // Left
    add_directional_moves(board_width, board_height, location, 0, 1, possible_moves);  // Up
    add_directional_moves(board_width, board_height, location, 0, -1, possible_moves); // Down
    
    // Bishop moves (diagonal)
    add_directional_moves(board_width, board_height, location, 1, 1, possible_moves);  // Up-right
    add_directional_moves(board_width, board_height, location, -1, 1, possible_moves); // Up-left
    add_directional_moves(board_width, board_height, location, 1, -1, possible_moves); // Down-right
    add_directional_moves(board_width, board_height, location, -1, -1, possible_moves); // Down-left
}


#include "Bishop.h"

Bishop::Bishop(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Bishop::~Bishop() = default;

// --------------------------------------------------------------------------

void Bishop::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // Bishop moves diagonally
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Diagonal moves
    add_directional_moves(board_width, board_height, location, 1, 1, possible_moves);  // Up-right
    add_directional_moves(board_width, board_height, location, -1, 1, possible_moves); // Up-left
    add_directional_moves(board_width, board_height, location, 1, -1, possible_moves); // Down-right
    add_directional_moves(board_width, board_height, location, -1, -1, possible_moves); // Down-left
}


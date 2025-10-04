#include "Bishop.h"

Bishop::Bishop(PieceColor color, BoardLocation location)
:
Piece(PieceType::BISHOP, color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Bishop::~Bishop() = default;

// --------------------------------------------------------------------------

void Bishop::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) {
    // Bishop moves diagonally
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Diagonal moves
    add_directional_moves(board_width, board_height, active_pieces, 1, 1, possible_moves);  // Up-right
    add_directional_moves(board_width, board_height, active_pieces, -1, 1, possible_moves); // Up-left
    add_directional_moves(board_width, board_height, active_pieces, 1, -1, possible_moves); // Down-right
    add_directional_moves(board_width, board_height, active_pieces, -1, -1, possible_moves); // Down-left
}

// --------------------------------------------------------------------------

bool Bishop::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Bishop::get_piece_texture_index() const {
    return 2;
}


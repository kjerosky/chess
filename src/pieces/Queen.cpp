#include "Queen.h"

Queen::Queen(PieceColor color, BoardLocation location)
:
Piece(color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Queen::~Queen() = default;

// --------------------------------------------------------------------------

void Queen::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) {
    // Queen moves like a rook + bishop combined
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Rook moves (horizontal and vertical)
    add_directional_moves(board_width, board_height, active_pieces, 1, 0, possible_moves);  // Right
    add_directional_moves(board_width, board_height, active_pieces, -1, 0, possible_moves); // Left
    add_directional_moves(board_width, board_height, active_pieces, 0, 1, possible_moves);  // Up
    add_directional_moves(board_width, board_height, active_pieces, 0, -1, possible_moves); // Down
    
    // Bishop moves (diagonal)
    add_directional_moves(board_width, board_height, active_pieces, 1, 1, possible_moves);  // Up-right
    add_directional_moves(board_width, board_height, active_pieces, -1, 1, possible_moves); // Up-left
    add_directional_moves(board_width, board_height, active_pieces, 1, -1, possible_moves); // Down-right
    add_directional_moves(board_width, board_height, active_pieces, -1, -1, possible_moves); // Down-left
}

// --------------------------------------------------------------------------

bool Queen::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Queen::get_piece_texture_index() const {
    return 1;
}


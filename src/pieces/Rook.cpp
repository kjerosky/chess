#include "Rook.h"

Rook::Rook(PieceColor color, BoardLocation location)
:
Piece(color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Rook::~Rook() = default;

// --------------------------------------------------------------------------

void Rook::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) {
    // Rook moves horizontally and vertically
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Horizontal and vertical moves
    add_directional_moves(board_width, board_height, active_pieces, 1, 0, possible_moves);  // Right
    add_directional_moves(board_width, board_height, active_pieces, -1, 0, possible_moves); // Left
    add_directional_moves(board_width, board_height, active_pieces, 0, 1, possible_moves);  // Up
    add_directional_moves(board_width, board_height, active_pieces, 0, -1, possible_moves); // Down
}

// --------------------------------------------------------------------------

bool Rook::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Rook::get_piece_texture_index() const {
    return 4;
}

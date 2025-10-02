#include "Pawn.h"

Pawn::Pawn(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Pawn::~Pawn() = default;

// --------------------------------------------------------------------------

void Pawn::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) {
    // Pawn moves forward one square, or two squares on first move
    // For now, we'll implement basic forward movement without considering captures or other pieces
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Determine direction based on color
    int move_direction = (color == PieceColor::WHITE) ? 1 : -1;
    
    // Check if this is the pawn's starting position (for two-square move)
    bool is_starting_position = (color == PieceColor::WHITE && location.y == 1) || (color == PieceColor::BLACK && location.y == 6);
    
    // Build destinations vector
    std::vector<BoardLocation> destinations;
    
    // One square forward
    int one_square_ahead_y = location.y + move_direction;
    if (one_square_ahead_y >= 0 && one_square_ahead_y < board_height) {
        destinations.push_back({location.x, one_square_ahead_y});
        
        // Two squares forward on first move
        if (is_starting_position) {
            int two_squares_ahead_y = location.y + (2 * move_direction);
            if (two_squares_ahead_y >= 0 && two_squares_ahead_y < board_height) {
                destinations.push_back({location.x, two_squares_ahead_y});
            }
        }
    }

    //TODO need to handle en passant
    
    process_possible_destinations(board_width, board_height, active_pieces, destinations, possible_moves);
}

// --------------------------------------------------------------------------

bool Pawn::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Pawn::get_piece_texture_index() const {
    return 5;
}

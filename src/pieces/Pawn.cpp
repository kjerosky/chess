#include "Pawn.h"

Pawn::Pawn(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Pawn::~Pawn() = default;

// --------------------------------------------------------------------------

void Pawn::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // Pawn moves forward one square, or two squares on first move
    // For now, we'll implement basic forward movement without considering captures or other pieces
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Determine direction based on color
    int move_direction = (color == PieceColor::WHITE) ? 1 : -1;
    
    // Check if this is the pawn's starting position (for two-square move)
    bool is_starting_position = (color == PieceColor::WHITE && location.y == 1) || (color == PieceColor::BLACK && location.y == 6);
    
    // One square forward
    int new_y = location.y + move_direction;
    if (new_y >= 0 && new_y < board_height) {
        possible_moves.push_back({location.x, new_y});
        
        // Two squares forward on first move
        if (is_starting_position) {
            int two_squares_y = location.y + (2 * move_direction);
            if (two_squares_y >= 0 && two_squares_y < board_height) {
                possible_moves.push_back({location.x, two_squares_y});
            }
        }
    }
}

#include "King.h"

King::King(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

King::~King() = default;

// --------------------------------------------------------------------------

void King::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // King moves one square in any direction
    
    // Clear any existing moves
    possible_moves.clear();
    
    // All 8 possible king moves (precomputed actual positions)
    BoardLocation possible_destinations[] = {
        {location.x + 1, location.y},   // Right
        {location.x - 1, location.y},   // Left
        {location.x, location.y + 1},   // Up
        {location.x, location.y - 1},   // Down
        {location.x + 1, location.y + 1},   // Up-right
        {location.x - 1, location.y + 1},   // Up-left
        {location.x + 1, location.y - 1},   // Down-right
        {location.x - 1, location.y - 1}    // Down-left
    };
    
    // Check each possible move
    for (const BoardLocation& move : possible_destinations) {
        // Check if the move is within board bounds
        if (move.x >= 0 && move.x < board_width && move.y >= 0 && move.y < board_height) {
            possible_moves.push_back(move);
        }
    }
}

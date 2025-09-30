#include "King.h"

King::King(PieceColor color, BoardLocation location)
:
Piece(color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

King::~King() = default;

// --------------------------------------------------------------------------

void King::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) {
    // King moves one square in any direction
    
    // Clear any existing moves
    possible_moves.clear();
    
    // All 8 possible king moves (precomputed actual positions)
    std::vector<BoardLocation> destinations = {
        {location.x + 1, location.y},   // Right
        {location.x - 1, location.y},   // Left
        {location.x, location.y + 1},   // Up
        {location.x, location.y - 1},   // Down
        {location.x + 1, location.y + 1},   // Up-right
        {location.x - 1, location.y + 1},   // Up-left
        {location.x + 1, location.y - 1},   // Down-right
        {location.x - 1, location.y - 1}    // Down-left
    };
    
    process_possible_destinations(board_width, board_height, active_pieces, destinations, possible_moves);
}

// --------------------------------------------------------------------------

bool King::is_capturable() const {
    return false;
}

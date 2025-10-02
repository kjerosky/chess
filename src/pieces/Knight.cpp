#include "Knight.h"

Knight::Knight(PieceColor color, BoardLocation location)
:
Piece(color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Knight::~Knight() = default;

// --------------------------------------------------------------------------

void Knight::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) {
    // Knight moves in L-shapes (2 squares in one direction, then 1 square perpendicular)
    
    // Clear any existing moves
    possible_moves.clear();
    
    // All 8 possible knight moves (precomputed actual positions)
    std::vector<BoardLocation> destinations = {
        {location.x + 2, location.y + 1},   // Right 2, up 1
        {location.x + 2, location.y - 1},   // Right 2, down 1
        {location.x - 2, location.y + 1},   // Left 2, up 1
        {location.x - 2, location.y - 1},   // Left 2, down 1
        {location.x + 1, location.y + 2},   // Right 1, up 2
        {location.x + 1, location.y - 2},   // Right 1, down 2
        {location.x - 1, location.y + 2},   // Left 1, up 2
        {location.x - 1, location.y - 2}    // Left 1, down 2
    };
    
    process_possible_destinations(board_width, board_height, active_pieces, destinations, possible_moves);
}

// --------------------------------------------------------------------------

bool Knight::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Knight::get_piece_texture_index() const {
    return 3;
}

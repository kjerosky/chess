#include "Knight.h"

Knight::Knight(PieceColor c, BoardLocation location)
:
Piece(c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Knight::~Knight() = default;

// --------------------------------------------------------------------------

void Knight::get_possible_moves(int board_width, int board_height, std::vector<BoardLocation>& possible_moves) {
    // Knight moves in L-shapes (2 squares in one direction, then 1 square perpendicular)
    
    // Clear any existing moves
    possible_moves.clear();
    
    // All 8 possible knight moves (precomputed actual positions)
    BoardLocation possible_destinations[] = {
        {location.x + 2, location.y + 1},   // Right 2, up 1
        {location.x + 2, location.y - 1},   // Right 2, down 1
        {location.x - 2, location.y + 1},   // Left 2, up 1
        {location.x - 2, location.y - 1},   // Left 2, down 1
        {location.x + 1, location.y + 2},   // Right 1, up 2
        {location.x + 1, location.y - 2},   // Right 1, down 2
        {location.x - 1, location.y + 2},   // Left 1, up 2
        {location.x - 1, location.y - 2}    // Left 1, down 2
    };
    
    // Check each possible move
    for (const BoardLocation& move : possible_destinations) {
        // Check if the move is within board bounds
        if (move.x >= 0 && move.x < board_width && move.y >= 0 && move.y < board_height) {
            possible_moves.push_back(move);
        }
    }
}

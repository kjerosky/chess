#include "King.h"

King::King(PieceColor color, BoardLocation location)
:
Piece(PieceType::KING, color, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

King::~King() = default;

// --------------------------------------------------------------------------

void King::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) {
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

    check_for_castling(active_pieces, possible_moves);
}

// --------------------------------------------------------------------------

int King::get_piece_texture_index() const {
    return 0;
}

// --------------------------------------------------------------------------

void King::check_for_castling(const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) {
    //todo also return right away if king is in check
    if (has_been_moved()) {
        return;
    }

    std::vector<Piece*> castling_rooks;
    for (Piece* piece : active_pieces) {
        if (piece->get_type() == PieceType::ROOK && piece->get_color() == color && !piece->has_been_moved()) {
            castling_rooks.push_back(piece);
        }
    }
    
    for (Piece* rook : castling_rooks) {
        std::vector<BoardLocation> kings_path;
        if (location.x < rook->get_location().x) {
            kings_path = {
                {location.x + 1, location.y},
                {location.x + 2, location.y}
            };
        } else {
            kings_path = {
                {location.x - 1, location.y},
                {location.x - 2, location.y}
            };
        }

        bool is_castling_possible = true;
        for (BoardLocation location : kings_path) {
            if (get_piece_at_destination(location, active_pieces) != nullptr) {
                is_castling_possible = false;
                break;
            }

            //todo check if king would be in check at this location
        }

        if (is_castling_possible) {
            possible_moves.push_back(Move(MoveType::MOVE, kings_path[1], nullptr, false, rook, kings_path[0]));
        }
    }
}

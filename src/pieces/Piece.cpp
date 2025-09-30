#include "Piece.h"

Piece::Piece(PieceColor color, BoardLocation location)
:
color(color),
location(location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Piece::~Piece() = default;

// --------------------------------------------------------------------------

PieceColor Piece::get_color() const {
    return color;
}

// --------------------------------------------------------------------------

BoardLocation Piece::get_location() const {
    return location;
}

// --------------------------------------------------------------------------

void Piece::add_directional_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, int dx, int dy, std::vector<Move>& possible_moves) {
    int x = location.x + dx;
    int y = location.y + dy;
    
    // Keep moving in the direction until we hit the board edge or a piece is in the way
    while (x >= 0 && x < board_width && y >= 0 && y < board_height) {
        Piece* piece_at_destination = get_piece_at_destination({x, y}, active_pieces);
        MoveType move_type = determine_move_type(this, piece_at_destination);

        if (move_type == MoveType::INVALID) {
            break;
        }

        possible_moves.push_back({move_type, {x, y}});

        if (move_type == MoveType::CAPTURE) {
            break;
        }

        x += dx;
        y += dy;
    }
}

// --------------------------------------------------------------------------

void Piece::process_possible_destinations(int board_width, int board_height, const std::vector<Piece*>& active_pieces, const std::vector<BoardLocation>& destinations, std::vector<Move>& possible_moves) {
    for (const BoardLocation& destination : destinations) {
        if (destination.x >= 0 && destination.x < board_width && destination.y >= 0 && destination.y < board_height) {
            Piece* piece_at_destination = get_piece_at_destination(destination, active_pieces);
            MoveType move_type = determine_move_type(this, piece_at_destination);

            if (move_type != MoveType::INVALID) {
                possible_moves.push_back({move_type, destination});
            }
        }
    }
}

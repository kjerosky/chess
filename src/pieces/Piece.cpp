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

        Move move = {
            move_type,
            {x, y},
            move_type == MoveType::CAPTURE ? piece_at_destination : nullptr
        };
        possible_moves.push_back(move);

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
        Move move = create_move_for_destination(destination, board_width, board_height, active_pieces);
        if (move.type != MoveType::INVALID) {
            possible_moves.push_back(move);
        }
    }
}

// --------------------------------------------------------------------------

void Piece::move_to(const BoardLocation& destination) {
    location = destination;
}

// --------------------------------------------------------------------------

Move Piece::create_move_for_destination(const BoardLocation& destination, int board_width, int board_height, const std::vector<Piece*>& active_pieces) {
    Move move = {MoveType::INVALID, destination, nullptr};

    if (destination.x >= 0 && destination.x < board_width && destination.y >= 0 && destination.y < board_height) {
        Piece* piece_at_destination = get_piece_at_destination(destination, active_pieces);
        MoveType move_type = determine_move_type(this, piece_at_destination);
        move.type = move_type;

        if (move_type == MoveType::CAPTURE) {
            move.piece_to_capture = piece_at_destination;
        }
    }

    return move;
}

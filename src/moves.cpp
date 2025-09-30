#include "moves.h"
#include "pieces/Piece.h"

Piece* get_piece_at_destination(const BoardLocation& destination, const std::vector<Piece*>& active_pieces) {
    Piece* piece_at_destination = nullptr;
    for (Piece* piece : active_pieces) {
        if (piece->get_location() == destination) {
            piece_at_destination = piece;
            break;
        }
    }

    return piece_at_destination;
}

// --------------------------------------------------------------------------

MoveType determine_move_type(const Piece* piece_to_move, Piece* piece_at_destination) {
    MoveType move_type = MoveType::INVALID;

    if (piece_at_destination == nullptr) {
        move_type = MoveType::MOVE;
    } else if (piece_to_move->get_color() != piece_at_destination->get_color()) {
        if (piece_at_destination->is_capturable()) {
            move_type = MoveType::CAPTURE;
        }
    }

    return move_type;
}

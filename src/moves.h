#ifndef MOVES_H
#define MOVES_H

#include <vector>

#include "BoardLocation.h"

class Piece;

enum class MoveType {
    INVALID,
    MOVE,
    CAPTURE
};

class Move {

public:

    MoveType type;
    BoardLocation destination;
    Piece* piece_to_capture;
    bool is_en_passant_capturable;
    Piece* castling_rook;
    BoardLocation castling_rook_destination;

    Move(MoveType type, BoardLocation destination, Piece* piece_to_capture, bool is_en_passant_capturable, Piece* castling_rook, BoardLocation castling_rook_destination)
    :
    type(type),
    destination(destination),
    piece_to_capture(piece_to_capture),
    is_en_passant_capturable(is_en_passant_capturable),
    castling_rook(castling_rook),
    castling_rook_destination(castling_rook_destination) {
        // This is just a container class, so no need to do anything more than initialize the member variables.
    }

    ~Move() = default;
};

Piece* get_piece_at_destination(const BoardLocation& destination, const std::vector<Piece*>& active_pieces);

MoveType determine_move_type(const Piece* piece_to_move, Piece* piece_at_destination);

#endif

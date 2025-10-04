#ifndef MOVES_H
#define MOVES_H

#include <vector>

#include "BoardLocation.h"

class Piece;

enum class MoveType {
    INVALID,
    MOVE,
    CAPTURE,
    PROMOTION,
    CASTLING
};

struct Move {
    MoveType type;
    BoardLocation destination;
    Piece* piece_to_capture;
    bool is_en_passant_capturable;
};

Piece* get_piece_at_destination(const BoardLocation& destination, const std::vector<Piece*>& active_pieces);

MoveType determine_move_type(const Piece* piece_to_move, Piece* piece_at_destination);

#endif

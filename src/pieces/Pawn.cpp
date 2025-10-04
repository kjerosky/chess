#include "Pawn.h"

Pawn::Pawn(PieceColor c, BoardLocation location)
:
Piece(PieceType::PAWN, c, location) {
    // do nothing for now
}

// --------------------------------------------------------------------------

Pawn::~Pawn() = default;

// --------------------------------------------------------------------------

void Pawn::get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, Piece* en_passant_capturable_piece, std::vector<Move>& possible_moves) {
    // Pawn moves forward one square, or two squares on first move
    // For now, we'll implement basic forward movement without considering captures or other pieces
    
    // Clear any existing moves
    possible_moves.clear();
    
    // Determine direction based on color
    int move_direction = (color == PieceColor::WHITE) ? 1 : -1;
    
    // Check if this is the pawn's starting position (for two-square move)
    bool is_starting_position = (color == PieceColor::WHITE && location.y == 1) || (color == PieceColor::BLACK && location.y == 6);
    
    // Check moving one square forward
    int one_square_ahead_y = location.y + move_direction;
    if (one_square_ahead_y >= 0 && one_square_ahead_y < board_height) {
        Move one_square_ahead_move = create_move_for_destination({location.x, one_square_ahead_y}, board_width, board_height, active_pieces);
        if (one_square_ahead_move.type == MoveType::MOVE) {
            possible_moves.push_back(one_square_ahead_move);

            // Check moving two squares forward on first move
            if (is_starting_position) {
                int two_squares_ahead_y = location.y + (2 * move_direction);
                if (two_squares_ahead_y >= 0 && two_squares_ahead_y < board_height) {
                    Move two_squares_ahead_move = create_move_for_destination({location.x, two_squares_ahead_y}, board_width, board_height, active_pieces);
                    if (two_squares_ahead_move.type == MoveType::MOVE) {
                        two_squares_ahead_move.is_en_passant_capturable = true;
                        possible_moves.push_back(two_squares_ahead_move);
                    }
                }
            }
        }
    }

    // Check for captures
    if (location.x > 0) {
        Move capture_move_left = create_move_for_destination({location.x - 1, one_square_ahead_y}, board_width, board_height, active_pieces);
        if (capture_move_left.type == MoveType::CAPTURE) {
            possible_moves.push_back(capture_move_left);
        }
    }

    if (location.x < board_width - 1) {
        Move capture_move_right = create_move_for_destination({location.x + 1, one_square_ahead_y}, board_width, board_height, active_pieces);
        if (capture_move_right.type == MoveType::CAPTURE) {
            possible_moves.push_back(capture_move_right);
        }
    }

    if (en_passant_capturable_piece != nullptr) {
        std::vector<BoardLocation> locations_to_check = {
            {location.x - 1, location.y},
            {location.x + 1, location.y}
        };
        for (const BoardLocation& location_to_check : locations_to_check) {
            if (en_passant_capturable_piece->get_location() == location_to_check) {
                Move en_passant_move(
                    MoveType::CAPTURE,
                    { location_to_check.x, one_square_ahead_y },
                    en_passant_capturable_piece,
                    false,
                    nullptr,
                    {0, 0}
                );
                possible_moves.push_back(en_passant_move);
                break;
            }
        }
    }
}

// --------------------------------------------------------------------------

bool Pawn::is_capturable() const {
    return true;
}

// --------------------------------------------------------------------------

int Pawn::get_piece_texture_index() const {
    return 5;
}

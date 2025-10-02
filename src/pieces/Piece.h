#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "../BoardLocation.h"
#include "../moves.h"

enum class PieceColor {
    WHITE,
    BLACK
};

// --------------------------------------------------------------------------

class Piece {

public:

    Piece(PieceColor color, BoardLocation location);
    virtual ~Piece() = 0;

    virtual void get_possible_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, std::vector<Move>& possible_moves) = 0;
    virtual bool is_capturable() const = 0;
    virtual int get_piece_texture_index() const = 0;

    BoardLocation get_location() const;
    PieceColor get_color() const;
    void move_to(const BoardLocation& destination);

protected:

    BoardLocation location;
    PieceColor color;
    
    void add_directional_moves(int board_width, int board_height, const std::vector<Piece*>& active_pieces, int dx, int dy, std::vector<Move>& possible_moves);
    void process_possible_destinations(int board_width, int board_height, const std::vector<Piece*>& active_pieces, const std::vector<BoardLocation>& destinations, std::vector<Move>& possible_moves);
};

#endif

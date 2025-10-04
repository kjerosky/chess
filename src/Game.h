#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>

#include "pieces/Piece.h"
#include "input.h"

class Game {

public:

    Game(int board_horizontal_squares, int board_vertical_squares, SDL_Texture* pieces_texture);
    ~Game();

    void reset();
    void process_input(int window_width, int window_height, MouseClickEvent* mouse_click_event);
    void render(SDL_Renderer* renderer);

private:

    enum class GameState {
        WHITE_SELECTING_PIECE,
        BLACK_SELECTING_PIECE,
        WHITE_SELECTING_DESTINATION,
        BLACK_SELECTING_DESTINATION
    };

    int board_horizontal_squares;
    int board_vertical_squares;
    SDL_Texture* pieces_texture;

    SDL_Color light_square_color;
    SDL_Color dark_square_color;
    SDL_Color white_piece_color;
    SDL_Color black_piece_color;
    SDL_Color selected_color;
    SDL_Color move_color;
    SDL_Color capture_color;

    std::vector<Piece*> active_pieces;

    int board_x;
    int board_y;
    float board_square_width;
    float board_square_height;
    float board_side_length;

    GameState state;

    Piece* selected_piece;
    std::vector<Move> possible_moves_for_selected_piece;
    Piece* en_passant_capturable_piece;

    void recalculate_board_dimensions(int window_width, int window_height);
    void render_sprite_on_board(SDL_Renderer* renderer, const BoardLocation& location, int sprite_x, int sprite_y, const SDL_Color& color);
    void reset_piece_selection();
    void handle_piece_selection(Piece* clicked_piece, PieceColor piece_color, GameState next_state_on_successful_selection);
    void handle_piece_destination_selection(const BoardLocation& click_location, bool is_cancel_requested, GameState next_state_on_move, GameState next_state_on_cancel);
};

#endif

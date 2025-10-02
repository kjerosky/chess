#include "Game.h"

#include <algorithm>

#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Game::Game(int board_horizontal_squares, int board_vertical_squares, SDL_Texture* pieces_texture)
:
board_horizontal_squares(board_horizontal_squares),
board_vertical_squares(board_vertical_squares),
pieces_texture(pieces_texture),
light_square_color({ 255, 206, 158, 255 }),
dark_square_color({ 209, 139, 71, 255 }),
white_piece_color({ 255, 255, 255, 255 }),
black_piece_color({ 0, 0, 0, 255 }),
selected_color({ 0, 0, 255, 255 }),
move_color({ 0, 255, 0, 255 }),
capture_color({ 255, 0, 0, 255 }) {
    reset();
}

// --------------------------------------------------------------------------

Game::~Game() {
    // Clean up all pieces
    for (Piece* piece : active_pieces) {
        delete piece;
    }
}

// --------------------------------------------------------------------------

void Game::reset() {
    // Clean up existing pieces
    for (Piece* piece : active_pieces) {
        delete piece;
    }
    active_pieces.clear();

    for (int i = 0; i < 8; ++i) {
        active_pieces.push_back(new Pawn(PieceColor::WHITE, { i, 1 }));
        active_pieces.push_back(new Pawn(PieceColor::BLACK, { i, board_vertical_squares - 2 }));
    }

    active_pieces.push_back(new Rook(PieceColor::WHITE, { 0, 0 }));
    active_pieces.push_back(new Rook(PieceColor::WHITE, { 7, 0 }));
    active_pieces.push_back(new Rook(PieceColor::BLACK, { 0, board_vertical_squares - 1 }));
    active_pieces.push_back(new Rook(PieceColor::BLACK, { 7, board_vertical_squares - 1 }));

    active_pieces.push_back(new Knight(PieceColor::WHITE, { 1, 0 }));
    active_pieces.push_back(new Knight(PieceColor::WHITE, { 6, 0 }));
    active_pieces.push_back(new Knight(PieceColor::BLACK, { 1, board_vertical_squares - 1 }));
    active_pieces.push_back(new Knight(PieceColor::BLACK, { 6, board_vertical_squares - 1 }));

    active_pieces.push_back(new Bishop(PieceColor::WHITE, { 2, 0 }));
    active_pieces.push_back(new Bishop(PieceColor::WHITE, { 5, 0 }));
    active_pieces.push_back(new Bishop(PieceColor::BLACK, { 2, board_vertical_squares - 1 }));
    active_pieces.push_back(new Bishop(PieceColor::BLACK, { 5, board_vertical_squares - 1 }));

    active_pieces.push_back(new Queen(PieceColor::WHITE, { 3, 0 }));
    active_pieces.push_back(new Queen(PieceColor::BLACK, { 3, board_vertical_squares - 1 }));

    active_pieces.push_back(new King(PieceColor::WHITE, { 4, 0 }));
    active_pieces.push_back(new King(PieceColor::BLACK, { 4, board_vertical_squares - 1 }));

    state = GameState::WHITE_SELECTING_PIECE;

    selected_piece = nullptr;
    possible_moves_for_selected_piece.clear();
}

// --------------------------------------------------------------------------

void Game::process_input(int window_width, int window_height, MouseClickEvent* mouse_click_event) {
    recalculate_board_dimensions(window_width, window_height);

    if (mouse_click_event == nullptr) {
        return;
    }

    int board_relative_x = mouse_click_event->mouse_x - board_x;
    int board_relative_y = mouse_click_event->mouse_y - board_y;
    if (mouse_click_event->button == SDL_BUTTON_LEFT && (board_relative_x < 0 || board_relative_x >= board_side_length || board_relative_y < 0 || board_relative_y >= board_side_length)) {
        return;
    }

    BoardLocation click_location = {
        static_cast<int>(board_relative_x / board_square_width),
        board_vertical_squares - 1 - static_cast<int>(board_relative_y / board_square_height)
    };

    Piece* clicked_piece = nullptr;
    if (mouse_click_event->button == SDL_BUTTON_LEFT) {
        clicked_piece = get_piece_at_destination(click_location, active_pieces);
    }

    switch (state) {
        case GameState::WHITE_SELECTING_PIECE:
            handle_piece_selection(clicked_piece, PieceColor::WHITE, GameState::WHITE_SELECTING_DESTINATION);
            break;

        case GameState::BLACK_SELECTING_PIECE:
            handle_piece_selection(clicked_piece, PieceColor::BLACK, GameState::BLACK_SELECTING_DESTINATION);
            break;

        case GameState::WHITE_SELECTING_DESTINATION:
            handle_piece_destination_selection(click_location, mouse_click_event->button == SDL_BUTTON_RIGHT, GameState::BLACK_SELECTING_PIECE, GameState::WHITE_SELECTING_PIECE);
            break;

        case GameState::BLACK_SELECTING_DESTINATION:
            handle_piece_destination_selection(click_location, mouse_click_event->button == SDL_BUTTON_RIGHT, GameState::WHITE_SELECTING_PIECE, GameState::BLACK_SELECTING_PIECE);
            break;
    }
}

// --------------------------------------------------------------------------

void Game::render(SDL_Renderer* renderer) {
    SDL_Color original_texture_color_mod;
    SDL_GetTextureColorMod(pieces_texture, &original_texture_color_mod.r, &original_texture_color_mod.g, &original_texture_color_mod.b);

    // Render the board
    for (int i = 0; i < board_horizontal_squares; ++i) {
        for (int j = 0; j < board_vertical_squares; ++j) {
            SDL_Color& square_color = (i + j) % 2 == 0 ? light_square_color : dark_square_color;
            SDL_FRect square_rect = {
                board_x + i * board_square_width,
                board_y + j * board_square_height,
                board_square_width,
                board_square_height
            };

            SDL_SetRenderDrawColor(renderer, square_color.r, square_color.g, square_color.b, square_color.a);
            SDL_RenderFillRect(renderer, &square_rect);
        }
    }

    // Render the pieces
    float texture_piece_width = static_cast<float>(pieces_texture->w) / 6;
    float texture_piece_height = static_cast<float>(pieces_texture->h);
    for (Piece* piece : active_pieces) {
        SDL_Color& piece_color = piece->get_color() == PieceColor::WHITE ? white_piece_color : black_piece_color;
        render_sprite_on_board(renderer, piece->get_location(), piece->get_piece_texture_index(), 0, piece_color);
    }

    switch (state) {
        case GameState::WHITE_SELECTING_DESTINATION:
        case GameState::BLACK_SELECTING_DESTINATION:
            render_sprite_on_board(renderer, selected_piece->get_location(), 0, 1, selected_color);
            for (Move move : possible_moves_for_selected_piece) {
                if (move.type == MoveType::CAPTURE) {
                    render_sprite_on_board(renderer, move.destination, 0, 1, capture_color);
                } else {
                    render_sprite_on_board(renderer, move.destination, 0, 1, move_color);
                }
            }
            break;

        default:
            // do nothing for now
            break;
    }

    SDL_SetTextureColorMod(pieces_texture, original_texture_color_mod.r, original_texture_color_mod.g, original_texture_color_mod.b);
}

// --------------------------------------------------------------------------

void Game::recalculate_board_dimensions(int window_width, int window_height) {
    board_side_length = std::min(window_width, window_height);

    board_square_width = board_side_length / board_horizontal_squares;
    board_square_height = board_side_length / board_vertical_squares;

    board_x = (window_width - board_side_length) / 2;
    board_y = (window_height - board_side_length) / 2;
}

// --------------------------------------------------------------------------

void Game::reset_piece_selection() {
    selected_piece = nullptr;
    possible_moves_for_selected_piece.clear();
}

// --------------------------------------------------------------------------

void Game::handle_piece_selection(Piece* clicked_piece, PieceColor piece_color, GameState next_state_on_successful_selection) {
    if (clicked_piece != nullptr && clicked_piece->get_color() == piece_color) {
        selected_piece = clicked_piece;
        selected_piece->get_possible_moves(board_horizontal_squares, board_vertical_squares, active_pieces, possible_moves_for_selected_piece);
        if (possible_moves_for_selected_piece.empty()) {
            reset_piece_selection();
        } else {
            state = next_state_on_successful_selection;
        }
    }
}

// --------------------------------------------------------------------------

void Game::handle_piece_destination_selection(const BoardLocation& click_location, bool is_cancel_requested, GameState next_state_on_move, GameState next_state_on_cancel) {
    if (is_cancel_requested) {
        reset_piece_selection();
        state = next_state_on_cancel;
    } else {
        // Move selected piece to destination and capture if applicable
        for (Move move : possible_moves_for_selected_piece) {
            if (move.destination == click_location) {
                if (move.type == MoveType::CAPTURE) {
                    Piece* piece_to_capture = get_piece_at_destination(move.destination, active_pieces);
                    active_pieces.erase(std::remove(active_pieces.begin(), active_pieces.end(), piece_to_capture), active_pieces.end());
                }

                selected_piece->move_to(move.destination);

                reset_piece_selection();
                state = next_state_on_move;
                break;
            }
        }
    }
}

// --------------------------------------------------------------------------

void Game::render_sprite_on_board(SDL_Renderer* renderer, const BoardLocation& location, int sprite_x, int sprite_y, const SDL_Color& color) {
    float texture_sprite_width = static_cast<float>(pieces_texture->w) / 6;
    float texture_sprite_height = static_cast<float>(pieces_texture->h) / 2;

    SDL_FRect sprite_texture_rect = {
        sprite_x * texture_sprite_width,
        sprite_y * texture_sprite_height,
        texture_sprite_width,
        texture_sprite_height
    };

    SDL_FRect sprite_rect = {
        board_x + location.x * board_square_width,
        board_y + (board_vertical_squares - 1 - location.y) * board_square_height,
        board_square_width,
        board_square_height
    };

    SDL_SetTextureColorMod(pieces_texture, color.r, color.g, color.b);
    SDL_RenderTexture(renderer, pieces_texture, &sprite_texture_rect, &sprite_rect);
}

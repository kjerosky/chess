#include "Game.h"

#include <algorithm>

#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Game::Game(int board_width, int board_height, SDL_Texture* pieces_texture)
:
board_width(board_width),
board_height(board_height),
pieces_texture(pieces_texture),
light_square_color({ 255, 206, 158, 255 }),
dark_square_color({ 209, 139, 71, 255 }),
white_piece_color({ 255, 255, 255, 255 }),
black_piece_color({ 0, 0, 0, 255 }) {
    reset();
}

// --------------------------------------------------------------------------

Game::~Game() {
    // Clean up all pieces
    for (Piece* piece : pieces) {
        delete piece;
    }
}

// --------------------------------------------------------------------------

void Game::reset() {
    // Clean up existing pieces
    for (Piece* piece : pieces) {
        delete piece;
    }
    pieces.clear();

    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new Pawn(PieceColor::WHITE, { i, 1 }));
        pieces.push_back(new Pawn(PieceColor::BLACK, { i, board_height - 2 }));
    }

    pieces.push_back(new Rook(PieceColor::WHITE, { 0, 0 }));
    pieces.push_back(new Rook(PieceColor::WHITE, { 7, 0 }));
    pieces.push_back(new Rook(PieceColor::BLACK, { 0, board_height - 1 }));
    pieces.push_back(new Rook(PieceColor::BLACK, { 7, board_height - 1 }));

    pieces.push_back(new Knight(PieceColor::WHITE, { 1, 0 }));
    pieces.push_back(new Knight(PieceColor::WHITE, { 6, 0 }));
    pieces.push_back(new Knight(PieceColor::BLACK, { 1, board_height - 1 }));
    pieces.push_back(new Knight(PieceColor::BLACK, { 6, board_height - 1 }));

    pieces.push_back(new Bishop(PieceColor::WHITE, { 2, 0 }));
    pieces.push_back(new Bishop(PieceColor::WHITE, { 5, 0 }));
    pieces.push_back(new Bishop(PieceColor::BLACK, { 2, board_height - 1 }));
    pieces.push_back(new Bishop(PieceColor::BLACK, { 5, board_height - 1 }));

    pieces.push_back(new Queen(PieceColor::WHITE, { 3, 0 }));
    pieces.push_back(new Queen(PieceColor::BLACK, { 3, board_height - 1 }));

    pieces.push_back(new King(PieceColor::WHITE, { 4, 0 }));
    pieces.push_back(new King(PieceColor::BLACK, { 4, board_height - 1 }));
}

// --------------------------------------------------------------------------

void Game::process_input(int window_width, int window_height, MouseClickEvent* mouse_click_event) {
    this->window_width = window_width;
    this->window_height = window_height;

    if (mouse_click_event == nullptr) {
        return;
    }

    //todo
}

// --------------------------------------------------------------------------

void Game::render(SDL_Renderer* renderer) {
    // Render the board's squares so the board fills the window and the board's width and height are equal
    float board_side_length = std::min(window_width, window_height);
    float square_width = board_side_length / board_width;
    float square_height = board_side_length / board_height;

    int board_x = (window_width - board_side_length) / 2;
    int board_y = (window_height - board_side_length) / 2;

    for (int i = 0; i < board_width; ++i) {
        for (int j = 0; j < board_height; ++j) {
            SDL_Color& square_color = (i + j) % 2 == 0 ? light_square_color : dark_square_color;
            SDL_FRect square_rect = {
                board_x + i * square_width,
                board_y + j * square_height,
                square_width,
                square_height
            };

            SDL_SetRenderDrawColor(renderer, square_color.r, square_color.g, square_color.b, square_color.a);
            SDL_RenderFillRect(renderer, &square_rect);
        }
    }

    // Render the pieces
    SDL_Color original_color_mod;
    SDL_GetTextureColorMod(pieces_texture, &original_color_mod.r, &original_color_mod.g, &original_color_mod.b);

    float texture_piece_width = static_cast<float>(pieces_texture->w) / 6;
    float texture_piece_height = static_cast<float>(pieces_texture->h);
    for (Piece* piece : pieces) {
        SDL_FRect piece_texture_rect = {
            piece->get_piece_texture_index() * texture_piece_width,
            0,
            texture_piece_width,
            texture_piece_height
        };

        SDL_FRect piece_rect = {
            board_x + piece->get_location().x * square_width,
            board_y + (board_height - 1 - piece->get_location().y) * square_height,
            square_width,
            square_height
        };

        SDL_Color& piece_color = piece->get_color() == PieceColor::WHITE ? white_piece_color : black_piece_color;
        SDL_SetTextureColorMod(pieces_texture, piece_color.r, piece_color.g, piece_color.b);
        SDL_RenderTexture(renderer, pieces_texture, &piece_texture_rect, &piece_rect);
    }

    SDL_SetTextureColorMod(pieces_texture, original_color_mod.r, original_color_mod.g, original_color_mod.b);
}

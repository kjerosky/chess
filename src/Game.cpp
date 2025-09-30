#include "Game.h"

#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Game::Game(int board_width, int board_height)
:
board_width(board_width),
board_height(board_height) {
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

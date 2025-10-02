#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>

#include "pieces/Piece.h"
#include "input.h"

class Game {

public:

    Game(int board_width, int board_height, SDL_Texture* pieces_texture);
    ~Game();

    void reset();
    void process_input(int window_width, int window_height, MouseClickEvent* mouse_click_event);
    void render(SDL_Renderer* renderer);

private:

    int board_width;
    int board_height;
    SDL_Texture* pieces_texture;

    std::vector<Piece*> pieces;

    int window_width;
    int window_height;
};

#endif

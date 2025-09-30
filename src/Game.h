#ifndef GAME_H
#define GAME_H

#include <vector>

#include "pieces/Piece.h"

class Game {

public:

    Game(int board_width, int board_height);
    ~Game();

    void reset();

private:

    int board_width;
    int board_height;

    std::vector<Piece*> pieces;
};

#endif

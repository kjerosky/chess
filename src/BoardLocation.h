#ifndef BOARD_LOCATION_H
#define BOARD_LOCATION_H

struct BoardLocation {
    int x;
    int y;

    // Implement equality operator
    bool operator==(const BoardLocation& other) const {
        return x == other.x && y == other.y;
    }
};

#endif

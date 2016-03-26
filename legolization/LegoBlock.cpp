//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlock.h"

using namespace std;

bool LegoBlock::has_valid_size(int x, int y) {
    int smaller = min(x, y);
    int larger = max(x, y);

    return (smaller == 1 && (larger == 1 || larger == 2 || larger == 3 || larger == 4 || larger == 6 || larger == 8))
           || (smaller == 2 && (larger == 2 || larger == 3 || larger == 4 || larger == 6 || larger == 8));
}

LegoBlock::LegoBlock() { }

void LegoBlock::set_ignore_color() {
    ignore_color = true;
}

void LegoBlock::set_color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
    ignore_color = false;
}

void LegoBlock::set_size(int x, int y) {
    this->sx = x;
    this->sy = y;
}

void LegoBlock::set_location(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

LegoBlock::LegoBlock(int, x, int y, int z, int sx, int sy) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_ignore_color();
}

LegoBlock::LegoBlock(int, x, int y, int z, int sx, int sy, int r, int g, int b) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_color(r, g, b);
}
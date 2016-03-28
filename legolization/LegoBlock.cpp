//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlock.h"

using namespace std;

bool LegoBlock::has_valid_size(short x, short y) {
    short smaller = min(x, y);
    short larger = max(x, y);

    return (smaller == 1 && (larger == 1 || larger == 2 || larger == 3 || larger == 4 || larger == 6 || larger == 8))
           || (smaller == 2 && (larger == 2 || larger == 3 || larger == 4 || larger == 6 || larger == 8));
}

LegoBlock::LegoBlock() {
    ignore_color = false;
}

void LegoBlock::set_ignore_color() {
    ignore_color = true;
}

void LegoBlock::set_color(short r, short g, short b) {
    this->r = r;
    this->g = g;
    this->b = b;
    ignore_color = false;
}

void LegoBlock::set_size(short x, short y) {
    this->sx = x;
    this->sy = y;
}

void LegoBlock::set_location(short x, short y, short z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

LegoBlock::LegoBlock(short x, short y, short z, short sx, short sy) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_ignore_color();
}

LegoBlock::LegoBlock(short x, short y, short z, short sx, short sy, short r, short g, short b) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_color(r, g, b);
    ignore_color = false;
}
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
    this->sz = 1;
}

void LegoBlock::set_location(short x, short y, short z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

LegoBlock::LegoBlock(short x, short y, short z, short sx, short sy) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_color(25, 25, 25);
    set_ignore_color();
}

LegoBlock::LegoBlock(short x, short y, short z, short sx, short sy, short r, short g, short b) {
    set_location(x, y, z);
    set_size(sx, sy);
    set_color(r, g, b);
    ignore_color = false;
}

void LegoBlock::getTriangles(float *points) {
    // back

    float sx = this->sx - 0.05;
    float sy = this->sy - 0.05;
    float sz = this->sz - 0.05;

    short position = 0;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y;
    points[position + 5] = z;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z;

    position = 9;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y + sy;
    points[position + 5] = z;
    points[position + 6] = x;
    points[position + 7] = y + sy;
    points[position + 8] = z;

    // left
    position = 18;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x;
    points[position + 4] = y + sy;
    points[position + 5] = z;
    points[position + 6] = x;
    points[position + 7] = y + sy;
    points[position + 8] = z + sz;

    position = 27;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x;
    points[position + 4] = y + sy;
    points[position + 5] = z + sz;
    points[position + 6] = x;
    points[position + 7] = y;
    points[position + 8] = z + sz;

    // right
    position = 36;
    points[position + 0] = x + sx;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z + sz;

    position = 45;
    points[position + 0] = x + sx;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y + sy;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z;

    // bottom
    position = 54;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x;
    points[position + 4] = y;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y;
    points[position + 8] = z + sz;

    position = 63;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y;
    points[position + 8] = z;

    // Top
    position = 72;
    points[position + 0] = x;
    points[position + 1] = y + sy;
    points[position + 2] = z;
    points[position + 3] = x;
    points[position + 4] = y + sy;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z + sz;

    position = 81;
    points[position + 0] = x;
    points[position + 1] = y + sy;
    points[position + 2] = z;
    points[position + 3] = x + sx;
    points[position + 4] = y + sy;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z;

    // Front
    position = 90;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z + sz;
    points[position + 3] = x + sx;
    points[position + 4] = y;
    points[position + 5] = z + sz;
    points[position + 6] = x + sx;
    points[position + 7] = y + sy;
    points[position + 8] = z + sz;

    position = 99;
    points[position + 0] = x;
    points[position + 1] = y;
    points[position + 2] = z + sz;
    points[position + 3] = x + sx;
    points[position + 4] = y + sy;
    points[position + 5] = z + sz;
    points[position + 6] = x;
    points[position + 7] = y + sy;
    points[position + 8] = z + sz;
}

list<LegoBlock *> LegoBlock::split() {
    list<LegoBlock*> children;
    for (int i = 0; i < sx; i++) {
        for (int j = 0; j < sy; j++) {
            LegoBlock* block = new LegoBlock(x + i, y +  j, z, 1, 1, r, g, b);
            children.push_back(block);
        }
    }
    return children;
}

void LegoBlock::print() {
    cout << x << " " << y << " " << z << endl;
    cout << sx << " " << sy << " " << sz << endl;
    cout << w << endl;
}

void LegoBlock::print_info() {
    cout << "LegoBlock:: "
    << x << "," << y << "," << z << " position, "
    << sx << "," << sy << "," << sz << " size " << endl;

}
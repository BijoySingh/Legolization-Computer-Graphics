//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCK_H
#define GRAPHICSPROJECT_LEGOBLOCK_H

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

class LegoBlock {
public:
    // Positions or least x, y, z corner
    short x, y, z;

    // Size in x and y
    short sx, sy, sz;

    // color
    short r, g, b;

    // color is ignorable
    bool ignore_color;

    // Constructors
    LegoBlock();
    LegoBlock(short x, short y, short z, short sx, short sy);
    LegoBlock(short x, short y, short z, short sx, short sy, short r, short g, short b);

    // sets the ignore color to true
    void set_ignore_color();

    // sets the color of the block
    void set_color(short r, short g, short b);

    // sets the size of the block
    void set_size(short x, short y);

    // sets the coordinate of the block
    void set_location(short x, short y, short z);

    // Checks if the size configuration is valid
    static bool has_valid_size(short x, short y);

    void getTriangles(float *points);
};

#endif //GRAPHICSPROJECT_LEGOBLOCK_H

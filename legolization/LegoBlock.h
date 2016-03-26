//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCK_H
#define GRAPHICSPROJECT_LEGOBLOCK_H

#include <algorithm>

class LegoBlock {
public:
    // Positions or least x, y, z corner
    int x, y, z;

    // Size in x and y
    int sx, sy;

    // color
    int r, g, b;

    // color is ignorable
    bool ignore_color = false;

    // Constructors
    LegoBlock();
    LegoBlock(int, x, int y, int z, int sx, int sy);
    LegoBlock(int, x, int y, int z, int sx, int sy, int r, int g, int b);

    // sets the ignore color to true
    void set_ignore_color();

    // sets the color of the block
    void set_color(int r, int g, int b);

    // sets the size of the block
    void set_size(int x, int y);

    // sets the coordinate of the block
    void set_location(int x, int y, int z);

    // Checks if the size configuration is valid
    static bool has_valid_size(int x, int y);


};

#endif //GRAPHICSPROJECT_LEGOBLOCK_H

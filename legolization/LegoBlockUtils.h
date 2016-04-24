//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKSET_H
#define GRAPHICSPROJECT_LEGOBLOCKSET_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "LegoBlock.h"
#define MERGE_PROBABILITY 1
#define SAMPLE_COUNT 1000

using namespace std;

class LegoBlockUtils {
public:

    // Merge Blocks
    static LegoBlock* merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego blocks are connected
    static bool are_connected(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if the are adjacent
    static bool are_adjacent(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if block 2 is stacked over block 1
    static bool is_stacked_on(LegoBlock *block_1, LegoBlock *block_2);

    // Returns the number of knobs of 1 go inside 2
    static int overlap(LegoBlock *block_1, LegoBlock *block_2);

    // Returns the relative positions of knobs of 1 going inside 2
    static list<pair<int, int> > overlaps(LegoBlock *b1, LegoBlock *b2);

    // Checks if 2 Lego Blocks can merge (checks if colors are compatible)
    static bool can_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego Blocks can merge wrt color
    static bool can_colors_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Returns which block's color should be considered. 0 if ignore
    static short get_merge_color(LegoBlock *block_1, LegoBlock *block_2);

};

#endif //GRAPHICSPROJECT_LEGOBLOCKSET_H

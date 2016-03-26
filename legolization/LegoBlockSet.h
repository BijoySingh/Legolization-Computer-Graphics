//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKSET_H
#define GRAPHICSPROJECT_LEGOBLOCKSET_H

#include <algorithm>

class LegoBlockSet {
public:

    // Merge Blocks
    LegoBlock merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego blocks are connected
    bool are_connected(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if block 2 is stacked over block 1
    bool is_stacked_on(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego Blocks can merge (checks if colors are compatible)
    bool can_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego Blocks can merge wrt color
    bool can_colors_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Returns which block's color should be considered. 0 if ignore
    int get_merge_color(LegoBlock *block_1, LegoBlock *block_2);

};

#endif //GRAPHICSPROJECT_LEGOBLOCKSET_H

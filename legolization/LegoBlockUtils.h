//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKSET_H
#define GRAPHICSPROJECT_LEGOBLOCKSET_H

#include <algorithm>

class LegoBlockUtils {
public:

    // Merge Blocks
    static LegoBlock merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego blocks are connected
    static bool are_connected(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if block 2 is stacked over block 1
    static bool is_stacked_on(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego Blocks can merge (checks if colors are compatible)
    static bool can_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Checks if 2 Lego Blocks can merge wrt color
    static bool can_colors_merge(LegoBlock *block_1, LegoBlock *block_2);

    // Returns which block's color should be considered. 0 if ignore
    static int get_merge_color(LegoBlock *block_1, LegoBlock *block_2);

};

#endif //GRAPHICSPROJECT_LEGOBLOCKSET_H

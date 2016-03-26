//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKGRAPH_H
#define GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

#include "LegoBlock.h"
#include "LegoBlockUtils.h"
#include <list>
#include <unordered_map>

class LegoBlockGraph {

public:
    // List of blocks
    list<LegoBlock *> blocks;

    // Map of blocks to connected
    unordered_map<LegoBlock *, list < LegoBlock * > >
    graph;

    unordered_map<int, list<LegoBlock *> > levels;

    // Constructors
    LegoBlockGraph();

    // Add block in the blocks
    void add_block(LegoBlock *block);

    // Removes the block from blocks
    void remove_block(LegoBlock *block);

    // Get list of connected blocks to a block
    list<LegoBlock *> get_connected_blocks(LegoBlock *block);
};

#endif //GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

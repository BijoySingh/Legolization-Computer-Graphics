//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKGRAPH_H
#define GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

#include "LegoBlock.h"
#include "LegoBlockUtils.h"
#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class LegoBlockGraph {

public:
    // List of blocks
    list<LegoBlock *> blocks;

    // Map of blocks to connected
    unordered_map<LegoBlock *, list < LegoBlock * > >
    graph;

    unordered_map<short, list<LegoBlock *> > levels;

    // Constructors
    LegoBlockGraph();

    // Add block in the blocks
    void add_block(LegoBlock *block);

    // Removes the block from blocks
    void remove_block(LegoBlock *block);

    // Get list of connected blocks to a block
    list<LegoBlock *> get_connected_blocks(LegoBlock *block);

    // Get blocks
    void add_blocks(short ***r, short ***g, short ***b, short sx, short sy, short sz);

    // Generates a list of mergable pairs
    list <pair<LegoBlock *, LegoBlock *> > generate_mergables();

    // Merges the blocks randomly till maximal
    void merge_to_maximal();

    // Render the blocks
    void render_blocks(ostream &out);

    // Render the blocks
    void prman_render_blocks(ostream &out, bool use_real_colors = true);

};

#endif //GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

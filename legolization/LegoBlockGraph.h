//
// Created by Bijoy Kochar on 3/26/16.
//

#ifndef GRAPHICSPROJECT_LEGOBLOCKGRAPH_H
#define GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

#include "LegoBlock.h"
#include "LegoBlockUtils.h"
#include "LegoStabilityUtil.h"
#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>

#define F_MAX 100
#define K_N 7

using namespace std;

class LegoBlockGraph {

public:
    // List of blocks
    list<LegoBlock *> blocks;

    unordered_map<LegoBlock*, short> visited;

    short ***r; short ***g; short ***b;
    short sx; short sy; short sz;

    // Map of blocks to connected
    unordered_map<LegoBlock *, list < LegoBlock * > > graph;
    unordered_map<LegoBlock *, list < LegoBlock * > > reverse_graph;
    unordered_map<LegoBlock *, list < LegoBlock * > > horizontal_neighbours;

    unordered_map<short, list<LegoBlock *> > levels;

    // Constructors
    LegoBlockGraph();

    // Add block in the blocks
    void add_block(LegoBlock *block);

    // Removes the block from blocks
    void remove_block(LegoBlock *block);

    // Get blocks
    void add_blocks(short ***r, short ***g, short ***b, short sx, short sy, short sz);

    // Generates a list of mergable pairs
    list <pair<LegoBlock *, LegoBlock *> > generate_mergables();

    // Merges the blocks randomly till maximal
    void merge_to_maximal();

    // Render the blocks
    void render_blocks(ostream &out);

    // Render the blocks
    void prman_render_blocks(ostream &out, short filter_z = -1,  bool use_real_colors = true);

    void generate_single_component_analysis();

    pair<int, LegoBlock*> component_analysis();

    list<LegoBlock *> get_neighbours(LegoBlock *block);
    set<LegoBlock *> get_neighbours(LegoBlock *block, int k);

    void replicate(LegoBlock* reference, LegoBlock* &duplicate, LegoBlockGraph &lego_graph);

    void copy(LegoBlockGraph &graph);
    void remove_everything();

    LegoBlockGraph shuffle(LegoBlock* w);

    pair<int, LegoBlock*> stability_analysis();
    void generate_stable_component();

    void print_info();

};

#endif //GRAPHICSPROJECT_LEGOBLOCKGRAPH_H

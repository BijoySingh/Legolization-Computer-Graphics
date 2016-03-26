//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockGraph.h"

void LegoBlockGraph::add_block(LegoBlock *block) {
    blocks.push_back(block);
    levels[block->z] = block;
    graph[block] = get_connected_blocks(block);
    for (auto neighbour: graph[block]) {
        graph[neighbour].push_back(block);
    }
}

void LegoBlockGraph::remove_block(LegoBlock *block) {
    blocks.remove(block);
    levels.remove(block->level);
    for (auto neighbour: graph[block]) {
        graph[neighbour].remove(block);
    }
    graph.remove(block);
}

bool has_level(LegoBlockGraph *graph, int level) {
    return (graph->levels).find(level) != (graph->levels).end();
}

list<LegoBlock *> filter_connected(list < LegoBlock * > blocks, LegoBlock * reference) {
    list < LegoBlock * > filtered;
    for (auto block : blocks) {
        if (LegoBlockUtils::are_connected(block, reference)) {
            filtered.push_back(block);
        }
    }
    return filtered;
}

list<LegoBlock *> LegoBlockGraph::get_connected_blocks(LegoBlock *block) {
    list < LegoBlock * > connected;
    if (has_level(this, block->level + 1)) {
        connected.splice(connected.end(), filter_connected(levels[block->level + 1], block));
    }

    if (has_level(this, block->level - 1)) {
        connected.splice(connected.end(), filter_connected(levels[block->level - 1], block));
    }

    return connected;
}
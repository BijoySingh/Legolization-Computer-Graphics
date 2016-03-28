//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockGraph.h"

LegoBlockGraph::LegoBlockGraph() { }

bool has_level(LegoBlockGraph *graph, short level) {
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

void LegoBlockGraph::add_block(LegoBlock *block) {
    blocks.push_back(block);

    // Add in levels
    if (!has_level(this, block->z)) {
        list < LegoBlock * > empty_list;
        levels[block->z] = empty_list;
    }
    levels[block->z].push_back(block);

    // Add in graph
    graph[block] = get_connected_blocks(block);
    for (auto neighbour: graph[block]) {
        graph[neighbour].push_back(block);
    }
}

void LegoBlockGraph::remove_block(LegoBlock *block) {
    blocks.remove(block);
    levels.erase(block->z);
    for (auto neighbour: graph[block]) {
        graph[neighbour].remove(block);
    }
    graph.erase(block);
}

list<LegoBlock *> LegoBlockGraph::get_connected_blocks(LegoBlock *block) {
    list < LegoBlock * > connected;
    if (has_level(this, block->z + 1)) {
        connected.splice(connected.end(), filter_connected(levels[block->z + 1], block));
    }

    if (has_level(this, block->z - 1)) {
        connected.splice(connected.end(), filter_connected(levels[block->z - 1], block));
    }

    return connected;
}

void LegoBlockGraph::add_blocks(short ***r, short ***g, short ***b, short sx, short sy, short sz) {
    for (int i = 0; i < sx; i++) {
        for (int j = 0; j < sy; j++) {
            for (int k = 0; k < sz; k++) {
                if (r[i][j][k] == -1) {
                    add_block(new LegoBlock(i, j, k, 1, 1));
                } else if (r[i][j][k] >= 0) {
                    add_block(new LegoBlock(i, j, k, 1, 1, r[i][j][k], g[i][j][k], b[i][j][k]));
                }

                cout << " Block Added " << i << ", " << j << ", " << k << endl;
            }
        }
    }
}
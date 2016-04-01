//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockGraph.h"

LegoBlockGraph::LegoBlockGraph() { }

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
    levels[block->z].push_back(block);

    // Add in graph
    graph[block] = get_connected_blocks(block);
    for (auto neighbour: graph[block]) {
        graph[neighbour].push_back(block);
    }

}

void LegoBlockGraph::remove_block(LegoBlock *block) {
    blocks.remove(block);
    levels[block->z].remove(block);
    for (auto neighbour: graph[block]) {
        graph[neighbour].remove(block);
    }
    graph.erase(block);
}

list<LegoBlock *> LegoBlockGraph::get_connected_blocks(LegoBlock *block) {
    list < LegoBlock * > connected;
    connected.splice(connected.end(), filter_connected(levels[block->z + 1], block));
    connected.splice(connected.end(), filter_connected(levels[block->z - 1], block));
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

                // cout << " Block Added " << i << ", " << j << ", " << k << endl;
            }
        }
    }
}

void LegoBlockGraph::render_blocks(ostream &out) {
    out << blocks.size() << endl;
    for (LegoBlock *block : blocks) {
        out << block->x << " " << block->y << " " << block->z << endl;
        out << block->sx << " " << block->sy << endl;
        out << block->r << " " << block->g << " " << block->b << endl;
    }
}

void getColor(short sx, short sy, short *colors) {
    short smaller = min(sx, sy);
    short larger = max(sx, sy);

    if (smaller == 1) {
        switch (larger) {
            case 1:
                colors[0] = 255;
                colors[1] = 0;
                colors[2] = 76;
                break;
            case 2:
                colors[0] = 255;
                colors[1] = 0;
                colors[2] = 255;
                break;
            case 3:
                colors[0] = 13;
                colors[1] = 0;
                colors[2] = 255;
                break;
            case 4:
                colors[0] = 0;
                colors[1] = 255;
                colors[2] = 255;
                break;
            case 6:
                colors[0] = 0;
                colors[1] = 255;
                colors[2] = 149;
                break;
            case 8:
                colors[0] = 0;
                colors[1] = 255;
                colors[2] = 0;
                break;
        }
    } else {
        switch (larger) {
            case 2:
                colors[0] = 163;
                colors[1] = 255;
                colors[2] = 0;
                break;
            case 3:
                colors[0] = 255;
                colors[1] = 255;
                colors[2] = 0;
                break;
            case 4:
                colors[0] = 255;
                colors[1] = 166;
                colors[2] = 0;
                break;
            case 6:
                colors[0] = 83;
                colors[1] = 112;
                colors[2] = 138;
                break;
            case 8:
                colors[0] = 138;
                colors[1] = 109;
                colors[2] = 83;
                break;
        }
    }
}

void LegoBlockGraph::prman_render_blocks(ostream &out, bool use_real_colors) {
    for (LegoBlock *block : blocks) {
        out << "AttributeBegin" << endl;

        short colors[3];
        if (use_real_colors) {
            getColor(block->sx, block->sy, colors);
        } else {
            colors[0] = block->r;
            colors[1] = block->g;
            colors[2] = block->b;
        }
        out << "    Color [" << colors[0] / 255.0 << " " << colors[1] / 255.0 << " " << colors[2] / 255.0 << "]" <<
        endl;
        /*out << "    Scale " << block->sx << " " << block->sy << " " << block->sz << endl;
        out << "    Translate -" << block->x << " -" << block->y << " -" << block->z << endl;
        out << "    ReadArchive \"unitcube.rib\"" << endl;*/
        float points[108];
        block->getTriangles(points);
        for (int i = 0; i < 108; i++) {
            if (i%9 == 0) {
                out << "    Polygon \"P\" [";
            }
            out << points[i] << " ";
            if (i%9 == 8) {
                out << "]" <<endl;
            }
        }
        out << "AttributeEnd" << endl << endl;
    }
}


list <pair<LegoBlock *, LegoBlock *> > LegoBlockGraph::generate_mergables() {
    list <pair<LegoBlock *, LegoBlock *> > mergables;
    for (LegoBlock *block : blocks) {
        for (LegoBlock *neighbour : levels[block->z]) {
            if (LegoBlockUtils::can_merge(block, neighbour)) {
                mergables.push_back(make_pair(block, neighbour));
            }
        }
    }

    return mergables;
}

pair < LegoBlock * , LegoBlock *> get_iterator(list <pair<LegoBlock *, LegoBlock *> > &mergables, int position) {
    int index = 0;
    list < pair < LegoBlock * , LegoBlock * > >::iterator value;
    for (value = mergables.begin(); value != mergables.end(); value++) {
        if (index == position)
            return *value;
        index++;
    }
    assert(false);
}

void remove_mergables(list <pair<LegoBlock *, LegoBlock *> > &mergables, LegoBlock *block) {
    list < pair < LegoBlock * , LegoBlock * > >::iterator value;

    for (value = mergables.begin(); value != mergables.end(); value++) {
        if (value->first == block || value->second == block) {
            value = mergables.erase(value);
            value--;
        }
    }
}

void LegoBlockGraph::merge_to_maximal() {
    list <pair<LegoBlock *, LegoBlock *> > mergables = generate_mergables();
    cout << " Merge to Maximal " << mergables.size() << endl;

    while (mergables.size() != 0) {
        int position = rand() % mergables.size();
        cout<<" Merging @ " << mergables.size() <<" "<< position <<endl;

        pair < LegoBlock * , LegoBlock * > iter = get_iterator(mergables, position);
        LegoBlock *block = LegoBlockUtils::merge(iter.first, iter.second);

        remove_mergables(mergables, iter.first);
        remove_mergables(mergables, iter.second);
        remove_block(iter.first);
        remove_block(iter.second);

        delete iter.first;
        delete iter.second;

        add_block(block);

        for (LegoBlock *neighbour : levels[block->z]) {
            if (LegoBlockUtils::can_merge(block, neighbour)) {
                mergables.push_back(make_pair(block, neighbour));
                mergables.push_back(make_pair(neighbour, block));
            }
        }
    }
}
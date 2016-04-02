//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockGraph.h"

LegoBlockGraph::LegoBlockGraph() { }

list<LegoBlock *> LegoBlockGraph::get_neighbours(LegoBlock *block) {
    list < LegoBlock * > neighbours;
    neighbours.splice(neighbours.end(), graph[block]);
    neighbours.splice(neighbours.end(), reverse_graph[block]);
    neighbours.splice(neighbours.end(), horizontal_neighbours[block]);
    return neighbours;
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

list<LegoBlock *> get_horizontal_neighbours(list < LegoBlock * > blocks, LegoBlock * reference) {
    list < LegoBlock * > neighbours;
    for (auto block: blocks) {
        if (LegoBlockUtils::are_adjacent(block, reference)) {
            neighbours.push_back(block);
        }
    }
    return neighbours;
}

void LegoBlockGraph::add_block(LegoBlock *block) {
    blocks.push_back(block);

    // Add in levels
    levels[block->z].push_back(block);

    // Add in graph
    graph[block] = filter_connected(levels[block->z + 1], block);
    for (auto neighbour : graph[block]) {
        reverse_graph[neighbour].push_back(block);
    }
    reverse_graph[block] = filter_connected(levels[block->z - 1], block);
    for (auto neighbour : reverse_graph[block]) {
        graph[neighbour].push_back(block);
    }
    horizontal_neighbours[block] = get_horizontal_neighbours(blocks, block);
    for (auto neighbour : horizontal_neighbours[block]) {
        horizontal_neighbours[neighbour].push_back(block);
    }

    // cout << " Block added with " << horizontal_neighbours.size() << " horizontal neighbour, " << graph[block].size()
    // << " children, " << reverse_graph[block].size() << " parents " <<endl;
}

void LegoBlockGraph::remove_block(LegoBlock *block) {
    blocks.remove(block);
    levels[block->z].remove(block);
    for (auto child: graph[block]) {
        reverse_graph[child].remove(block);
    }
    for (auto parent: reverse_graph[block]) {
        graph[parent].remove(block);
    }
    for (auto neighbour : horizontal_neighbours[block]) {
        horizontal_neighbours[neighbour].remove(block);
    }
    graph.erase(block);
    reverse_graph.erase(block);
    horizontal_neighbours.erase(block);
}

void LegoBlockGraph::add_blocks(short ***r, short ***g, short ***b, short sx, short sy, short sz) {
    this->r = r; this->g = g; this->b = b;
    this->sx = sx; this->sy = sy; this->sz = sz;

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

void LegoBlockGraph::prman_render_blocks(ostream &out, short filter_z, bool use_real_colors) {
    for (LegoBlock *block : blocks) {
        if (filter_z != -1 && block->z != filter_z) {
            continue;
        }

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
            if (i % 9 == 0) {
                out << "    Polygon \"P\" [";
            }
            out << points[i] << " ";
            if (i % 9 == 8) {
                out << "]" << endl;
            }
        }
        out << "AttributeEnd" << endl << endl;
    }
}


list <pair<LegoBlock *, LegoBlock *>> LegoBlockGraph::generate_mergables() {
    list <pair<LegoBlock *, LegoBlock *>> mergables;
    for (LegoBlock *block : blocks) {
        for (LegoBlock *neighbour : horizontal_neighbours[block]) {
            if (LegoBlockUtils::can_merge(block, neighbour)) {
                mergables.push_back(make_pair(block, neighbour));
            }
        }
    }

    return mergables;
}

pair<LegoBlock *, LegoBlock *> get_iterator(list <pair<LegoBlock *, LegoBlock *>> &mergables, int position) {
    int index = 0;
    list < pair < LegoBlock * , LegoBlock * > > ::iterator
    value;
    for (value = mergables.begin(); value != mergables.end(); value++) {
        if (index == position)
            return *value;
        index++;
    }
    assert(false);
}

void remove_mergables(list <pair<LegoBlock *, LegoBlock *>> &mergables, LegoBlock *block) {
    list < pair < LegoBlock * , LegoBlock * > > ::iterator
    value;

    for (value = mergables.begin(); value != mergables.end(); value++) {
        if (value->first == block || value->second == block) {
            value = mergables.erase(value);
            value--;
        }
    }
}

void LegoBlockGraph::merge_to_maximal() {
    int start_size = blocks.size();
    list <pair<LegoBlock *, LegoBlock *>> mergables = generate_mergables();

    while (mergables.size() != 0) {
        int position = rand() % mergables.size();

        pair < LegoBlock * , LegoBlock * > iter = get_iterator(mergables, position);
        LegoBlock *block = LegoBlockUtils::merge(iter.first, iter.second);

        remove_mergables(mergables, iter.first);
        remove_mergables(mergables, iter.second);
        remove_block(iter.first);
        remove_block(iter.second);

        delete iter.first;
        delete iter.second;

        add_block(block);

        for (LegoBlock *neighbour : horizontal_neighbours[block]) {
            if (LegoBlockUtils::can_merge(block, neighbour)) {
                mergables.push_back(make_pair(block, neighbour));
                mergables.push_back(make_pair(neighbour, block));
            }
        }
    }

    cout << " Merged to Maximal from " << start_size << " to " <<  blocks.size() << endl;
}

void LegoBlockGraph::replicate(LegoBlock* reference, LegoBlock* &duplicate, LegoBlockGraph &lego_graph) {
    for (LegoBlock* block : blocks) {
        LegoBlock *b = new LegoBlock(block->x, block->y, block->z, block->sx, block->sy, block->r, block->g, block->b);
        lego_graph.add_block(b);

        if (block == reference) {
            duplicate = b;
        }
    }
}

void LegoBlockGraph::copy(LegoBlockGraph &graph) {
    this->blocks = graph.blocks;
    this->visited = graph.visited;
    this->graph = graph.graph;
    this->reverse_graph = graph.reverse_graph;
    this->horizontal_neighbours = graph.horizontal_neighbours;
    this->levels = graph.levels;
}

void LegoBlockGraph::remove_everything() {
    graph.clear();
    reverse_graph.clear();
    levels.clear();
    visited.clear();
    horizontal_neighbours.clear();
    for (LegoBlock* block : blocks) {
        delete block;
    }
    blocks.clear();
}

void LegoBlockGraph::generate_single_component_analysis() {
    pair<int, LegoBlock*> ca = component_analysis();
    pair<int, LegoBlock*> t_ca;
    int s = ca.first;
    LegoBlock* w = ca.second;
    set<LegoBlock*> neighbours;
    list<LegoBlock*> replacements;

    short f = 0;
    while( s > 1 && f < F_MAX) {
        // cout << " Trying to Improve s from " << s << endl;

        LegoBlock* duplicate;
        LegoBlockGraph replicated;
        replicate(w, duplicate, replicated);
        // cout << " Replicated Successfully " << endl;

        neighbours.clear();
        neighbours = replicated.get_neighbours(duplicate, K_N);
        neighbours.insert(duplicate);
        // cout << " Got the " << K_N << "-ring neighbourhood " << endl;

        for (LegoBlock *neighbour: neighbours) {
            // cout << " Removing the neighbour " << neighbour->x << " " << neighbour->y << " "<<neighbour->z << endl;
            replicated.remove_block(neighbour);
            // cout << " Removed the neighbour" << endl;
            replacements.splice(replacements.end(), neighbour->split());
            // cout << " Splicing completed"<<endl;
            delete neighbour;
        }

        // cout << " Neighbours removed and Replacements created from the replicated graph " << endl;

        for (LegoBlock *replacement: replacements) {
            replicated.add_block(replacement);
        }

        // cout << " Replacements added to replicated graph " << endl;

        t_ca = replicated.component_analysis();
        // cout << " TCA Pre Calculated " << t_ca.first << endl;
        replicated.merge_to_maximal();

        t_ca = replicated.component_analysis();
        // cout << " TCA Post Calculated " << t_ca.first << endl;

        if (t_ca.first < s) {
            cout << "Improved the S from " << s << " to " << t_ca.first << endl;

            s = t_ca.first;
            w = t_ca.second;
            f = 0;

            remove_everything();
            copy(replicated);
        } else {
            cout << " Failure " << f << ", could not get better than "<< s
            << ". Was able to make it "<< t_ca.first << endl;
            replicated.remove_everything();
            f++;
        }

    }
}

set<LegoBlock*> LegoBlockGraph::get_neighbours(LegoBlock* block, int k) {
    visited.clear();
    for (LegoBlock *block : blocks) {
        visited[block] = -1;
    }

    set<LegoBlock*> neighbours;
    list<LegoBlock*> stack;
    stack.push_back(block);
    visited[block] = 0;
    while (stack.size() > 0) {
        LegoBlock* top = stack.front();
        stack.pop_front();
        if (visited[top] != -2 && visited[top] < k) {
            list<LegoBlock*> t_neighbours = get_neighbours(top);
            for (auto child : t_neighbours) {
                neighbours.insert(child);
                stack.push_back(child);
                visited[child] = visited[top] + 1;
            }
            visited[top] = -2;
        }
    }

    // cout << " K - Neighbourhood of size " << neighbours.size() << endl;

    return neighbours;
}

pair<int, LegoBlock*> LegoBlockGraph::component_analysis() {
    visited.clear();
    for (LegoBlock *block : blocks) {
        visited[block] = -1;
    }

    // cout << "All Blocks marked unvisited " << blocks.size() << endl;

    int A = 0;
    for (LegoBlock *bi : blocks) {
        if (visited[bi] != -1) {
            continue;
        }

        list < LegoBlock * > B;
        B.push_back(bi);
        while (B.size() > 0) {
            LegoBlock *bj = B.front();
            B.pop_front();
            visited[bj] = A;

            for (LegoBlock *bk : graph[bj]) {
                if (visited[bk] == -1) {
                    B.push_back(bk);
                }
            }

            for (LegoBlock *bk : reverse_graph[bj]) {
                if (visited[bk] == -1) {
                    B.push_back(bk);
                }
            }
        }

        A++;
    }
    // cout << "All Blocks Visited with A " << A << endl;

    int sum = 0;
    set<int> components;
    list<LegoBlock*> neighbours;
    for (LegoBlock* block : blocks) {
        neighbours = get_neighbours(block);

        components.clear();
        components.insert(visited[block]);
        for (LegoBlock* neighbour : neighbours) {
            components.insert(visited[neighbour]);
        }
        block->w = components.size() - 1;
        sum += components.size() - 1;
        // cout << " Disparity Count " << block->x << " "
        // << block->y << " " << block->z << " " << components.size() << " " << neighbours.size() << endl;
    }

    // cout << "All Neighbours counted " << sum << endl;

    if (sum == 0) {
        return make_pair(A, *blocks.begin());
    }

    int position = rand() % sum;
    int count = 0;
    for (LegoBlock* block : blocks) {
        count += block->w;
        if (count > position) {
            return make_pair(A, block);
        }
    }

    assert(false);
}
//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockGraph.h"

LegoBlockGraph::LegoBlockGraph() { }

list<LegoBlock *> LegoBlockGraph::get_neighbours(LegoBlock *block) {
    list < LegoBlock * > neighbours;
    neighbours.insert(neighbours.end(), graph[block].begin(), graph[block].end());
    neighbours.insert(neighbours.end(), reverse_graph[block].begin(), reverse_graph[block].end());
    neighbours.insert(neighbours.end(), horizontal_neighbours[block].begin(), horizontal_neighbours[block].end());
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

    // cout << " Block added with " << horizontal_neighbours[block].size() << " horizontal neighbour, " << graph[block].size()
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
        } else if (block->ignore_color) {
            colors[0] = 125;
            colors[1] = 125;
            colors[2] = 125;
        } else {
            colors[0] = block->r;
            colors[1] = block->g;
            colors[2] = block->b;
        }

        out << "    Color [" << colors[0] / 255.0 << " "
        << colors[1] / 255.0 << " " << colors[2] / 255.0 << "]" << endl;

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

    // cout<<" Found "<<mergables.size() << " mergeables" << endl;

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

    // cout << " Merged to Maximal from " << start_size << " to " <<  blocks.size() << endl;
}

void LegoBlockGraph::replicate(LegoBlock* reference, LegoBlock* &duplicate, LegoBlockGraph &lego_graph) {
    for (LegoBlock* block : blocks) {
        LegoBlock *b = new LegoBlock(block->x, block->y, block->z, block->sx, block->sy, block->r, block->g, block->b);
        b->ignore_color = block->ignore_color;
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

LegoBlockGraph LegoBlockGraph::shuffle(LegoBlock* w) {
    set<LegoBlock*> neighbours;
    list<LegoBlock*> replacements;
    LegoBlock* duplicate;
    LegoBlockGraph replicated;

    replicate(w, duplicate, replicated);
    neighbours = replicated.get_neighbours(duplicate, K_N);
    neighbours.insert(duplicate);

    for (LegoBlock *neighbour: neighbours) {
        replicated.remove_block(neighbour);
        replacements.splice(replacements.end(), neighbour->split());
        delete neighbour;
    }

    for (LegoBlock *replacement: replacements) {
        replicated.add_block(replacement);
    }

    replicated.merge_to_maximal();

    return replicated;
}

void LegoBlockGraph::generate_single_component_analysis() {
    pair<int, LegoBlock*> ca = component_analysis();
    pair<int, LegoBlock*> t_ca;
    int s = ca.first;
    LegoBlock* w = ca.second;

    short same_f = 0;
    short f = 0;
    while( s > 1 && f < F_MAX && same_f < F_MAX) {
        LegoBlockGraph replicated = shuffle(w);
        t_ca = replicated.component_analysis();

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

void LegoBlockGraph::generate_stable_component() {
    pair<int, LegoBlock*> sa = stability_analysis();
    pair<int, LegoBlock*> ca;
    pair<int, LegoBlock*> t_sa;
    int s = sa.first;
    LegoBlock* w = sa.second;

    short same_f = 0;
    short f = 0;
    while( s < 0 && f < F_MAX && same_f < F_MAX) {

        LegoBlockGraph replicated = shuffle(w);
        ca = replicated.component_analysis();
        t_sa = replicated.component_analysis();

        if (t_sa.first > s && ca.first == 1) {
            cout << "Improved the S from " << s << " to " << t_sa.first << endl;

            s = t_sa.first;
            w = t_sa.second;
            f = 0;

            remove_everything();
            copy(replicated);
        } else {
            cout << " Failure " << f << ", could not get better than "<< s
            << ". Was able to make it "<< t_sa.first << endl;
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

pair<int, LegoBlock*> LegoBlockGraph::stability_analysis() {
    LegoStabilityUtil util(this);
    return util.getStabilityAnalysis();
};

pair<int, LegoBlock*> LegoBlockGraph::component_analysis() {
    visited.clear();
    for (LegoBlock *block : blocks) {
        visited[block] = -1;
    }

    int A = 0;  // number of single connected component
    for (LegoBlock *bi : blocks) {
        if (visited[bi] != -1) {
            continue;
        }

        set < LegoBlock * > B;
        B.insert(bi);
        while (B.size() > 0) {
            LegoBlock *bj = *B.begin();
            B.erase(bj);
            visited[bj] = A;

            for (LegoBlock *bk : graph[bj]) {
                if (visited[bk] == -1) {
                    B.insert(bk);
                }
            }

            for (LegoBlock *bk : reverse_graph[bj]) {
                if (visited[bk] == -1) {
                    B.insert(bk);
                }
            }
        }

        A++;
    }

    int sum = 0;
    set<int> components;
    list<LegoBlock*> neighbours;
    list<LegoBlock*> concerned;
    for (LegoBlock* block : blocks) {
        neighbours = get_neighbours(block);

        components.clear();
        components.insert(visited[block]);
        for (LegoBlock* neighbour : neighbours) {
            components.insert(visited[neighbour]);
        }

        block->w = components.size() - 1;
        sum += components.size() - 1;

        if (components.size() - 1 > 0) {
            concerned.push_back(block);
        }
    }

    if (sum == 0) {
        return make_pair(A, *blocks.begin());
    }

    int position = rand() % sum;
    int count = 0;
    for (LegoBlock* block : concerned) {
        count += block->w;
        if (count > position) {
            return make_pair(A, block);
        }
    }

    assert(false);
}

void LegoBlockGraph::print_info() {
    cout << "LegoBlockGraph:: "
        << blocks.size() << " blocks, "
        << graph.size() << " graph nodes, "
        << reverse_graph.size() << " reverse-graph nodes, "
        << horizontal_neighbours.size() << " horizontal nodes."
        << endl;

    for (LegoBlock* block : blocks) {
        block->print_info();
        cout << graph[block].size() << " children, "
            << reverse_graph[block].size() << " parents, "
            << horizontal_neighbours[block].size() << " neighbours." << endl;
    }
}
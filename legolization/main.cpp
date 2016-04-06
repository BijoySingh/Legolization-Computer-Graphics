//
// Created by Bijoy Kochar on 4/2/16.
//

#include <cstdio>
#include "LegoBlock.h"
#include "LegoBlockUtils.h"
#include "LegoBlockGraph.h"

void render_stuff(LegoBlockGraph &graph, short sz, bool print_layers = false,
                  bool single_only = false, bool piece_colored = false) {
    ofstream fout;
    fout.open("pixels.txt");
    graph.render_blocks(fout);
    fout.close();

    fout.open("../renderman/pixels.rib");
    graph.prman_render_blocks(fout, -1, piece_colored);
    fout.close();

    string cmd;
    if (single_only) {
        cmd = "cd ../renderman; make single";
    } else {
        cmd = "cd ../renderman; make";
    }

    const char *cmd_car = cmd.c_str();
    cout << cmd << endl;
    system(cmd_car);

    if (print_layers) {
        for (int i = 0; i < sz; i++) {
            fout.open("../renderman/layer.rib");
            graph.prman_render_blocks(fout, i, piece_colored);
            cmd = "cd ../renderman; make layer NUM=" + to_string(i + 1) + " ";
            const char *cmd_car = cmd.c_str();
            cout << cmd << endl;
            system(cmd_car);
            fout.close();
        }
    }

}

short ***getImageMatrix(short sx, short sy, short sz) {
    srand(time(NULL));
    short ***image = new short **[(int) sx];
    for (int i = 0; i < sx; i++) {
        image[i] = new short *[(int) sy];
        for (int j = 0; j < sy; j++) {
            image[i][j] = new short[(int) sz];
            for (int k = 0; k < sz; k++) {
                image[i][j][k] = -2;
            }
        }
    }

    return image;
}

void print_progress(float progress) {
    int barWidth = 70;
    cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
}

bool validate(LegoBlockGraph &graph) {
    set<pair<int, pair<int, int> > > points;
    for (LegoBlock* block : graph.blocks) {
        pair<int, pair<int, int> > point = make_pair(block->x, make_pair(block->y, block->z));
        if (points.find(point) != points.end()) {
            return false;
        }
        points.insert(point);
    }

    return true;
}

int main() {
    int points, sx, sy, sz;
    short x, y, z;
    cin >> points >> sx >> sy >> sz;
    short ***r = getImageMatrix(sx, sy, sz);

    LegoBlockGraph graph;
    set<pair<int, pair<int, int> > > point_locs;
    pair<int, pair<int, int> > point;

    for (short i = 0; i < points; i++) {
        cin >> x >> y >> z;
        r[x][y][z] = 255;

        point = make_pair(x, make_pair(y, z));
        if (point_locs.find(point) == point_locs.end()) {
            graph.add_block(new LegoBlock(x, y, z, 1, 1, r[x][y][z], r[x][y][z], r[x][y][z]));
            point_locs.insert(point);
        }

        print_progress((1.0 * (i + 1)) / points);
    }
    cout << endl;

    graph.merge_to_maximal();
    graph.generate_single_component_analysis();

    render_stuff(graph, sz, false, true, false);
    assert(validate(graph));
}
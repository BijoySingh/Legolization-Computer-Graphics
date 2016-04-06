//
// Created by Bijoy Kochar on 3/26/16.
//

#include <cstdio>
#include "LegoBlock.h"
#include "LegoBlockUtils.h"
#include "LegoBlockGraph.h"

void setToSphere(short ***image, short sx, short sy, short sz, short max_value, short r) {
    for (int i = 0; i < sx; i++) {
        for (int j = 0; j < sy; j++) {
            for (int k = 0; k < sz; k++) {
                float value = (i - (sx / 2)) * (i - (sx / 2)) + (j - (sy / 2)) * (j - (sy / 2)) +
                              (k - (sz / 2)) * (k - (sz / 2));
                value = sqrt(value);
                value = max_value * (value / r);

                if (value > max_value)
                    image[i][j][k] = -2;
                else if (value <= 3 * max_value / 4)
                    image[i][j][k] = -1;
                else
                    image[i][j][k] = (short) value;
            }
        }
    }
}

void setValue(short ***image, short sx, short sy, short sz, short value) {
    for (int i = 0; i < sx; i++) {
        for (int j = 0; j < sy; j++) {
            for (int k = 0; k < sz; k++) {
                image[i][j][k] = (short) value;
            }
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

void render_stuff(LegoBlockGraph &graph, short sz) {
    ofstream fout;
    fout.open("pixels.txt");
    graph.render_blocks(fout);
    fout.close();

    fout.open("../renderman/pixels.rib");
    graph.prman_render_blocks(fout, -1, false);
    fout.close();

    string cmd;

    for (int i = 0; i < sz; i++) {
        fout.open("../renderman/layer.rib");
        graph.prman_render_blocks(fout, i, false);
        cmd = "cd ../renderman; make layer NUM=" + to_string(i + 1) + " ";
        const char *cmd_car = cmd.c_str();
        cout << cmd << endl;
        system(cmd_car);
        fout.close();
    }
    cmd = "cd ../renderman; make";
    const char *cmd_car = cmd.c_str();
    cout << cmd << endl;
    system(cmd_car);
}

int main() {
    short size = 20;
    short sx = size, sy = size, sz = size, max_value = 255;
    short ***r = getImageMatrix(sx, sy, sz);
    short ***g = getImageMatrix(sx, sy, sz);

    setToSphere(r, sx, sy, sz, max_value, 8);
    setValue(g, sx, sy, sz, 0);

    LegoBlockGraph graph;
    graph.add_blocks(r, g, g, sx , sy , sz);
    graph.merge_to_maximal();
    graph.generate_single_component_analysis();

    render_stuff(graph, sz);
}

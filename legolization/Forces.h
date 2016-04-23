//
// Created by Bijoy Kochar on 4/6/16.
//

#ifndef GRAPHICSPROJECT_FORCES_H
#define GRAPHICSPROJECT_FORCES_H

#include <list>

using namespace std;

#define LEGO_WEIGHT 0.0003
#define FRIC_T 0.702
#define PARAMS 6
#define GRAVITY 9.8

enum ForceType {NORMAL, FRICTION, NORMAL_UNCONSTRAINED, OTHER, WEIGHT};

class Force {
public:
    ForceType type;
    float value;
    int direction[3];
    float positions[3];
    bool known_value;
    bool known_position;
    bool known_direction;

    Force(ForceType type) {
        this->type = type;
        known_value = false;
        known_direction = false;
        known_value = false;
    }

    void setDirection(int dx, int dy, int dz) {
        direction[0] = dx;
        direction[1] = dy;
        direction[2] = dz;
        known_direction = true;
    }

    void setValue(float value) {
        this->value = value;
        known_value = true;
    }

    void setPosition(float px, float py, float pz) {
        positions[0] = px;
        positions[1] = py;
        positions[2] = pz;
        known_position = true;
    }
};

struct ForceConstraint {
    Force weight = Force(WEIGHT);
    int start;
    int stop;

    ForceConstraint(Force weight, int start, int stop) {
        this->weight = weight;
        this->start = start;
        this->stop = stop;
    }
};


#endif //GRAPHICSPROJECT_FORCES_H

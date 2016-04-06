//
// Created by Bijoy Kochar on 4/6/16.
//

#ifndef GRAPHICSPROJECT_FORCES_H
#define GRAPHICSPROJECT_FORCES_H

#define LEGO_WEIGHT 0.3
enum ForceType {NORMAL, FRICTION, WEIGHT, OTHER};

class Force {
public:
    ForceType type;
    bool known;
    float value;
    int direction[3];

    Force(ForceType type, int dx, int dy, int dz) {
        this->type = type;
        known = false;
        direction[0] = dx;
        direction[1] = dy;
        direction[2] = dz;
    }

    Force(ForceType type, float value, int dx, int dy, int dz) {
        this->type = type;
        known = true;
        direction[0] = dx;
        direction[1] = dy;
        direction[2] = dz;
        this->value = value;
    }
};

class LegoBlockForces {
public:
    float weight;
    list<Force> forces;
    list<Force> normals;
    list<Force> frictions;
};

#endif //GRAPHICSPROJECT_FORCES_H

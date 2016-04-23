//
// Created by Bijoy Kochar on 4/6/16.
//

#ifndef GRAPHICSPROJECT_LEGOSTABILITYUTIL_H
#define GRAPHICSPROJECT_LEGOSTABILITYUTIL_H

#include "Forces.h"
#include "LegoBlock.h"
#include "LegoBlockGraph.h"
#include "LegoBlockUtils.h"
#include <nlopt.hpp>
#include <utility>
#include <cmath>
#include <unordered_map>

#define LEGO_SQUARE 0.008
#define LEGO_KNOB 0.0048
#define DELIMITER "########"

using namespace std;
using namespace nlopt;

class LegoBlockGraph;
class LegoStabilityUtil {
public:
    LegoBlockGraph *g;
    LegoStabilityUtil(LegoBlockGraph *g);
    list< pair<LegoBlock*, list<Force> > > getForces();
    pair<int, LegoBlock*> getStabilityAnalysis();
};

struct LegoForceConstraintData {
public:
    list<Force> *force;
    ForceConstraint *constraint;
};

#endif //GRAPHICSPROJECT_LEGOSTABILITYUTIL_H

//
// Created by Bijoy Kochar on 4/6/16.
//

#ifndef GRAPHICSPROJECT_LEGOSTABILITYUTIL_H
#define GRAPHICSPROJECT_LEGOSTABILITYUTIL_H

#include "Forces.h"
#include "LegoBlock.h"
#include "LegoBlockGraph.h"
#include <nlopt.hpp>
#include <utility>
#include <cmath>

using namespace std;
using namespace nlopt;

class LegoStabilityUtil {
public:
    LegoBlockGraph *g;
    LegoStabilityUtil(LegoBlockGraph *g);
    list<LegoBlockForces> getForces();
    pair<int, LegoBlock*> getStabilityAnalysis();
};

#endif //GRAPHICSPROJECT_LEGOSTABILITYUTIL_H

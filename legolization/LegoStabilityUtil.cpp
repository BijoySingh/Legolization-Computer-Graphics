//
// Created by Bijoy Kochar on 4/6/16.
//

#include "LegoStabilityUtil.h"



LegoStabilityUtil::LegoStabilityUtil(LegoBlockGraph *g) {
    this->g = g;

    cout<<endl<<DELIMITER<<endl;
    g->print_info();
    cout<<DELIMITER<<endl<<endl;
}

list< pair<LegoBlock*, list<Force> > > LegoStabilityUtil::getForces() {
    list< pair<LegoBlock*, list<Force> > > final_forces;
    for (LegoBlock* block : g->blocks) {
        list<Force> forces;
        for (LegoBlock* child : g->graph[block]) {
            list<pair<int, int> > overlap = LegoBlockUtils::overlaps(block, child);
            for (auto pr : overlap) {
                Force friction(FRICTION);
                friction.setDirection(0, 0, 1);
                friction.setPosition(pr.first * LEGO_SQUARE + LEGO_KNOB / 2, pr.second * LEGO_SQUARE + LEGO_KNOB / 2, 1);
                forces.push_back(friction);

                Force normal(NORMAL_UNCONSTRAINED);
                normal.setPosition(pr.first * LEGO_SQUARE + LEGO_KNOB / 2, pr.second * LEGO_SQUARE + LEGO_KNOB / 2, 1);
                normal.setDirection(1, 0, 0);
                forces.push_back(normal);
                normal.setDirection(0, 1, 0);
                forces.push_back(normal);
            }

//            Force normal(NORMAL);
//            normal.setDirection(0, 0, -1);
//            forces[block].push_back(normal);
        }

        for (LegoBlock* parent : g->reverse_graph[block]) {
            list<pair<int, int> > overlap = LegoBlockUtils::overlaps(parent, block);
            for (auto pr : overlap) {
                Force friction(FRICTION);
                friction.setDirection(0, 0, 1);
                friction.setPosition(pr.first * LEGO_SQUARE + LEGO_KNOB / 2, pr.second * LEGO_SQUARE + LEGO_KNOB / 2, 0);
                forces.push_back(friction);

                Force normal(NORMAL_UNCONSTRAINED);
                normal.setPosition(pr.first * LEGO_SQUARE + LEGO_KNOB / 2, pr.second * LEGO_SQUARE + LEGO_KNOB / 2, 0);
                normal.setDirection(1, 0, 0);
                forces.push_back(normal);
                normal.setDirection(0, 1, 0);
                forces.push_back(normal);
            }

//            Force normal(NORMAL);
//            normal.setDirection(0, 0, 1);
//            forces[block].push_back(normal);
        }

        for (LegoBlock* neighbour : g->horizontal_neighbours[block]) {
            // int overlap = LegoBlockUtils::overlap(neighbour, block);
        }

        final_forces.push_back(make_pair(block, forces));
    }

    return final_forces;
}

double maximization_function(const std::vector<double> &x, std::vector<double> &grad, void* f_data) {
    LegoForceConstraintData*  frictions = (LegoForceConstraintData *) f_data;
    double min_diff = 10000000;
    int index = 0;
    for (Force force : *(frictions->force)) {
        if (force.type == FRICTION) {
            double diff = FRIC_T - x[index];
            min_diff = min(min_diff, diff);
        }
        index++;
    }
    return min_diff;
}

double trans_eqbm_constraint(const std::vector<double> &x, std::vector<double> &grad, void* f_data) {
    double vx = 0, vy = 0, vz = 0;
    LegoForceConstraintData* forces = (LegoForceConstraintData *) f_data;
    ForceConstraint p = *(forces->constraint);

    int i = 0;
    for (Force force : *(forces->force)) {
        if (i >= p.start && i < p.stop) {
            vx += x[i] * force.direction[0];
            vy += x[i] * force.direction[1];
            vz += x[i] * force.direction[2];
        }
        i++;
    }

    vx += p.weight.value * p.weight.direction[0];
    vy += p.weight.value * p.weight.direction[1];
    vz += p.weight.value * p.weight.direction[2];

    return sqrt(vx * vx + vy * vy + vz * vz);
}

double rot_eqbm_constraint(const std::vector<double> &x, std::vector<double> &grad, void* f_data) {
    double vx = 0, vy = 0, vz = 0;

    LegoForceConstraintData* forces = (LegoForceConstraintData *) f_data;
    ForceConstraint p = *(forces->constraint);

    int i = 0;
    for (Force force : *(forces->force)) {
        if (i >= p.start && i < p.stop) {
            double a1 = force.positions[0];
            double a2 = force.positions[1];
            double a3 = force.positions[2];

            double b1 = x[i] * force.direction[0];
            double b2 = x[i] * force.direction[1];
            double b3 = x[i] * force.direction[2];

            vx +=  a2 * b3 - a3 * b2;
            vy += a3 * b1 - a1 * b3;
            vz += a1 * b2 - b1 * a2;
        }
        i++;
    }

    vx += p.weight.value * (p.weight.direction[1] * p.weight.positions[2] - p.weight.direction[2] * p.weight.positions[1]);
    vy += p.weight.value * (p.weight.direction[2] * p.weight.positions[0] - p.weight.direction[0] * p.weight.positions[2]);
    vz += p.weight.value * (p.weight.direction[0] * p.weight.positions[1] - p.weight.direction[1] * p.weight.positions[0]);

    return sqrt(vx * vx + vy * vy + vz * vz);
}

double direction_constraint(const std::vector<double> &x, std::vector<double> &grad, void* f_data) {
    double v = 0;
    list<int> p = * (list<int> *) f_data;
    for (auto f : p) {
        v += x[f] * x[f];
    }

    return sqrt(v);
}

double positivity_constraint(const std::vector<double> &x, std::vector<double> &grad, void* f_data) {
    int index  = *(int *) f_data;
    return -x[index];
}

pair<int, LegoBlock *> LegoStabilityUtil::getStabilityAnalysis() {
    int force_counter = 0;
    list< pair<LegoBlock*, list<Force> > > forces = getForces();
    list<Force> allForces;
    for (auto kv : forces) {
        force_counter += kv.second.size();
        allForces.insert(allForces.end(), kv.second.begin(), kv.second.end());
    }

    int optimizer_dimension = force_counter;
    cout << "Setting up the Optimizer of dimension " << optimizer_dimension << endl;
    nlopt::opt opt(nlopt::LN_COBYLA, optimizer_dimension);

    force_counter = 0;

    list<int> direction_list;
    list<int> *directions = &direction_list;

    list<int> positions;
    list<LegoBlock*> blocks;
    for (auto kv : forces) {
        LegoBlock* block = kv.first;

        float weight_value = block->sx * block->sy * LEGO_WEIGHT * GRAVITY;
        Force weight(WEIGHT);
        weight.setValue(weight_value);
        weight.setDirection(0, 0, -1);
        weight.setPosition(((int) (block->sx / 2)) * LEGO_SQUARE + LEGO_KNOB / 2,
                           ((int) (block->sy / 2)) * LEGO_SQUARE + LEGO_KNOB / 2, 0.5);

        int force_start = force_counter;
        force_counter += kv.second.size();

        ForceConstraint* constraint = new ForceConstraint(weight, force_start, force_counter);
        LegoForceConstraintData* force_constraint = new LegoForceConstraintData();
        force_constraint->constraint = constraint;
        force_constraint->force = &allForces;

        opt.add_equality_constraint(trans_eqbm_constraint, force_constraint, 1e-2);
        opt.add_equality_constraint(rot_eqbm_constraint, force_constraint, 1e-2);

        blocks.push_back(block);
        positions.push_back(force_counter);
    }

    LegoForceConstraintData* force_constraint = new LegoForceConstraintData();
    force_constraint->force = &allForces;
    opt.set_lower_bounds(-1);
    opt.set_upper_bounds(1);
    opt.set_max_objective(maximization_function, force_constraint);

    cout << "Optimizing constraints" << endl;
    vector<double> x(optimizer_dimension);
    double maxValue;
    nlopt::result result = opt.optimize(x, maxValue);
    cout << "Optimized Constraints" << endl;

    // Find which block has this lowest threshold
    double lowest_diff = 1000000000;
    int lowest_position = 0;
    int index = 0;
    for (Force force : allForces) {
        if (force.type == FRICTION) {
            double diff = FRIC_T - x[index];
            if (diff < lowest_diff) {
                lowest_position = index;
                lowest_diff = diff;
            }
        }

        index++;
    }

    int counter = 0;
    for (int position : positions) {
        if (position > lowest_position) {
            break;
        }
        counter++;
    }

    LegoBlock* target;
    for (LegoBlock* block: blocks) {
        if (counter == 0) {
            target = block;
            break;
        }
        counter--;
    }


    return make_pair(maxValue, target);
}
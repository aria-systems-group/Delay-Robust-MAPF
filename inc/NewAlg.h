#pragma once
#include "CBS.h"
#include "SpaceTimeAStar.h"


class NewAlg
{
public:
    NewAlg(Instance *instance, bool sipp, int screen);

    bool solve(double time_limit, int cost_lowerbound = 0, int cost_upperbound = MAX_COST);

    double runtime;
    bool solution_found;
    vector<Path*> paths;
    int solution_cost;
private:
    Instance* instance_;
    const int screen_;
    const bool sipp_;
    std::vector<Path> my_paths_{};
    DelayInstance* calcDelay();
    void resetInstance(Instance *new_instance);
};
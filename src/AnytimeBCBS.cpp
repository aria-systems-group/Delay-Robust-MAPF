#include "AnytimeBCBS.h"
#include "CBS.h"


void AnytimeBCBS::run()
{
    int num_of_agents = instance->getDefaultNumberOfAgents();
    bool improvements = true;
    double w = (double) MAX_COST / (instance->num_of_cols + instance->num_of_rows)
            / 10 / num_of_agents; // a large enough w without integer overflow issue
    CBS bcbs(instance, false, screen);
    bcbs.setPrioritizeConflicts(improvements);
    bcbs.setDisjointSplitting(false);
    bcbs.setBypass(improvements);
    bcbs.setRectangleReasoning(improvements);
    bcbs.setCorridorReasoning(improvements);
    bcbs.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    bcbs.setTargetReasoning(improvements);
    bcbs.setMutexReasoning(false);
    bcbs.setConflictSelectionRule(conflict_selection::EARLIEST);
    bcbs.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS);
    bcbs.setSavingStats(false);
    bcbs.setHighLevelSolver(high_level_solver_type::ASTAREPS, w);

    preprocessing_time = bcbs.runtime_preprocessing;
    sum_of_distances = 0;
    for (int i = 0; i < num_of_agents; i++)
    {
        sum_of_distances += bcbs.getSearchEngine(i)->my_heuristic[bcbs.getSearchEngine(i)->start_location.location];
    }

    // run
    CBSNode* best_goal_node = nullptr;
    // std::cout << sum_of_costs << " vs. " << sum_of_costs_lowerbound << std::endl;
    while(runtime < time_limit && sum_of_costs > sum_of_costs_lowerbound)
    {
        bcbs.solve(time_limit - runtime, sum_of_costs_lowerbound, sum_of_costs);
        runtime += bcbs.runtime;
        assert(sum_of_costs_lowerbound <= bcbs.getLowerBound());
        sum_of_costs_lowerbound = bcbs.getLowerBound();
        if (bcbs.solution_found)
        {
            assert(sum_of_costs > bcbs.solution_cost);
            sum_of_costs = bcbs.solution_cost;
            best_goal_node = bcbs.getGoalNode();
            iteration_stats.emplace_back(instance->getDefaultNumberOfAgents(), sum_of_costs,
                                         runtime, "BCBS", sum_of_costs_lowerbound);
        }

        if (screen >= 1)
            cout << "Iteration " << iteration_stats.size() << ", "
                 << "lower bound = " << sum_of_costs_lowerbound << ", "
                 << "solution cost = " << sum_of_costs << ", "
                 << "remaining time = " << time_limit - runtime << endl;
    }
    if (best_goal_node == nullptr)
        sum_of_costs = -1; // no solution found
    else
    {
        solution.resize(num_of_agents);
        bcbs.updatePaths(best_goal_node);
        for (int i = 0; i < num_of_agents; i++)
            solution[i] = *bcbs.paths[i];
    }
    bcbs.clearSearchEngines();
    cout << getSolverName() << ": Iterations = " << iteration_stats.size() << ", "
         << "lower bound = " << sum_of_costs_lowerbound << ", "
         << "solution cost = " << sum_of_costs << ", "
         << "initial solution cost = " << iteration_stats.front().sum_of_costs << ", "
         << "runtime = " << runtime << endl;
}


bool AnytimeBCBS::validateSolution() const
{
    if (solution.empty())
        return true;
    int N = instance->getDefaultNumberOfAgents();
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            const auto a1 = solution[i].size() <= solution[j].size()? i : j;
            const auto a2 = solution[i].size() <= solution[j].size()? j : i;
            int t = 1;
            for (; t < (int) solution[a1].size(); t++)
            {
                if (solution[a1][t].Loc.location == solution[a2][t].Loc.location) // vertex conflict
                {
                    cerr << "Find a vertex conflict between agents " << a1 << " and " << a2 <<
                         " at location " << solution[a1][t].Loc.location << " at timestep " << t << endl;
                    exit(-1);
                }
                else if (solution[a1][t].Loc.location == solution[a2][t - 1].Loc.location &&
                        solution[a1][t - 1].Loc.location == solution[a2][t].Loc.location) // edge conflict
                {
                    cerr << "Find an edge conflict between agents " << a1 << " and " << a2 <<
                         " at edge (" << solution[a1][t - 1].Loc.location << "," << solution[a1][t].Loc.location <<
                         ") at timestep " << t << endl;
                    exit(-1);
                }
            }
            int target = solution[a1].back().Loc.location;
            for (; t < (int) solution[a2].size(); t++)
            {
                if (solution[a2][t].Loc.location == target)  // target conflict
                {
                    cerr << "Find a target conflict where agent " << a2 << " traverses agent " << a1 <<
                         "'s target location " << target << " at timestep " << t << endl;
                    exit(-1);
                }
            }
        }
    }
    std::cout << "Plan is correct" << std::endl;
    return true;
}

void AnytimeBCBS::writeIterStatsToFile(string file_name) const
{
    std::ofstream output;
    output.open(file_name);
    // header
    output << "num of agents," <<
           "sum of costs," <<
           "runtime," <<
           "cost lowerbound," <<
           "MAPF algorithm" << endl;

    for (const auto &data : iteration_stats)
    {
        output << data.num_of_agents << "," <<
               data.sum_of_costs << "," <<
               data.runtime << "," <<
               data.sum_of_costs_lowerbound << "," <<
               data.algorithm << endl;
    }
    output.close();
}

void AnytimeBCBS::writeResultToFile(string file_name) const
{
    std::ifstream infile(file_name);
    bool exist = infile.good();
    infile.close();
    if (!exist)
    {
        ofstream addHeads(file_name);
        addHeads << "runtime,solution cost,initial solution cost,min f value,root g value," <<
                 "iterations," <<
                 "runtime of initial solution,area under curve," <<
                 "preprocessing runtime,solver name,instance name" << endl;
        addHeads.close();
    }
    double auc = 0;
    if (!iteration_stats.empty())
    {
        auto prev = iteration_stats.begin();
        auto curr = prev;
        ++curr;
        while (curr != iteration_stats.end() && curr->runtime < time_limit)
        {
            auc += (prev->sum_of_costs - sum_of_distances) * (curr->runtime - prev->runtime);
            prev = curr;
            ++curr;
        }
        auc += (prev->sum_of_costs - sum_of_distances) * (time_limit - prev->runtime);
    }
    ofstream stats(file_name, std::ios::app);
    stats << runtime << "," << sum_of_costs << "," << iteration_stats.front().sum_of_costs << "," <<
          sum_of_costs_lowerbound << "," << sum_of_distances << "," <<
          iteration_stats.size() << "," << iteration_stats.front().runtime << "," <<  auc << "," <<
          preprocessing_time << "," << getSolverName() << "," << instance->getInstanceName() << endl;
    stats.close();
}

void AnytimeBCBS::writePathsToFile(const string & file_name) const
{
    std::ofstream output;
    output.open(file_name);
    // header
    // output << agents.size() << endl;

    for (int ag = 0; ag < solution.size(); ag++)
    {
        output << "Agent " << ag << ":";
        for (const auto &state : solution[ag])
            output << "(" << (*instance).getRowCoordinate(state.Loc.location) << "," <<
                            (*instance).getColCoordinate(state.Loc.location) << ")->";
        output << endl;
    }
    output.close();
}

void AnytimeBCBS::countInducedDelays(std::vector<Path> &old_paths) const
{
    // first, run sanity checks
    const int shift = instance->delay_->second + 1;
    // now, examine the number of delays
    // note that delays may only be induced iff new path > 1
    std::vector<int> agent_ids{};
    for (int ag = 0; ag < solution.size(); ag++)
    {
        if (solution[ag].size() > 1)
            agent_ids.push_back(ag);
    }

    for (int a : agent_ids)
    {
        // std::cout << "Agent: " << a << std::endl;
        auto new_path = solution[a];
        auto old_path = old_paths[a];
        int new_idx = 0;
        int old_idx = shift;
        // for (int t = shift; t < old_paths[a].size(); t++)
        while ((new_path.begin() + new_idx != new_path.end()))
        {
            // std::cout << "new loc: " << new_path[new_idx].Loc.location << std::endl;
            // std::cout << "old loc: " << old_path[old_idx].Loc.location << std::endl;
            while ( new_path[new_idx].Loc.location != old_path[old_idx].Loc.location )
            {
                new_idx++;
                instance->numDelays++;
            }
            old_idx++;
            new_idx++;
        }
        // std::cout << "numDelays: " << instance->numDelays << std::endl;
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    std::cout << "induced " << instance->numDelays << " delays" << std::endl;
}

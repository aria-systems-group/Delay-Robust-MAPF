#include "NewAlg.h"


NewAlg::NewAlg(Instance *instance, bool sipp, int screen):
    instance_(instance), sipp_(sipp), screen_(screen), 
    runtime(-1), solution_found(false), solution_cost(-1) 
{
    paths = {};
}


bool NewAlg::solve(double time_limit, int cost_lowerbound, int cost_upperbound)
{
    bool improvements = true;
    CBS cbs1(instance_, sipp_, screen_);
    cbs1.setPrioritizeConflicts(improvements);
    cbs1.setDisjointSplitting(false);
    cbs1.setBypass(improvements);
    cbs1.setRectangleReasoning(improvements);
    cbs1.setCorridorReasoning(improvements);
    cbs1.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    cbs1.setTargetReasoning(improvements);
    cbs1.setMutexReasoning(false);
    cbs1.setConflictSelectionRule(conflict_selection::EARLIEST);
    cbs1.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS);
    cbs1.setSavingStats(false);
    cbs1.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);
    cbs1.output_root_node = true;

    cbs1.solve(time_limit, cost_lowerbound, cost_upperbound);

    // get solution from root node of CBS
    if (cbs1.solution_found)
    {
        for (int a = 0; a < cbs1.paths.size(); a++)
        {
            Path a_path;
            for (int i = 0; i < cbs1.paths[a]->size(); i++) // const auto entry : agent.path
            {
                auto entry = (*cbs1.paths[a])[i];
                a_path.emplace_back(entry);
            }
            my_paths_.push_back(a_path);
        }
        // create a delay instance
        DelayInstance* nxt_instance = calcDelay();

        // for (int a=0; a < nxt_instance->getDefaultNumberOfAgents(); a++)
        // {
        //     std::cout << nxt_instance->getStarts()[a].location << std::endl;
        // }

        // solve the delay instance to completely solve MAPF
        bool improvements = true;
        CBS cbs2(nxt_instance, sipp_, screen_);
        cbs2.setPrioritizeConflicts(improvements);
        cbs2.setDisjointSplitting(false);
        cbs2.setBypass(improvements);
        cbs2.setRectangleReasoning(improvements);
        cbs2.setCorridorReasoning(improvements);
        cbs2.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
        cbs2.setTargetReasoning(improvements);
        cbs2.setMutexReasoning(false);
        cbs2.setConflictSelectionRule(conflict_selection::EARLIEST);
        cbs2.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS);
        cbs2.setSavingStats(false);
        cbs2.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);

        cbs2.solve(time_limit, cost_lowerbound, cost_upperbound);

        runtime = cbs2.runtime;

        if (cbs2.solution_found && cbs2.validateSolution())
        {
            std::cout << "Found Correct Solution" << std::endl;
            solution_found = true;
            for (int a = 0; a < cbs2.paths.size(); a++)
            {
                Path* a_path = new Path();
                for (int i = 0; i < cbs2.paths[a]->size(); i++) // const auto entry : agent.path
                {
                    auto entry = (*cbs2.paths[a])[i];
                    (*a_path).emplace_back(entry);
                }
            }
            solution_cost = cbs2.solution_cost;
        }
        else
        {
            std::cout << "No solution found within allocated time" << std::endl;
            solution_found = false;
        }
    }
    return solution_found;
}

DelayInstance* NewAlg::calcDelay()
{
    // create delay instance
    DelayInstance* nxtInstance = new DelayInstance(instance_->getMapFile(), 
            instance_->getInstanceName(), my_paths_, instance_->getDefaultNumberOfAgents(), true);

    // if found a delay, then create new planner instance
    if ((*nxtInstance).foundDelay())
    {
        // run sanity checks
        std::cout <<"running sanity check" << std::endl;
        for (int i = 0; i < nxtInstance->getStarts().size();  i++)
        {
            nxtInstance->agent_idx = i;
            if (!nxtInstance->isConnected(nxtInstance->getStarts()[i], nxtInstance->getGoals()[i]))
            {
                std::cout << "running sanity check for agent " << i << std::endl;
                std::cout << "start: " << nxtInstance->getCoordinate(nxtInstance->getStarts()[i].location).first << "," <<
                    nxtInstance->getCoordinate(nxtInstance->getStarts()[i].location).second << std::endl;
                std::cout << "goal: " << nxtInstance->getCoordinate(nxtInstance->getGoals()[i].location).first << "," <<
                    nxtInstance->getCoordinate(nxtInstance->getGoals()[i].location).second << std::endl;
                std::cout << i << " failed!" << std::endl;
                exit(1);
            }
        }
        std::cout << "Sanity checks succeeded. Ready to correct delayed plan..." << std::endl;;
    }
    return nxtInstance;
}

void NewAlg::resetInstance(Instance *new_instance)
{
    // // reset the cbs instance ptr
    // instance_ = new_instance;

    // // reset the low-level searches
    // search_engines.clear();
    // search_engines.resize(num_of_agents);
    // for (int i = 0; i < num_of_agents; i++)
    //     search_engines[i] = new SpaceTimeAStar(instance_, i,  instance_->originalPlan[i]);

    // // reset heuristic helper and MDD
    // for (int i = 0; i < num_of_agents; i++){
    //     auto itr = mdd_helper.search_engines.begin() + i;
    //     (*itr) = search_engines[i];
    // }

    // CBSHeuristic new_heuristic_helper(instance_->getDefaultNumberOfAgents(), orig_paths, search_engines, initial_constraints, mdd_helper);
    // heuristic_helper = new_heuristic_helper;
}




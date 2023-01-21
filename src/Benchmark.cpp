#include "Benchmark.h"


unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

string random_string()
{
     string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     std::random_device rd;
     std::mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, 20);    // assumes 20 < number of characters in str         
}

std::unordered_map<std::string, std::string> runExperiment_3(const po::variables_map vm)
{
    // initialize the results directory
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"initial-runtime",                                            std::to_string(dummy_var)},
        {"initial-soc",                                                std::to_string(dummy_var)},
        // replan w/ CBS on CG
        {"replan-CBS-CG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-CG-soc",                                          std::to_string(dummy_var)},
        {"replan-CBS-CG-numDelays",                                    std::to_string(dummy_var)},
        // replan w/ CBS on ICG
        {"replan-CBS-ICG-runtime",                                     std::to_string(dummy_var)},
        {"replan-CBS-ICG-soc",                                         std::to_string(dummy_var)},
        {"replan-CBS-ICG-numDelays",                                   std::to_string(dummy_var)}
    };
    
    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with LNS
    calcInitialSolution_LNS(vm, results, dataResults);
    // std::cout << "initial" << std::endl;
    // std::cout << results["Example-ID"] << std::endl;
    // std::cout << results["Num-Agents"] << std::endl;
    // std::cout << results["initial-runtime"] << std::endl;
    // std::cout << results["initial-soc"] << std::endl;

    // if initial plan was successful, then continue with replanning
    if (results["Example-ID"] != "")
    {
        // calculate the delay and create delay instance
        DelayInstance* delay_instance = calcDelay(vm, results, dataResults);

        // change start locations for replanning on OG
        dataResults.original_instance->updateStartLocations(delay_instance->getStarts());

        // update delay for replanning on OG b/c its needed for soc calc
        dataResults.original_instance->delay_ = delay_instance->delay_;

        // replan w/ CBS on CG
        calcReplan_CBS_CG(delay_instance, vm, results, dataResults);
        // std::cout << "replan CBS CG" << std::endl;
        // std::cout << results["replan-CBS-CG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-CG-soc"] << std::endl;
        // std::cout << results["replan-CBS-CG-numDelays"] << std::endl;

        // activate ICG
        delay_instance->activateImprovement();

        // replan w/ CBS on ICG
        calcReplan_CBS_ICG(delay_instance, vm, results, dataResults);
        // std::cout << "replan CBS ICG" << std::endl;
        // std::cout << results["replan-CBS-ICG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-ICG-soc"] << std::endl;
        // std::cout << results["replan-CBS-ICG-numDelays"] << std::endl;
    }
    return results;
}

std::unordered_map<std::string, std::string> runExperiment_2(const po::variables_map vm)
{
    // initialize the results directory
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"initial-runtime",                                            std::to_string(dummy_var)},
        {"initial-soc",                                                std::to_string(dummy_var)},
        // replan w/ CBS on OG
        {"replan-CBS-OG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-OG-soc",                                          std::to_string(dummy_var)},
        // replan w/ CBS on CG
        {"replan-CBS-CG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-CG-soc",                                          std::to_string(dummy_var)},
        {"replan-CBS-CG-numDelays",                                    std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on OG
        {"replan-LNS-SIPP-OG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-soc",                                     std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on CG
        {"replan-LNS-SIPP-CG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-soc",                                     std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-numDelays",                               std::to_string(dummy_var)}
    };
    
    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with LNS
    calcInitialSolution_CBS(vm, results, dataResults);
    // std::cout << "initial" << std::endl;
    // std::cout << results["Example-ID"] << std::endl;
    // std::cout << results["Num-Agents"] << std::endl;
    // std::cout << results["initial-runtime"] << std::endl;
    // std::cout << results["initial-soc"] << std::endl;

    // if initial plan was successful, then continue with replanning
    if (results["Example-ID"] != "")
    {
        // calculate the delay and create delay instance
        DelayInstance* delay_instance = calcDelay(vm, results, dataResults);

        // change start locations for replanning on OG
        dataResults.original_instance->updateStartLocations(delay_instance->getStarts());

        // update delay for replanning on OG b/c its needed for soc calc
        dataResults.original_instance->delay_ = delay_instance->delay_;

        // replan w/ CBS on OG
        calcReplan_CBS_OG(dataResults.original_instance, vm, results, dataResults);
        // std::cout << "replan CBS OG" << std::endl;
        // std::cout << results["replan-CBS-OG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-OG-soc"] << std::endl;

        // replan w/ CBS on CG
        calcReplan_CBS_CG(delay_instance, vm, results, dataResults);
        // std::cout << "replan CBS CG" << std::endl;
        // std::cout << results["replan-CBS-CG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-CG-soc"] << std::endl;
        // std::cout << results["replan-CBS-CG-numDelays"] << std::endl;

        // replan w/ LNS-SIPP on OG
        calcReplan_LNS_SIPP_OG(dataResults.original_instance, vm, results, dataResults);
        // std::cout << "replan LNS OG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-soc"] << std::endl;

        // replan w/ LNS-SIPP on CG
        calcReplan_LNS_SIPP_CG(delay_instance, vm, results, dataResults);
        // std::cout << "replan LNS CG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-soc"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-numDelays"] << std::endl; 
    }
    return results;
}

std::unordered_map<std::string, std::string> runExperiment_1(const po::variables_map vm)
{
    // initialize the results directory
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"initial-runtime",                                            std::to_string(dummy_var)},
        {"initial-soc",                                                std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on OG
        {"replan-LNS-SIPP-OG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-soc",                                     std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on CG
        {"replan-LNS-SIPP-CG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-soc",                                     std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-numDelays",                               std::to_string(dummy_var)},
        // replan CBS on CG
        {"replan-CBS-CG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-CG-soc",                                          std::to_string(dummy_var)},
        {"replan-CBS-CG-numDelays",                                    std::to_string(dummy_var)}
    };

    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with LNS
    calcInitialSolution_LNS(vm, results, dataResults);
    // std::cout << "initial" << std::endl;
    // std::cout << results["Example-ID"] << std::endl;
    // std::cout << results["Num-Agents"] << std::endl;
    // std::cout << results["initial-runtime"] << std::endl;
    // std::cout << results["initial-soc"] << std::endl;

    // if initial plan was successful, then continue with replanning
    if (results["Example-ID"] != "")
    {
        // calculate the delay and create delay instance
        DelayInstance* delay_instance = calcDelay(vm, results, dataResults);

        // change start locations for replanning on OG
        dataResults.original_instance->updateStartLocations(delay_instance->getStarts());

        // update delay for replanning on OG b/c its needed for soc calc
        dataResults.original_instance->delay_ = delay_instance->delay_;

        // replan w/ LNS-SIPP on OG
        calcReplan_LNS_SIPP_OG(dataResults.original_instance, vm, results, dataResults);
        // std::cout << "replan LNS OG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-soc"] << std::endl;

        // replan w/ LNS-SIPP on CG
        calcReplan_LNS_SIPP_CG(delay_instance, vm, results, dataResults);
        // std::cout << "replan LNS CG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-soc"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-CG-numDelays"] << std::endl;

        // replan w/ CBS on OG
        // calcReplan_CBS_OG(dataResults.original_instance, vm, results, dataResults);
        // std::cout << "replan CBS OG" << std::endl;
        // std::cout << results["replan-CBS-OG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-OG-soc"] << std::endl;

        // replan w/ CBS on CG
        calcReplan_CBS_CG(delay_instance, vm, results, dataResults);
        // std::cout << "replan CBS CG" << std::endl;
        // std::cout << results["replan-CBS-CG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-CG-soc"] << std::endl;
        // std::cout << results["replan-CBS-CG-numDelays"] << std::endl;
    }

    // return filled out results directory
    return results;
}

void calcInitialSolution_LNS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    // set-up LNS
    PIBTPPS_option pipp_options;
    pipp_options.windowSize = vm["pibtWindow"].as<int>();
    pipp_options.winPIBTSoft = vm["winPibtSoftmode"].as<bool>();

    data.pipp_options = pipp_options;

    // initialize traditional instance object
    Instance* instance = new Instance(vm["map"].as<string>(), vm["agents"].as<string>(),
        vm["agentNum"].as<int>());

    data.original_instance = instance;

    // save instance-related data
    results["Num-Agents"] = std::to_string(instance->getDefaultNumberOfAgents());
    
    // initialize LNS object
    LNS lns(instance, vm["cutoffTime"].as<double>(),
                vm["initAlgo"].as<string>(),
                vm["replanAlgo"].as<string>(),
                vm["destoryStrategy"].as<string>(),
                vm["neighborSize"].as<int>(),
                vm["maxIterations"].as<int>(),
                vm["initLNS"].as<bool>(),
                vm["initDestoryStrategy"].as<string>(),
                vm["sipp"].as<bool>(),
                vm["screen"].as<int>(), pipp_options);

    // run LNS
    bool succ = lns.run();

    // save computation time
    results["initial-runtime"] = std::to_string(lns.runtime);

    if (succ)
    {
        // make sure solution is correct
        lns.validateSolution();

        // create the results directory
        results["Example-ID"] = random_string();
        string random_dir_str = "Results/" + results["Example-ID"] + "/";
        data.local_path = random_dir_str; // Is this assignment safe?
        fs::create_directories(data.local_path);

        // save initial plan to directory and shared data
        ofstream myfile;
        myfile.open (string(data.local_path) + "initial_solution.txt");
        for (const auto &agent : lns.agents)
        {
            myfile << "Agent: " << agent.id << std::endl;
            Path a_path;
            for (int i = 0; i < agent.path.size(); i++) // const auto entry : agent.path
            {
                auto entry = agent.path[i];
                myfile << i << " " <<
                instance->getRowCoordinate(entry.Loc.location) << " " << 
                instance->getColCoordinate(entry.Loc.location) << std::endl;
                a_path.emplace_back(entry);
            }
            data.initial_plan.push_back(a_path);
        }
        myfile.close();
        results["initial-soc"] = std::to_string(lns.iteration_stats.back().sum_of_costs);
    }
    return;
}

void calcInitialSolution_CBS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    // set-up LNS (possibly needed later)
    PIBTPPS_option pipp_options;
    pipp_options.windowSize = vm["pibtWindow"].as<int>();
    pipp_options.winPIBTSoft = vm["winPibtSoftmode"].as<bool>();

    data.pipp_options = pipp_options;

    // initialize traditional instance object
    Instance* instance = new Instance(vm["map"].as<string>(), vm["agents"].as<string>(),
        vm["agentNum"].as<int>());

    data.original_instance = instance;

    // save instance-related data
    results["Num-Agents"] = std::to_string(instance->getDefaultNumberOfAgents());

    bool improvements = true;
    CBS cbs(instance, false, vm["screen"].as<int>());
    cbs.setPrioritizeConflicts(improvements);
    cbs.setDisjointSplitting(false);
    cbs.setBypass(improvements);
    cbs.setRectangleReasoning(improvements);
    cbs.setCorridorReasoning(improvements);
    cbs.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    cbs.setTargetReasoning(improvements);
    cbs.setMutexReasoning(false);
    cbs.setConflictSelectionRule(conflict_selection::EARLIEST);
    cbs.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS); //
    cbs.setSavingStats(false);
    cbs.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);

    cbs.solve(vm["cutoffTime"].as<double>(), 0, MAX_COST);

    // save computation time
    results["initial-runtime"] = std::to_string(cbs.runtime);

    if (cbs.solution_found && cbs.validateSolution())
    {
        // create the results directory
        results["Example-ID"] = random_string();
        string random_dir_str = "Results/" + results["Example-ID"] + "/";
        data.local_path = random_dir_str; // Is this assignment safe?
        fs::create_directories(data.local_path);

        // save initial plan to directory and shared data
        ofstream myfile;
        myfile.open (string(data.local_path) + "initial_solution.txt");
        for (int a = 0; a < cbs.paths.size(); a++)
        {
            myfile << "Agent: " << a << std::endl;
            Path a_path;
            for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
            {
                auto entry = (*cbs.paths[a])[i];
                myfile << i << " " <<
                instance->getRowCoordinate(entry.Loc.location) << " " << 
                instance->getColCoordinate(entry.Loc.location) << std::endl;
                a_path.emplace_back(entry);
            }
            data.initial_plan.push_back(a_path);
        }
        myfile.close();
        results["initial-soc"] = std::to_string(cbs.solution_cost);
    }
}

DelayInstance* calcDelay(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData& data)
{
	// create delay instance
    DelayInstance* nxtInstance = new DelayInstance(vm["map"].as<string>(), 
    		vm["agents"].as<string>(), data.initial_plan, vm["agentNum"].as<int>());

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

        // save the delay
        // Create and open a text file
        ofstream mydelay(string(data.local_path) + "delay.txt");
        // Write to the file
        mydelay << (*nxtInstance->delay_).first << ' ' << (*nxtInstance->delay_).second;
        // Close the file
        mydelay.close();
    }
    return nxtInstance;
}

void calcReplan_LNS_SIPP_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
	// initialize LNS object
	LNS lns(replan_instance, vm["cutoffTime"].as<double>(),
                vm["initAlgo"].as<string>(),
                vm["replanAlgo"].as<string>(),
                vm["destoryStrategy"].as<string>(),
                vm["neighborSize"].as<int>(),
                vm["maxIterations"].as<int>(),
                vm["initLNS"].as<bool>(),
                vm["initDestoryStrategy"].as<string>(),
                true,
                vm["screen"].as<int>(), data.pipp_options);

	// run LNS
	bool succ = lns.run();

	// save computation time
	results["replan-LNS-SIPP-OG-runtime"] = std::to_string(lns.runtime);

	if (succ)
    {
    	// make sure solution is correct
        lns.validateSolution();

        // save new plan to directory and shared data
        ofstream myfile;
  		myfile.open (std::string(data.local_path) + "replan-LNS-SIPP-OG.txt");
        // int soc = 0; // must compute soc manually for replanning
        for (const auto &agent : lns.agents)
        {
        	myfile << "Agent: " << agent.id << std::endl;
            for (int i = 0; i < agent.path.size(); i++) // const auto entry : agent.path
            {
            	auto entry = agent.path[i];
            	myfile << i << " " <<
            	replan_instance->getRowCoordinate(entry.Loc.location) << " " << 
            	replan_instance->getColCoordinate(entry.Loc.location) << std::endl;
            }
            // if (agent.path.size() == 1)
            //     soc += replan_instance->delay_->second + 1;
            // else
            //     soc += replan_instance->delay_->second + agent.path.size();
        }
        results["replan-LNS-SIPP-OG-soc"] = std::to_string(lns.iteration_stats.back().sum_of_costs);
        myfile.close();
    }
}

void calcReplan_LNS_SIPP_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    delay_instance->numDelays = 0;
	// initialize LNS object
    LNS lns(delay_instance, vm["cutoffTime"].as<double>(),
                vm["initAlgo"].as<string>(),
                vm["replanAlgo"].as<string>(),
                vm["destoryStrategy"].as<string>(),
                vm["neighborSize"].as<int>(),
                vm["maxIterations"].as<int>(),
                vm["initLNS"].as<bool>(),
                vm["initDestoryStrategy"].as<string>(),
                true,
                vm["screen"].as<int>(), data.pipp_options);

	// run LNS
    bool succ = lns.run();

    // save computation time
    results["replan-LNS-SIPP-CG-runtime"] = std::to_string(lns.runtime);

    if (succ)
    {
        // make sure solution is correct
        lns.validateSolution();

        // count delays
        lns.countInducedDelays(delay_instance->postDelayPlan);

        // save new plan to directory and shared data
        ofstream myfile;
        myfile.open (std::string(data.local_path) + "replan-LNS-SIPP-CG.txt");
        // int soc = 0; // must compute soc manually for replanning
        for (const auto &agent : lns.agents)
        {
            myfile << "Agent: " << agent.id << std::endl;
            for (int i = 0; i < agent.path.size(); i++) // const auto entry : agent.path
            {
                auto entry = agent.path[i];
                myfile << i << " " <<
                delay_instance->getRowCoordinate(entry.Loc.location) << " " << 
                delay_instance->getColCoordinate(entry.Loc.location) << std::endl;
            }
            // if (agent.path.size() == 1)
            //     soc += delay_instance->delay_->second + 1;
            // else
            //     soc += delay_instance->delay_->second + agent.path.size();
        }
        results["replan-LNS-SIPP-CG-soc"] = std::to_string(lns.iteration_stats.back().sum_of_costs);
        results["replan-LNS-SIPP-CG-numDelays"] = std::to_string(delay_instance->numDelays);
        myfile.close();
    }
}

void calcReplan_CBS_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    bool improvements = true;
    CBS cbs(replan_instance, false, vm["screen"].as<int>());
    cbs.setPrioritizeConflicts(improvements);
    cbs.setDisjointSplitting(false);
    cbs.setBypass(improvements);
    cbs.setRectangleReasoning(improvements);
    cbs.setCorridorReasoning(false);
    cbs.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    cbs.setTargetReasoning(improvements);
    cbs.setMutexReasoning(false);
    cbs.setConflictSelectionRule(conflict_selection::EARLIEST);
    cbs.setNodeSelectionRule(node_selection::NODE_H);
    cbs.setSavingStats(false);
    cbs.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);

    cbs.solve(vm["cutoffTime"].as<double>(), 0, MAX_COST);
    
    // save computation time
    results["replan-CBS-OG-runtime"] = std::to_string(cbs.runtime);

    if (cbs.solution_found && cbs.validateSolution())
    {
        // save new plan to directory and shared data
        ofstream myfile;
        myfile.open (std::string(data.local_path) + "replan-CBS-OG.txt");
        // int soc = 0; // must compute soc manually for replanning
        for (int a = 0; a < cbs.paths.size(); a++)
        {
            myfile << "Agent: " << a << std::endl;
            for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
            {
                auto entry = (*cbs.paths[a])[i];
                myfile << i << " " <<
                replan_instance->getRowCoordinate(entry.Loc.location) << " " << 
                replan_instance->getColCoordinate(entry.Loc.location) << std::endl;
            }
        }
        results["replan-CBS-OG-soc"] = std::to_string(cbs.solution_cost);
        myfile.close();
    }
}

void calcReplan_CBS_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    delay_instance->numDelays = 0;
    bool improvements = true;
    CBS cbs(delay_instance, false, vm["screen"].as<int>());
    cbs.setPrioritizeConflicts(improvements);
    cbs.setDisjointSplitting(false);
    cbs.setBypass(improvements);
    cbs.setRectangleReasoning(improvements);
    cbs.setCorridorReasoning(false);
    cbs.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    cbs.setTargetReasoning(improvements);
    cbs.setMutexReasoning(false);
    cbs.setConflictSelectionRule(conflict_selection::EARLIEST);
    cbs.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS); //
    cbs.setSavingStats(false);
    cbs.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);

    cbs.solve(vm["cutoffTime"].as<double>(), 0, MAX_COST);

    // save computation time
    results["replan-CBS-CG-runtime"] = std::to_string(cbs.runtime);
    
    if (cbs.solution_found && cbs.validateSolution())
    {
        // count delays
        cbs.countInducedDelays(delay_instance->postDelayPlan);

        // save new plan to directory and shared data
        ofstream myfile;
        myfile.open (std::string(data.local_path) + "replan-CBS-CG.txt");
        // int soc = 0; // must compute soc manually for replanning
        for (int a = 0; a < cbs.paths.size(); a++)
        {
            myfile << "Agent: " << a << std::endl;
            for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
            {
                auto entry = (*cbs.paths[a])[i];
                myfile << i << " " <<
                delay_instance->getRowCoordinate(entry.Loc.location) << " " << 
                delay_instance->getColCoordinate(entry.Loc.location) << std::endl;
            }
        }
        results["replan-CBS-CG-soc"] = std::to_string(cbs.solution_cost);
        results["replan-CBS-CG-numDelays"] = std::to_string(delay_instance->numDelays);
        myfile.close();
    }
}

void calcReplan_CBS_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    delay_instance->numDelays = 0;
    bool improvements = true;
    CBS cbs(delay_instance, false, vm["screen"].as<int>());
    cbs.setPrioritizeConflicts(improvements);
    cbs.setDisjointSplitting(false);
    cbs.setBypass(improvements);
    cbs.setRectangleReasoning(improvements);
    cbs.setCorridorReasoning(false);
    cbs.setHeuristicType(improvements? heuristics_type::WDG : heuristics_type::ZERO, heuristics_type::ZERO);
    cbs.setTargetReasoning(improvements);
    cbs.setMutexReasoning(false);
    cbs.setConflictSelectionRule(conflict_selection::EARLIEST);
    cbs.setNodeSelectionRule(node_selection::NODE_CONFLICTPAIRS); //
    cbs.setSavingStats(false);
    cbs.setHighLevelSolver(high_level_solver_type::ASTAREPS, 1.0);

    cbs.solve(vm["cutoffTime"].as<double>(), 0, MAX_COST);

    // save computation time
    results["replan-CBS-ICG-runtime"] = std::to_string(cbs.runtime);
    
    if (cbs.solution_found && cbs.validateSolution())
    {
        // count delays
        cbs.countInducedDelays(delay_instance->postDelayPlan);

        // save new plan to directory and shared data
        ofstream myfile;
        myfile.open (std::string(data.local_path) + "replan-CBS-ICG.txt");
        // int soc = 0; // must compute soc manually for replanning
        for (int a = 0; a < cbs.paths.size(); a++)
        {
            myfile << "Agent: " << a << std::endl;
            for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
            {
                auto entry = (*cbs.paths[a])[i];
                myfile << i << " " <<
                delay_instance->getRowCoordinate(entry.Loc.location) << " " << 
                delay_instance->getColCoordinate(entry.Loc.location) << std::endl;
            }
        }
        results["replan-CBS-ICG-soc"] = std::to_string(cbs.solution_cost);
        results["replan-CBS-ICG-numDelays"] = std::to_string(delay_instance->numDelays);
        myfile.close();
    }
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
void write_csv(const string& file_name, const vector<pair<std::string, std::string>>& results_map)
{
    string name = file_name + ".csv";

    std::ifstream infile(name);
    bool exist = infile.good();
    infile.close();
    if (!exist)
    {
        ofstream addHeads(name);
        for (const auto &elem : results_map)
            addHeads << elem.first << ",";
        addHeads << std::endl;
        addHeads.close();
    }
    ofstream stats(name, std::ios::app);
    for (const auto &elem : results_map)
        stats << elem.second << ",";
    stats << std::endl;
    std::cout << "Finished writing results." << std::endl;
}

void write_csv(const string& file_name, const std::unordered_map<std::string, std::string> &results)
{
    string name = file_name + ".csv";

    std::ifstream infile(name);
    bool exist = infile.good();
    infile.close();
    if (!exist)
    {
        ofstream addHeads(name);
        for(auto kv : results)
            addHeads << kv.first << ",";
        addHeads << std::endl;
        addHeads.close();
    }
    ofstream stats(name, std::ios::app);
    for(auto kv : results)
        stats << kv.second << ",";
    stats << std::endl;
    std::cout << "Finished writing results." << std::endl;
}







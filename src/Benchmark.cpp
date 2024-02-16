#include "Benchmark.h"
#include <vector>


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

std::unordered_map<std::string, std::string> runExperiment_6(const po::variables_map vm)
{
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        // meta data
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"Num-Delays",                                                 std::to_string(dummy_var)},
        // initial solution data
        {"initial-EECBS-runtime",                                      std::to_string(dummy_var)},
        {"initial-EECBS-soc",                                          std::to_string(dummy_var)},
        /* replanning on OG */
        {"replan-LNS-SIPP-OG-first-runtime",                           std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-first-soc",                               std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-first-added-length",                      std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-best-runtime",                            std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-best-soc",                                std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-best-added-length",                       std::to_string(dummy_var)},
        {"replan-CBS-OG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-OG-soc",                                          std::to_string(dummy_var)},
        {"replan-CBS-OG-added-length",                                 std::to_string(dummy_var)},
        {"replan-EECBS-OG-first-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-OG-first-soc",                                  std::to_string(dummy_var)},
        {"replan-EECBS-OG-first-added-length",                         std::to_string(dummy_var)},
        {"replan-EECBS-OG-BBC-runtime",                                std::to_string(dummy_var)},
        {"replan-EECBS-OG-BBC-soc",                                    std::to_string(dummy_var)},
        {"replan-EECBS-OG-BBC-added-length",                           std::to_string(dummy_var)},
        {"replan-EECBS-OG-best-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-OG-best-soc",                                   std::to_string(dummy_var)},      
        {"replan-EECBS-OG-best-added-length",                          std::to_string(dummy_var)},
        /* replanning on CG */
        {"replan-LNS-SIPP-CG-first-runtime",                           std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-first-soc",                               std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-first-added-length",                      std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-runtime",                            std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-soc",                                std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-added-length",                       std::to_string(dummy_var)},
        {"replan-CBS-CG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-CG-soc",                                          std::to_string(dummy_var)},
        {"replan-CBS-CG-delays",                                       std::to_string(dummy_var)},
        {"replan-EECBS-CG-first-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-CG-first-soc",                                  std::to_string(dummy_var)},
        {"replan-EECBS-CG-first-delays",                               std::to_string(dummy_var)},
        {"replan-EECBS-CG-BBC-runtime",                                std::to_string(dummy_var)},
        {"replan-EECBS-CG-BBC-soc",                                    std::to_string(dummy_var)},
        {"replan-EECBS-CG-BBC-delays",                                 std::to_string(dummy_var)},
        {"replan-EECBS-CG-best-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-CG-best-soc",                                   std::to_string(dummy_var)},
        {"replan-EECBS-CG-best-delays",                                std::to_string(dummy_var)},
        /* replanning on ICG */
        {"replan-LNS-SIPP-CG-first-runtime",                           std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-first-soc",                               std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-first-added-length",                      std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-runtime",                            std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-soc",                                std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-best-added-length",                       std::to_string(dummy_var)},
        {"replan-CBS-ICG-runtime",                                     std::to_string(dummy_var)},
        {"replan-CBS-ICG-soc",                                         std::to_string(dummy_var)},
        {"replan-CBS-ICG-delays",                                      std::to_string(dummy_var)},
        {"replan-EECBS-ICG-first-runtime",                             std::to_string(dummy_var)},
        {"replan-EECBS-ICG-first-soc",                                 std::to_string(dummy_var)},
        {"replan-EECBS-ICG-first-delays",                              std::to_string(dummy_var)},
        {"replan-EECBS-ICG-BBC-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-ICG-BBC-soc",                                   std::to_string(dummy_var)},
        {"replan-EECBS-ICG-BBC-delays",                                std::to_string(dummy_var)},
        {"replan-EECBS-ICG-best-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-ICG-best-soc",                                  std::to_string(dummy_var)},
        {"replan-EECBS-ICG-best-delays",                               std::to_string(dummy_var)}
    };

    // initialize statistics structure
    PlannerData dataResults;

    // calculate initial solution with EECBS
    std::cout << "Calculating initial solution with Anytime-EECBS" << std::endl;
    // calcInitialSolution_EECBS(vm, results, dataResults);
    // dataResults.initial_plan.clear();
    calcInitialSolution_EECBS(vm, results, dataResults);

    // if initial plan was successful, then continue with re-planning
    if (results["Example-ID"] != "")
    {
        /* initialize the new constrained graph instance and update old instance */
        results["Num-Delays"] = std::to_string(vm["numDelays"].as<int>());
        DelayInstance* delay_instance = calcDelay(vm, results, dataResults);

        dataResults.original_instance->start_locations = delay_instance->start_locations;
        for (auto &L: dataResults.original_instance->start_locations) {
            L.index = -1; 
        }
        dataResults.original_instance->delay_ = delay_instance->delay_;
        dataResults.original_instance->originalPlan = delay_instance->originalPlan;
        dataResults.original_instance->postDelayPlan = delay_instance->postDelayPlan;
        
        /* Replan on Original Graph */
        calcReplan_CBS_OG(dataResults.original_instance, vm, results, dataResults);
        results["replan-CBS-OG-added-length"] = std::to_string(stoi(results["replan-CBS-OG-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));

        calcReplan_LNS_SIPP_OG(dataResults.original_instance, vm, results, dataResults);
        results["replan-LNS-SIPP-OG-first-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-OG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-LNS-SIPP-OG-best-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-OG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        calcReplan_EECBS_OG(dataResults.original_instance, vm, results, dataResults);
        results["replan-EECBS-OG-first-added-length"] = std::to_string(stoi(results["replan-EECBS-OG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        if (stoi(results["replan-EECBS-OG-BBC-soc"]) > 0)
            results["replan-EECBS-OG-BBC-added-length"] = std::to_string(stoi(results["replan-EECBS-OG-BBC-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-EECBS-OG-best-added-length"] = std::to_string(stoi(results["replan-EECBS-OG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        /* Replan on Constrained Graph */
        calcReplan_CBS_CG(delay_instance, vm, results, dataResults);
        results["replan-CBS-CG-delays"] = std::to_string(stoi(results["replan-CBS-CG-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));

        calcReplan_LNS_SIPP_CG(delay_instance, vm, results, dataResults);
        results["replan-LNS-SIPP-CG-first-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-CG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-LNS-SIPP-CG-best-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-CG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        calcReplan_EECBS_CG(delay_instance, vm, results, dataResults);
        results["replan-EECBS-CG-first-delays"] = std::to_string(stoi(results["replan-EECBS-CG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        if (stoi(results["replan-EECBS-CG-BBC-soc"]) > 0)
            results["replan-EECBS-CG-BBC-delays"] = std::to_string(stoi(results["replan-EECBS-CG-BBC-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-EECBS-CG-best-delays"] = std::to_string(stoi(results["replan-EECBS-CG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        /* Activate improved constrained graph */
        delay_instance->activateImprovement();

        /* Replan on Improved Constrained Graph */
        calcReplan_CBS_ICG(delay_instance, vm, results, dataResults);
        results["replan-CBS-ICG-delays"] = std::to_string(stoi(results["replan-CBS-ICG-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        calcReplan_EECBS_ICG(delay_instance, vm, results, dataResults);
        results["replan-EECBS-ICG-first-delays"] = std::to_string(stoi(results["replan-EECBS-ICG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        if (stoi(results["replan-EECBS-ICG-BBC-soc"]) > 0)
            results["replan-EECBS-ICG-BBC-delays"] = std::to_string(stoi(results["replan-EECBS-ICG-BBC-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-EECBS-ICG-best-delays"] = std::to_string(stoi(results["replan-EECBS-ICG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        
        calcReplan_LNS_SIPP_ICG(delay_instance, vm, results, dataResults);
        results["replan-LNS-SIPP-ICG-first-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-ICG-first-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
        results["replan-LNS-SIPP-ICG-best-added-length"] = std::to_string(stoi(results["replan-LNS-SIPP-ICG-best-soc"]) - (stoi(results["initial-EECBS-soc"]) + 1));
    }
    return results;
}

std::unordered_map<std::string, std::string> runNewPlanner(const po::variables_map vm)
{
    // initialize the results directory
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"initial-runtime",                                            std::to_string(dummy_var)},
        {"initial-soc",                                                std::to_string(dummy_var)}
    };

    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with New Algorithm
    calcInitialSolution_NewAlg(vm, results, dataResults);

    return results;
}

std::unordered_map<std::string, std::string> runExperiment_5(const po::variables_map vm)
{
    // initialize the results directory
    int dummy_var = std::numeric_limits<int>::min();
    std::unordered_map<std::string, std::string> results {
        {"Example-ID",                                                                        ""},
        {"Num-Agents",                                                 std::to_string(dummy_var)},
        {"initial-runtime",                                            std::to_string(dummy_var)},
        {"initial-soc",                                                std::to_string(dummy_var)},
        // replan w/ EECBS on OG
        {"replan-EECBS-OG-first-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-OG-first-soc",                                  std::to_string(dummy_var)},
        {"replan-EECBS-OG-best-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-OG-best-soc",                                   std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on OG
        {"replan-LNS-SIPP-OG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-OG-soc",                                     std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on CG
        {"replan-LNS-SIPP-CG-runtime",                                 std::to_string(dummy_var)},
        {"replan-LNS-SIPP-CG-soc",                                     std::to_string(dummy_var)},
        // replan w/ CBS on CG
        {"replan-CBS-CG-runtime",                                      std::to_string(dummy_var)},
        {"replan-CBS-CG-soc",                                          std::to_string(dummy_var)},
        // replan w/ EECBS on CG
        {"replan-EECBS-CG-first-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-CG-first-soc",                                  std::to_string(dummy_var)},
        {"replan-EECBS-CG-BBC-runtime",                                std::to_string(dummy_var)},
        {"replan-EECBS-CG-BBC-soc",                                    std::to_string(dummy_var)},
        {"replan-EECBS-CG-best-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-CG-best-soc",                                   std::to_string(dummy_var)},
        // replan w/ LNS-SIPP on ICG
        {"replan-LNS-SIPP-ICG-runtime",                                std::to_string(dummy_var)},
        {"replan-LNS-SIPP-ICG-soc",                                    std::to_string(dummy_var)},
        // replan w/ CBS on ICG
        {"replan-CBS-ICG-runtime",                                     std::to_string(dummy_var)},
        {"replan-CBS-ICG-soc",                                         std::to_string(dummy_var)},
        // replan w/ EECBS on ICG
        {"replan-EECBS-ICG-first-runtime",                             std::to_string(dummy_var)},
        {"replan-EECBS-ICG-first-soc",                                 std::to_string(dummy_var)},
        {"replan-EECBS-ICG-BBC-runtime",                               std::to_string(dummy_var)},
        {"replan-EECBS-ICG-BBC-soc",                                   std::to_string(dummy_var)},
        {"replan-EECBS-ICG-best-runtime",                              std::to_string(dummy_var)},
        {"replan-EECBS-ICG-best-soc",                                  std::to_string(dummy_var)}
    };

    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with EECBS
    calcInitialSolution_EECBS(vm, results, dataResults);

    // if initial plan was successful, then continue with replanning
    if (results["Example-ID"] != "")
    {
        // create delay instance and set-up delay
        DelayInstance* delay_instance = calcDelay(vm, results, dataResults);
        dataResults.original_instance->updateStartLocations(delay_instance->getStarts());
        dataResults.original_instance->delay_ = delay_instance->delay_;

        // replan w/ available planners on OG
        calcReplan_EECBS_OG(dataResults.original_instance, vm, results, dataResults);
        calcReplan_LNS_SIPP_OG(dataResults.original_instance, vm, results, dataResults);

        // replan w/ available planners on CG
        calcReplan_LNS_SIPP_CG(delay_instance, vm, results, dataResults);
        calcReplan_CBS_CG(delay_instance, vm, results, dataResults);
        calcReplan_EECBS_CG(delay_instance, vm, results, dataResults);

        // activate ICG
        delay_instance->activateImprovement();

        // replan w/ available planners on ICG
        calcReplan_LNS_SIPP_ICG(delay_instance, vm, results, dataResults);
        calcReplan_CBS_ICG(delay_instance, vm, results, dataResults);
        calcReplan_EECBS_ICG(delay_instance, vm, results, dataResults);
    }

    return results;
}

std::unordered_map<std::string, std::string> runExperiment_4(const po::variables_map vm)
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
        // replan w/ LNS-SIPP on ICG
        {"replan-LNS-SIPP-ICG-runtime",                                std::to_string(dummy_var)},
        {"replan-LNS-SIPP-ICG-soc",                                    std::to_string(dummy_var)},
        {"replan-LNS-SIPP-ICG-numDelays",                              std::to_string(dummy_var)},
        // replan w/ CBS on ICG
        {"replan-CBS-ICG-runtime",                                     std::to_string(dummy_var)},
        {"replan-CBS-ICG-soc",                                         std::to_string(dummy_var)},
        {"replan-CBS-ICG-numDelays",                                   std::to_string(dummy_var)}
    };
    
    // initialize statistics stucture
    PlannerData dataResults;

    // calculate initial solution with LNS
    // calcInitialSolution_LNS(vm, results, dataResults);
    calcInitialSolution_EECBS(vm, results, dataResults);
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

        // activate ICG
        delay_instance->activateImprovement();

        // replan w/ LNS-SIPP on OG
        calcReplan_LNS_SIPP_OG(dataResults.original_instance, vm, results, dataResults);
        // std::cout << "replan LNS OG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-OG-soc"] << std::endl;

        // replan w/ LNS-SIPP on ICG
        calcReplan_LNS_SIPP_ICG(delay_instance, vm, results, dataResults);
        // std::cout << "replan LNS-SIPP ICG" << std::endl;
        // std::cout << results["replan-LNS-SIPP-ICG-runtime"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-ICG-soc"] << std::endl;
        // std::cout << results["replan-LNS-SIPP-ICG-numDelays"] << std::endl;

        // replan w/ CBS on ICG
        calcReplan_CBS_ICG(delay_instance, vm, results, dataResults);
        // std::cout << "replan CBS ICG" << std::endl;
        // std::cout << results["replan-CBS-ICG-runtime"] << std::endl;
        // std::cout << results["replan-CBS-ICG-soc"] << std::endl;
        // std::cout << results["replan-CBS-ICG-numDelays"] << std::endl;
    }
    return results;
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

void calcInitialSolution_NewAlg(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
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

    // for (int a=0; a < instance->getDefaultNumberOfAgents(); a++)
    // {
    //     std::cout << instance->getStarts()[a].location << std::endl;
    // }

    NewAlg newAlgorithm(instance, false, vm["screen"].as<int>());

    newAlgorithm.solve(vm["cutoffTime"].as<double>(), 0, MAX_COST);

    // save computation time
    results["initial-newAlg-runtime"] = std::to_string(newAlgorithm.runtime);

    if (newAlgorithm.solution_found)
    {
        if (data.initial_plan.empty())
        {
            // save instance-related data
            results["Num-Agents"] = std::to_string(instance->getDefaultNumberOfAgents());
            // create the results directory
            results["Example-ID"] = random_string();
            string random_dir_str = "Results/" + results["Example-ID"] + "/";
            data.local_path = random_dir_str; // Is this assignment safe?
            fs::create_directories(data.local_path);
            // save initial plan to directory and shared data
            ofstream myfile;
            myfile.open (string(data.local_path.string()) + "initial_solution.txt");
            for (int a = 0; a < newAlgorithm.paths.size(); a++)
            {
                myfile << "Agent: " << a << std::endl;
                Path a_path;
                for (int i = 0; i < newAlgorithm.paths[a]->size(); i++) // const auto entry : agent.path
                {
                    auto entry = (*newAlgorithm.paths[a])[i];
                    myfile << i << " " <<
                    instance->getRowCoordinate(entry.Loc.location) << " " << 
                    instance->getColCoordinate(entry.Loc.location) << std::endl;
                    a_path.emplace_back(entry);
                }
                data.initial_plan.push_back(a_path);
            }
            myfile.close();
        }
        results["initial-newAlg-soc"] = std::to_string(newAlgorithm.solution_cost);
    }
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
        myfile.open (string(data.local_path.string()) + "initial_solution.txt");
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

void calcInitialSolution_EECBS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
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

    AnytimeEECBS a_eecbs(instance, vm["cutoffTime"].as<double>(), vm["screen"].as<int>());

    a_eecbs.run();

    // save computation time
    results["initial-EECBS-runtime"] = std::to_string(a_eecbs.runtime);

    if (a_eecbs.iteration_stats.empty())
        return;

    if (a_eecbs.validateSolution())
    {
        // create the results directory
        results["Example-ID"] = instance->getInstanceName();
        string random_dir_str = "Results/" + results["Example-ID"] + "/";
        data.local_path = random_dir_str; // Is this assignment safe?
        fs::create_directories(data.local_path);

        // save initial plan to directory and shared data
        ofstream myfile;
        myfile.open (string(data.local_path.string()) + "initial_solution.txt");
        for (int a = 0; a < a_eecbs.solution.size(); a++)
        {
            myfile << "Agent: " << a << std::endl;
            Path a_path;
            for (int i = 0; i < a_eecbs.solution[a].size(); i++) // const auto entry : agent.path
            {
                auto entry = a_eecbs.solution[a][i];
                myfile << i << " " <<
                instance->getRowCoordinate(entry.Loc.location) << " " << 
                instance->getColCoordinate(entry.Loc.location) << std::endl;
                a_path.emplace_back(entry);
            }
            data.initial_plan.push_back(a_path);
        }
        myfile.close();
        std::cout << "EECBS init soc: " << a_eecbs.iteration_stats.back().sum_of_costs << std::endl;
        results["initial-EECBS-soc"] = std::to_string(a_eecbs.iteration_stats.back().sum_of_costs);
    }
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
        myfile.open (string(data.local_path.string()) + "initial_solution.txt");
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
        int soc = 0;
        for (auto p: cbs.paths) {
            soc += p->size() - 1;
        }
        std::cout << "CBS init soc: " << soc << std::endl;
        std::cout << "CBS init solution_cost: " << cbs.solution_cost << std::endl;
        results["initial-CBS-soc"] = std::to_string(soc);
    }
}

DelayInstance* calcDelay(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData& data)
{
	// create delay instance
    DelayInstance* nxtInstance = new DelayInstance(vm["map"].as<string>(), 
    		vm["agents"].as<string>(), data.initial_plan, vm["agentNum"].as<int>(), vm["numDelays"].as<int>());

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
        ofstream mydelay(string(data.local_path.string()) + "delay.txt");
        // Write to the file
        for (int i = 0; i < nxtInstance->num_of_delays_; i++)
            mydelay << (*nxtInstance->delay_[i]).first << ' ' << (*nxtInstance->delay_[i]).second;
        // Close the file
        mydelay.close();
    }
    return nxtInstance;
}

void calcReplan_EECBS_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    AnytimeEECBS a_eecbs(replan_instance, vm["cutoffTime"].as<double>(), vm["screen"].as<int>());
    a_eecbs.replanning  = true;
    a_eecbs.run();
    
    if (a_eecbs.iteration_stats.empty())
        return;

    // save computation time
    results["replan-EECBS-OG-first-runtime"] = std::to_string(a_eecbs.iteration_stats.front().runtime);
    results["replan-EECBS-OG-best-runtime"] = std::to_string(a_eecbs.iteration_stats.back().runtime);
    if (std::stod(results["replan-CBS-OG-runtime"]) > std::stod(results["replan-EECBS-OG-first-runtime"]))
    {
        // find the best solution from EECBS given the time limit of CBS
        for (auto stat_itr = a_eecbs.iteration_stats.begin(); stat_itr != a_eecbs.iteration_stats.end(); stat_itr++)
        {
            if (std::stod(results["replan-CBS-OG-runtime"]) > stat_itr->runtime)
            {
                results["replan-EECBS-OG-BBC-runtime"] = std::to_string(stat_itr->runtime);
                int soc = 0;
                int delay_time = replan_instance->delay_[0]->second;
                std::vector<Path> new_paths = stat_itr->paths;
                std::vector<Path> old_paths = replan_instance->postDelayPlan;
                for (int idx = 0; idx != new_paths.size(); idx++) {
                    auto olp_path = old_paths[idx];
                    auto new_path = new_paths[idx];
                    if (new_path.size() == 1)
                        soc += olp_path.size() - 1;
                    else
                        soc += delay_time + new_path.size();
                }
                int t = stoi(results["initial-EECBS-soc"]);
                if (soc == t) {
                    std::cout << "ERROR!" << std::endl;
                    exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
                }
                results["replan-EECBS-OG-BBC-soc"] =  std::to_string(soc);
            }
            else
                break;
        }
    }
    cout << "Testing Solution validity: " << a_eecbs.validateSolution() << endl;
    if (a_eecbs.validateSolution())
    {
        // save SOC
        int soc_first = 0;
        int delay_time = replan_instance->delay_[0]->second;
        std::vector<Path> new_paths = a_eecbs.iteration_stats.front().paths;
        std::vector<Path> old_paths = replan_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_first += olp_path.size() - 1;
            else
                soc_first += delay_time + new_path.size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        // if (soc_first == t) { // on OG we can find better solutions -- this only counts on CG/ICG
        //     std::cout << "ERROR!" << std::endl;
        //     exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        // }
        results["replan-EECBS-OG-first-soc"] = std::to_string(soc_first);
        cout  << soc_first << " -- " << results["replan-EECBS-OG-first-soc"] << endl;
        int soc_best = 0;
        new_paths = a_eecbs.iteration_stats.back().paths;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_best += olp_path.size() - 1;
            else
                soc_best += delay_time + new_path.size();
        }
        if (soc_best == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-EECBS-OG-best-soc"] = std::to_string(soc_best);
        cout  << soc_best << " -- " << results["replan-EECBS-OG-best-soc"] << endl;
    }
}

void calcReplan_EECBS_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    AnytimeEECBS a_eecbs(delay_instance, vm["cutoffTime"].as<double>(), vm["screen"].as<int>());
    a_eecbs.replanning  = true;
    a_eecbs.run();

    
    if (a_eecbs.iteration_stats.empty())
        return;

    // save computation time
    results["replan-EECBS-CG-first-runtime"] = std::to_string(a_eecbs.iteration_stats.front().runtime);
    results["replan-EECBS-CG-best-runtime"] = std::to_string(a_eecbs.iteration_stats.back().runtime);
    if (std::stod(results["replan-CBS-CG-runtime"]) > std::stod(results["replan-EECBS-CG-first-runtime"]))
    {
        // find the best solution from EECBS given the time limit of CBS
        for (auto stat_itr = a_eecbs.iteration_stats.begin(); stat_itr != a_eecbs.iteration_stats.end(); stat_itr++)
        {
            if (std::stod(results["replan-CBS-CG-runtime"]) > stat_itr->runtime)
            {
                results["replan-EECBS-CG-BBC-runtime"] = std::to_string(stat_itr->runtime);
                int soc = 0;
                int delay_time = delay_instance->delay_[0]->second;
                std::vector<Path> new_paths = stat_itr->paths;
                std::vector<Path> old_paths = delay_instance->postDelayPlan;
                for (int idx = 0; idx != new_paths.size(); idx++) {
                    auto olp_path = old_paths[idx];
                    auto new_path = new_paths[idx];
                    if (new_path.size() == 1)
                        soc += olp_path.size() - 1;
                    else
                        soc += delay_time + new_path.size();
                }
                int t = stoi(results["initial-EECBS-soc"]);
                if (soc == t) {
                    std::cout << "ERROR!" << std::endl;
                    exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
                }
                results["replan-EECBS-CG-BBC-soc"] =  std::to_string(soc);
            }
            else
                break;
        }
    }

    if (a_eecbs.validateSolution())
    {
        // save SOC
        int soc_first = 0;
        int delay_time = delay_instance->delay_[0]->second;
        std::vector<Path> new_paths = a_eecbs.iteration_stats.front().paths;
        std::vector<Path> old_paths = delay_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_first += olp_path.size() - 1;
            else
                soc_first += delay_time + new_path.size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        if (soc_first == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-EECBS-CG-first-soc"] = std::to_string(soc_first);
        int soc_best = 0;
        new_paths = a_eecbs.iteration_stats.back().paths;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_best += olp_path.size() - 1;
            else
                soc_best += delay_time + new_path.size();
        }
        if (soc_best == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-EECBS-CG-best-soc"] = std::to_string(soc_best);
    }
}

void calcReplan_EECBS_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
{
    AnytimeEECBS a_eecbs(delay_instance, vm["cutoffTime"].as<double>(), vm["screen"].as<int>());
    a_eecbs.replanning  = true;
    a_eecbs.run();

    
    if (a_eecbs.iteration_stats.empty())
        return;
    // save computation time
    results["replan-EECBS-ICG-first-runtime"] = std::to_string(a_eecbs.iteration_stats.front().runtime);
    results["replan-EECBS-ICG-best-runtime"] = std::to_string(a_eecbs.iteration_stats.back().runtime);
    if (std::stod(results["replan-CBS-ICG-runtime"]) > std::stod(results["replan-EECBS-ICG-first-runtime"]))
    {
        // find the best solution from EECBS given the time limit of CBS
        for (auto stat_itr = a_eecbs.iteration_stats.begin(); stat_itr != a_eecbs.iteration_stats.end(); stat_itr++)
        {
            if (std::stod(results["replan-CBS-ICG-runtime"]) > stat_itr->runtime)
            {
                results["replan-EECBS-ICG-BBC-runtime"] = std::to_string(stat_itr->runtime);
                int soc = 0;
                int delay_time = delay_instance->delay_[0]->second;
                std::vector<Path> new_paths = stat_itr->paths;
                std::vector<Path> old_paths = delay_instance->postDelayPlan;
                for (int idx = 0; idx != new_paths.size(); idx++) {
                    auto olp_path = old_paths[idx];
                    auto new_path = new_paths[idx];
                    if (new_path.size() == 1)
                        soc += olp_path.size() - 1;
                    else
                        soc += delay_time + new_path.size();
                }
                int t = stoi(results["initial-EECBS-soc"]);
                if (soc == t) {
                    std::cout << "ERROR!" << std::endl;
                    exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
                }
                results["replan-EECBS-ICG-BBC-soc"] =  std::to_string(soc);
            }
            else
                break;
        }
    }

    if (a_eecbs.validateSolution())
    {
        // save SOC
        int soc_first = 0;
        int delay_time = delay_instance->delay_[0]->second;
        std::vector<Path> new_paths = a_eecbs.iteration_stats.front().paths;
        std::vector<Path> old_paths = delay_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_first += olp_path.size() - 1;
            else
                soc_first += delay_time + new_path.size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        if (soc_first == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-EECBS-ICG-first-soc"] = std::to_string(soc_first);
        int soc_best = 0;
        new_paths = a_eecbs.iteration_stats.back().paths;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path.size() == 1)
                soc_best += olp_path.size() - 1;
            else
                soc_best += delay_time + new_path.size();
        }
        if (soc_best == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-EECBS-ICG-best-soc"] = std::to_string(soc_best);
    }
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
                vm["sipp"].as<bool>(),
                vm["screen"].as<int>(), data.pipp_options);

	// run LNS
	bool succ = lns.run();

    if (lns.iteration_stats.empty())
        return;
    // save computation time
    results["replan-LNS-SIPP-OG-first-runtime"] = std::to_string(lns.iteration_stats.front().runtime);
    results["replan-LNS-SIPP-OG-best-runtime"] = std::to_string(lns.iteration_stats.back().runtime);

    // lns.validateSolution(); // exits out of program if not valid
    if (!succ)
        return;

    // save SOC
    int soc_first = 0;
    int delay_time = replan_instance->delay_[0]->second;
    std::vector<Path> new_paths = lns.iteration_stats.front().paths;
    if (new_paths.empty()) {
        cout << "HERE" << endl;
        exit(1);
    }
    std::vector<Path> old_paths = replan_instance->postDelayPlan;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_first += olp_path.size() - 1;
        else
            soc_first += delay_time + new_path.size();
    }
    int t = stoi(results["initial-EECBS-soc"]);
    if (soc_first == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-OG-first-soc"] = std::to_string(soc_first);
        
    int soc_best = 0;
    new_paths = lns.iteration_stats.back().paths;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_best += olp_path.size() - 1;
        else
            soc_best += delay_time + new_path.size();
    }
    if (soc_best == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-OG-best-soc"] = std::to_string(soc_best);

    // cout << lns.iteration_stats.front().runtime << endl;
    // cout << lns.iteration_stats.front().sum_of_costs << endl;
    // cout << lns.iteration_stats.front().num_of_colliding_pairs << endl;

    // cout << lns.iteration_stats.back().runtime << endl;
    // cout << lns.iteration_stats.back().sum_of_costs << endl;
    // cout << lns.iteration_stats.front().num_of_colliding_pairs << endl;
    // exit(1);

	// // save computation time
	// results["replan-LNS-SIPP-OG-runtime"] = std::to_string(lns.runtime);

	// if (succ)
    // {

    //     cout << lns.iteration_stats.size() << endl;
    //     exit(1);

    // 	// make sure solution is correct
    //     lns.validateSolution();
    //     // save SOC
    //     int soc = 0;
    //     int delay_time = replan_instance->delay_[0]->second;
    //     std::vector<Path> old_paths = replan_instance->postDelayPlan;
    //     int idx = 0; 
    //     for (auto &a: lns.agents) {
    //         auto olp_path = old_paths[idx];
    //         if (a.path.size() == 1)
    //             soc += olp_path.size() - 1;
    //         else
    //             soc += delay_time + a.path.size();
    //         idx++;
    //     }
    //     int t = stoi(results["initial-EECBS-soc"]);
    //     if (soc == t) {
    //         std::cout << "ERROR!" << std::endl;
    //         exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    //     }
    //     results["replan-LNS-SIPP-OG-soc"] = std::to_string(soc);
    // }
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
                vm["sipp"].as<bool>(),
                vm["screen"].as<int>(), data.pipp_options);


    // run LNS
    bool succ = lns.run();

    if (lns.iteration_stats.empty())
        return;
    // save computation time
    results["replan-LNS-SIPP-CG-first-runtime"] = std::to_string(lns.iteration_stats.front().runtime);
    results["replan-LNS-SIPP-CG-best-runtime"] = std::to_string(lns.iteration_stats.back().runtime);

    // lns.validateSolution(); // exits out of program if not valid
    if (!succ)
        return;

    // save SOC
    int soc_first = 0;
    int delay_time = delay_instance->delay_[0]->second;
    std::vector<Path> new_paths = lns.iteration_stats.front().paths;
    std::vector<Path> old_paths = delay_instance->postDelayPlan;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_first += olp_path.size() - 1;
        else
            soc_first += delay_time + new_path.size();
    }
    int t = stoi(results["initial-EECBS-soc"]);
    if (soc_first == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-CG-first-soc"] = std::to_string(soc_first);
        
    int soc_best = 0;
    new_paths = lns.iteration_stats.back().paths;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_best += olp_path.size() - 1;
        else
            soc_best += delay_time + new_path.size();
    }
    if (soc_best == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-CG-best-soc"] = std::to_string(soc_best);
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
        // save file here, if needed
        // ofstream myfile;
        // myfile.open (std::string(data.local_path) + "replan-CBS-OG.txt");
        // // int soc = 0; // must compute soc manually for replanning
        // for (int a = 0; a < cbs.paths.size(); a++)
        // {
        //     myfile << "Agent: " << a << std::endl;
        //     for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
        //     {
        //         auto entry = (*cbs.paths[a])[i];
        //         myfile << i << " " <<
        //         replan_instance->getRowCoordinate(entry.Loc.location) << " " << 
        //         replan_instance->getColCoordinate(entry.Loc.location) << std::endl;
        //     }
        // }
        // myfile.close();
        // save SOC
        int soc = 0;
        int delay_time = replan_instance->delay_[0]->second;
        std::vector<Path*> new_paths = cbs.paths;
        std::vector<Path> old_paths = replan_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path->size() == 1)
                soc += olp_path.size() - 1;
            else
                soc += delay_time + new_path->size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        if (soc == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-CBS-OG-soc"] = std::to_string(soc);
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

        // save file here, if needed
        // ofstream myfile;
        // myfile.open (std::string(data.local_path) + "replan-CBS-CG.txt");
        // // int soc = 0; // must compute soc manually for replanning
        // for (int a = 0; a < cbs.paths.size(); a++)
        // {
        //     myfile << "Agent: " << a << std::endl;
        //     for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
        //     {
        //         auto entry = (*cbs.paths[a])[i];
        //         myfile << i << " " <<
        //         delay_instance->getRowCoordinate(entry.Loc.location) << " " << 
        //         delay_instance->getColCoordinate(entry.Loc.location) << std::endl;
        //     }
        // }
        // myfile.close();
        // save SOC
        int soc = 0;
        int delay_time = delay_instance->delay_[0]->second;
        std::vector<Path*> new_paths = cbs.paths;
        std::vector<Path> old_paths = delay_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path->size() == 1)
                soc += olp_path.size() - 1;
            else
                soc += delay_time + new_path->size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        if (soc == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-CBS-CG-soc"] = std::to_string(soc);
    }
}

void calcReplan_LNS_SIPP_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data)
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
                vm["sipp"].as<bool>(),
                vm["screen"].as<int>(), data.pipp_options);


    // run LNS
    bool succ = lns.run();

    if (lns.iteration_stats.empty())
        return;
    // save computation time
    results["replan-LNS-SIPP-ICG-first-runtime"] = std::to_string(lns.iteration_stats.front().runtime);
    results["replan-LNS-SIPP-ICG-best-runtime"] = std::to_string(lns.iteration_stats.back().runtime);

    // lns.validateSolution(); // exits out of program if not valid
    if (!succ)
        return;

    // save SOC
    int soc_first = 0;
    int delay_time = delay_instance->delay_[0]->second;
    std::vector<Path> new_paths = lns.iteration_stats.front().paths;
    std::vector<Path> old_paths = delay_instance->postDelayPlan;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_first += olp_path.size() - 1;
        else
            soc_first += delay_time + new_path.size();
    }
    int t = stoi(results["initial-EECBS-soc"]);
    if (soc_first == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-ICG-first-soc"] = std::to_string(soc_first);
        
    int soc_best = 0;
    new_paths = lns.iteration_stats.back().paths;
    for (int idx = 0; idx != new_paths.size(); idx++) {
        auto olp_path = old_paths[idx];
        auto new_path = new_paths[idx];
        if (new_path.size() == 1)
            soc_best += olp_path.size() - 1;
        else
            soc_best += delay_time + new_path.size();
    }
    if (soc_best == t) {
        std::cout << "ERROR!" << std::endl;
        exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
    }
    results["replan-LNS-SIPP-ICG-best-soc"] = std::to_string(soc_best);
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
        // save file here, if needed
        // ofstream myfile;
        // myfile.open (std::string(data.local_path) + "replan-CBS-ICG.txt");
        // // int soc = 0; // must compute soc manually for replanning
        // for (int a = 0; a < cbs.paths.size(); a++)
        // {
        //     myfile << "Agent: " << a << std::endl;
        //     for (int i = 0; i < cbs.paths[a]->size(); i++) // const auto entry : agent.path
        //     {
        //         auto entry = (*cbs.paths[a])[i];
        //         myfile << i << " " <<
        //         delay_instance->getRowCoordinate(entry.Loc.location) << " " << 
        //         delay_instance->getColCoordinate(entry.Loc.location) << std::endl;
        //     }
        // }
        // myfile.close();
        // save SOC
        int soc = 0;
        int delay_time = delay_instance->delay_[0]->second;
        std::vector<Path*> new_paths = cbs.paths;
        std::vector<Path> old_paths = delay_instance->postDelayPlan;
        for (int idx = 0; idx != new_paths.size(); idx++) {
            auto olp_path = old_paths[idx];
            auto new_path = new_paths[idx];
            if (new_path->size() == 1)
                soc += olp_path.size() - 1;
            else
                soc += delay_time + new_path->size();
        }
        int t = stoi(results["initial-EECBS-soc"]);
        if (soc == t) {
            std::cout << "ERROR!" << std::endl;
            exit(-1); // some kind of annoying bug soc should be >= t + 1. Just remove this example
        }
        results["replan-CBS-ICG-soc"] = std::to_string(soc);
    }
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

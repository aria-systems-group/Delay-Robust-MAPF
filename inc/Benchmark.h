#pragma once
#include "common.h"
#include "LNS.h"
#include "CBS.h"
#include "NewAlg.h"
#include "AnytimeEECBS.h"
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>


namespace po = boost::program_options;
namespace fs = boost::filesystem;
typedef std::vector<char> char_array;


// a struct object that holds relevent statistics for planners
struct PlannerStats
{
	double original_plan_comp_time = -1;

	double lns_sipp_replan_comp_time = -1;
	int lns_sipp_replan_delay_count = -1;

	double lns_no_sipp_replan_comp_time = -1;
	int lns_no_sipp_replan_delay_count = -1;

	double cbs_replan_comp_time = -1;
	int cbs_replan_delay_count = -1;

	double cbs_replan_icg_comp_time = -1;
	int cbs_replan_icg_delay_count = -1;

	double lns_sipp_replan_igp_comp_time = -1;
	int lns_sipp_replan_igp_delay_count = -1;

	double lns_nosipp_replan_igp_comp_time = -1;
	int lns_nosipp_replan_igp_delay_count = -1;
};

// a struct object that holds releven data returned from planners
struct PlannerData
{
	// int num_agents = -1;
	vector<Path> initial_plan{};
	// string example_id = "";
	fs::path local_path = "";
	PIBTPPS_option pipp_options;
	Instance* original_instance = nullptr;
};

string random_string();

// this is a randomization function used for programs faster than 1 second 
unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

// write results from results_map to file_name.csv
void write_csv(const string& file_name, const std::unordered_map<std::string, std::string> &results);

// new algorithm tests
std::unordered_map<std::string, std::string> runNewPlanner(const po::variables_map vm);

// main experiment functions
std::unordered_map<std::string, std::string> runExperiment_1(const po::variables_map vm);
std::unordered_map<std::string, std::string> runExperiment_2(const po::variables_map vm);
std::unordered_map<std::string, std::string> runExperiment_3(const po::variables_map vm);
std::unordered_map<std::string, std::string> runExperiment_4(const po::variables_map vm);
std::unordered_map<std::string, std::string> runExperiment_5(const po::variables_map vm);
std::unordered_map<std::string, std::string> runExperiment_6(const po::variables_map vm);

// calculate initial solution to problem
void calcInitialSolution_NewAlg(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcInitialSolution_LNS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcInitialSolution_CBS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcInitialSolution_EECBS(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);

// calculate a delay that causes a collision
DelayInstance* calcDelay(const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);

// replanning functions
void calcReplan_EECBS_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_EECBS_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_EECBS_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_LNS_SIPP_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_LNS_SIPP_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_LNS_SIPP_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_CBS_OG(Instance* replan_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_CBS_CG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);
void calcReplan_CBS_ICG(DelayInstance* delay_instance, const po::variables_map vm, std::unordered_map<std::string, std::string> &results, PlannerData &data);

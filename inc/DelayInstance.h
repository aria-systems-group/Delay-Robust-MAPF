#pragma once
#include "Instance.h"
#include <unordered_map>


class DelayInstance: public Instance
{
public:
	DelayInstance(const string& map_fname, const string& agent_fname, 
		vector<Path>& paths,
		int num_of_agents = 0, bool collidingPaths=false, int num_of_rows = 0, int num_of_cols = 0, 
		int num_of_obstacles = 0, int warehouse_width = 0);
	~DelayInstance() {};
	bool foundDelay()
	{
        if (!collidingPaths_)
        {
            if (delay_)
                return true;
            else
                return false;
        }   
        else 
        {
            return true;
        }
	}

    list<Location> getNeighbors(Location curr);

    int getDegree(int loc)
    {
    	auto n = getNeighbors(loc);
    	return n.size();
    }

    void activateImprovement() 
    {
    	improvements_++;
    	calcRepresentativePoints();
    	fillicgGraphMap();
    };

private:
	void createDelay();
	bool isCollisionFree();
	void changeStarts();
	list<Location> improvedCG_getNeighbors(Location curr);
	void calcRepresentativePoints();
	void fillicgGraphMap();
	void fillcgGraphMap();
	int improvements_;
    bool collidingPaths_;
	std::vector<Location> rep_points_;
	// std::vector<bool> isRepPoint;
	vector<unordered_map<Location, list<Location>, std::hash<Location>>> cgGraphMaps;
	vector<unordered_map<Location, list<Location>, std::hash<Location>>> icgGraphMaps;
};
#include "csv.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

struct location{
    double x;
    double y;
    std::vector<int> RSSi;

    bool operator<(const location& loc){
        return distance < loc.distance;
    }

    bool operator<=(const location& loc){
        return distance <= loc.distance;
    }

    int distance = INT_MAX;
};

std::ostream& operator<<(std::ostream& os, const location loc) { 
    os << "(" << loc.x << "," << loc.y << ")" << std::endl;

    os << "\t [";
    for (auto i : loc.RSSi) 
        os << i << ", ";
    os << "]" << std::endl;
    if (loc.distance != INT_MAX){
        os << "\t Distance: " << loc.distance << std::endl;
    }

    return os;
}

location kNN_location(std::vector<location>& list, int k);

void updateDistance(const location& p1, std::vector<location>& trainingList);

double euclideanDistance(const location& p1, const location& p2);

std::vector<location>  leesData(std::string filename, int number_of_lines  = INT_MAX );
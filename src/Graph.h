#ifndef GRAPH_H
#define GRAPH_H

#include "City.h"
#include <unordered_map>
#include <vector>
#include <string>

struct Edge
{
    std::string to;
    double cost;
};

class Graph
{
public:
    void loadCities(const std::string &filename);
    void loadEdges(const std::string &filename);

    const std::unordered_map<std::string, City> &getCities() const;
    const std::unordered_map<std::string, std::vector<Edge>> &getAdjList() const;

private:
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, std::vector<Edge>> adjList;
};

#endif

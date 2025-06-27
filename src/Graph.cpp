#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Graph::loadCities(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening cities file: " << filename << "\n";
        return;
    }
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, xs, ys;
        std::getline(ss, name, ',');
        std::getline(ss, xs, ',');
        std::getline(ss, ys, ',');

        double x = std::stod(xs);
        double y = std::stod(ys);
        cities[name] = City(name, x, y);
    }
}

void Graph::loadEdges(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening edges file: " << filename << "\n";
        return;
    }
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string from, to, distStr;

        std::getline(ss, from, ',');
        std::getline(ss, to, ',');
        std::getline(ss, distStr, ',');

        double cost = std::stod(distStr);
        adjList[from].push_back({to, cost});
        adjList[to].push_back({from, cost}); // undirected graph
    }
}

const std::unordered_map<std::string, City> &Graph::getCities() const
{
    return cities;
}

const std::unordered_map<std::string, std::vector<Edge>> &Graph::getAdjList() const
{
    return adjList;
}

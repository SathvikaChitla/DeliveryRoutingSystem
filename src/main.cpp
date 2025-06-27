#include "Graph.h"
#include "DeliveryManager.h"
#include <iostream>
#include <string>

int main()
{
    Graph graph;
    graph.loadCities("C:\\DeliveryRoutingSystem\\data\\cities.csv");
    graph.loadEdges("C:\\DeliveryRoutingSystem\\data\\edges.csv");

    std::string source, destination;
    int weight;
    std::string mode;

    std::cin >> source >> destination >> weight >> mode;

    DeliveryManager dm(graph);
    dm.findRoute(source, destination, weight, mode);

    return 0;
}

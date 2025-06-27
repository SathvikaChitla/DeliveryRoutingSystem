#ifndef DELIVERYMANAGER_H
#define DELIVERYMANAGER_H

#include "Graph.h"
#include <string>

class DeliveryManager
{
public:
    DeliveryManager(const Graph &graph);
    void findRoute(const std::string &start, const std::string &goal, double weightInGrams, const std::string &mode);

private:
    const Graph &graph;

    double calculateRealCourierCost(double distance, double weightInGrams, const std::string &mode);
};

#endif
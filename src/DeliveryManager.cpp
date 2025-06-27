#include "DeliveryManager.h"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cmath>
struct Node
{
    std::string city;
    double f, g;
    std::string parent;

    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

DeliveryManager::DeliveryManager(const Graph &graph) : graph(graph) {}

struct RateSlab
{
    double maxDistance;
    std::vector<double> baseRates; // 0: ≤200g, 1: ≤500g, 2: ≤1kg
    double extraPerKgAbove1kg;
};

double DeliveryManager::calculateRealCourierCost(double distance, double weightInGrams, const std::string &mode)
{
    std::vector<RateSlab> rateTable = {
        {500, {100, 130, 170}, 300},
        {1000, {140, 180, 240}, 400},
        {1e9, {180, 230, 310}, 600}};

    double weightKg = weightInGrams / 1000.0;
    int weightTier;

    if (weightInGrams <= 200)
        weightTier = 0;
    else if (weightInGrams <= 500)
        weightTier = 1;
    else if (weightInGrams <= 1000)
        weightTier = 2;
    else
        weightTier = 3;

    for (const auto &slab : rateTable)
    {
        if (distance <= slab.maxDistance)
        {
            double base = (weightTier <= 2) ? slab.baseRates[weightTier] : slab.baseRates[2];
            double extra = (weightTier == 3) ? slab.extraPerKgAbove1kg * std::ceil(weightKg - 1.0) : 0.0;
            double multiplier = (mode == "express") ? 1.5 : 1.0;
            return (base + extra) * multiplier;
        }
    }

    return 0.0; // fallback
}

void DeliveryManager::findRoute(const std::string &start, const std::string &goal, double weightInGrams, const std::string &mode)
{
    const auto &cities = graph.getCities();
    const auto &adj = graph.getAdjList();

    if (cities.find(start) == cities.end() || cities.find(goal) == cities.end())
    {
        std::cout << "Invalid city input.\n";
        return;
    }

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::unordered_map<std::string, double> gCost;
    std::unordered_map<std::string, std::string> parent;

    gCost[start] = 0;
    pq.push({start, cities.at(start).distanceTo(cities.at(goal)), 0, ""});

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        if (current.city == goal)
        {
            std::vector<std::string> path;
            std::string step = goal;
            while (!step.empty())
            {
                path.push_back(step);
                step = parent[step];
            }

            std::reverse(path.begin(), path.end());

            std::cout << "\n📍 Optimal Path: ";
            for (const auto &c : path)
                std::cout << c << " ";
            std::cout << "\n📦 Total Distance: " << current.g << " km";

            double finalCost = calculateRealCourierCost(current.g, weightInGrams, mode);
            std::cout << "\n💰 Estimated " << mode << " delivery cost: ₹" << finalCost << "\n";

            return;
        }

        if (adj.find(current.city) == adj.end())
            continue;

        for (const auto &edge : adj.at(current.city))
        {
            double tentative_g = current.g + edge.cost;

            if (!gCost.count(edge.to) || tentative_g < gCost[edge.to])
            {
                gCost[edge.to] = tentative_g;
                double h = cities.at(edge.to).distanceTo(cities.at(goal));
                pq.push({edge.to, tentative_g + h, tentative_g, current.city});
                parent[edge.to] = current.city;
            }
        }
    }

    std::cout << "No route found.\n";
}

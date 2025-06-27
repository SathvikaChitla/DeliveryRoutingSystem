#ifndef CITY_H
#define CITY_H

#include <string>

class City
{
public:
    std::string name;
    double latitude, longitude;

    City(std::string name = "", double latitude = 0, double longitude = 0);
    double distanceTo(const City &other) const; // Uses Haversine formula
};

#endif

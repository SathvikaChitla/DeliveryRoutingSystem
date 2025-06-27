#include "City.h"
#include <cmath>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constructor
City::City(std::string name, double latitude, double longitude)
    : name(name), latitude(latitude), longitude(longitude) {}

// Haversine formula to calculate distance between two lat/lng points
double City::distanceTo(const City &other) const
{
    const double R = 6371.0; // Earth's radius in kilometers
    double lat1_rad = latitude * M_PI / 180.0;
    double lon1_rad = longitude * M_PI / 180.0;
    double lat2_rad = other.latitude * M_PI / 180.0;
    double lon2_rad = other.longitude * M_PI / 180.0;

    double dlat = lat2_rad - lat1_rad;
    double dlon = lon2_rad - lon1_rad;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1_rad) * std::cos(lat2_rad) *
                   std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

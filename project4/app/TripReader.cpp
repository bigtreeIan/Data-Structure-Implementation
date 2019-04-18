// TripReader.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic

#include <sstream>
#include <string>
#include "TripReader.hpp"


std::vector<Trip> TripReader::readTrips(InputReader& in)
{
    std::vector<Trip> trips;

    int numberOfTrips = in.readIntLine();

    for (int i = 0; i < numberOfTrips; ++i)
    {
        std::istringstream tripLine{in.readLine()};

        int fromVertex;
        int toVertex;
        std::string metricType;

        tripLine >> fromVertex >> toVertex >> metricType;

        trips.push_back(
            {fromVertex, toVertex,
             metricType == "D" ? TripMetric::Distance : TripMetric::Time});
    }

    return trips;
}


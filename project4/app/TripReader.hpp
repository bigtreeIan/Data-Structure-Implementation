// TripReader.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// A TripReader reads a sequence of trips from the given input, assuming
// they're written in the format described in the project write-up.

#ifndef TRIPREADER_HPP
#define TRIPREADER_HPP

#include <vector>
#include "Trip.hpp"
#include "InputReader.hpp"



class TripReader
{
public:
    // readTrips() reads a sequence of trips from the given input,
    // returning them as a vector of Trip structs.
    std::vector<Trip> readTrips(InputReader& in);    
};



#endif // TRIPREADER_HPP

